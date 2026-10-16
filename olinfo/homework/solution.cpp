#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>
template<typename... Args>
using vec = vector<Args...>;
#ifdef LOCAL
bool DBG = 1;
#define infor(str, ...) do { print(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { println(stderr, str, ##__VA_ARGS__); } while(0)
#else
bool DBG = 0;
#define infor(...)
#define infof(...)
#endif
mt19937 timmy_loves_gambling(73);

struct segtree{
	struct node{
		int L=0, R=0;
		int x=0;
		bool lazy=0;
	};

	vec<node> t;
	int s;

	segtree(int N) {
		s = N;
		t.resize(2);
		t[1].x = s;
	}

	void push(int v, int l, int m, int r) {
		if(t[v].L == 0) {
			t[v].L = t.size();
			t[v].R = t.size()+1;
			t.emplace_back();
			t.emplace_back();
			t[t[v].L].x = m-l;
			t[t[v].R].x = r-m;
		}

		if(t[v].lazy) {
			t[t[v].L].x = 0;
			t[t[v].R].x = 0;
			t[t[v].L].lazy = 1;
			t[t[v].R].lazy = 1;
			//t[v].lazy = 0;
		}
	}

	void pull(int v) {
		t[v].x = t[t[v].L].x + t[t[v].R].x;
	}

	int find(int v, int l, int r, int k) {
		if(t[v].x < k) return -1;
		if(r-l == 1) return l;
		int m = (l+r)/2;
		push(v, l, m, r);
		if(t[t[v].R].x < k)
			return find(t[v].L, l, m, k-t[t[v].R].x);
		else
			return find(t[v].R, m, r, k);
	}

	int suff(int v, int l, int r, int p) {
		if(r <= p) return 0;
		if(l >= p) return t[v].x;
		int m = (l+r)/2;
		push(v, l, m, r);
		return suff(t[v].L, l, m, p) + suff(t[v].R, m, r, p);
	}

	void kill(int v, int l, int r, int ql, int qr) {
		if(qr <= l || r <= ql) return;
		if(ql <= l && r <= qr) {
			t[v].x = 0;
			t[v].lazy = 1;
			return;
		}
		int m = (l+r)/2;
		push(v, l, m, r);
		kill(t[v].L, l, m, ql, qr);
		kill(t[v].R, m, r, ql, qr);
		pull(v);
	}

	int find(int k) {
		return find(1, 0, s, k);
	}
	int suff(int p) {
		return suff(1, 0, s, p);
	}
	void kill(int ql, int qr) {
		kill(1, 0, s, ql, qr);
	}
};

void solve() {
	int N, M;
	cin >> N >> M;

	segtree sg(M);

	vec<pair<ll, ll>> v(N);
	for(auto &[a, b]: v) cin >> a >> b;
	sort(all(v));

	vector<ll> pfx(N), pfx2;
	for(int i=0; i<N; i++) pfx[i] = v[i].fi;
	for(int i=1; i<N; i++) pfx[i] += pfx[i-1];

	int ans = upper_bound(all(pfx), M)-pfx.begin();
	int used = 0;
	int ii = 0;

	for(auto &[s, d]: v) {
		ll p = sg.find(s + sg.suff(d));
		if(p == -1) {
			pfx2.push_back(s + (pfx2.empty() ? 0 : pfx2.back()) );
		}
		else {
			used++;
			sg.kill(p, d);
		}

		p = sg.suff(0);

		int k = upper_bound(all(pfx2), p)-pfx2.begin();
		if( 1) {
			ans = max(ans, used*2 + k);
		}
		else {
			k = upper_bound(all(pfx), pfx[ii] + p - (pfx2.empty()? 0: pfx2.back()))-pfx.begin();
			ans = max(ans, used*2 + (int)pfx2.size()+k-ii-1);
		}

		ii++;
	}

	cout << ans << "\n";
}


signed main(){	
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    int t; cin >> t;
	while(t--) solve();
}

