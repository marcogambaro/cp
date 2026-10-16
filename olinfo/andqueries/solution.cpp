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

int N, q;
vector<vector<int>> G;
map<pair<int, int>, int> edge;
vector<array<int, 2>> redge;
vector<ll> W;
vector<array<int, 4>> Q;
vector<ll> ans;
ll P;

struct Op{
	int a, va, b, vb;
	ll x;
};

struct Dsu{
	vector<int> v;
	stack<Op> hs;
	ll X = 0;

	ll calc(int n) {
		return (ll)v[n]*(v[n]-1)/2;
	}

	int findrep(int n) {
		if(v[n] > 0) return n;
		return findrep(-v[n]);
	}

	void unite(int a, int b) {
		a = findrep(a);
		b = findrep(b);

		assert(a != b);

		if(v[a] > v[b]) swap(a, b);
		hs.push({a, v[a], b, v[b], X});
		X -= calc(a);
		X -= calc(b);
		v[b] += v[a];
		v[a] = -b;
		X += calc(b);
	}

	void rollback(int K = 1) {
		while(K > 0) {
			Op op = hs.top();
			hs.pop();
			v[op.a] = op.va;
			v[op.b] = op.vb;
			X = op.x;
			K--;
		}
	}

	Dsu() {
		v.resize(N, 1);
	}
};

void solve() {
	vector<vector<array<int, 2>>> t(4*q + 7);

	auto insert = [&](int v, int l, int r, int ql, int qr, array<int, 2>& op, auto &&insert) -> void {
		if(ql > qr) return;
		if(ql == l && qr == r) {
			t[v].push_back(op);
			return;
		}

		int m = (l+r)/2;
		insert(v*2, l, m, ql, min(m, qr), op, insert);
		insert(v*2+1, m+1, r, max(m+1, ql), qr, op, insert);
	};

	vector<int> V(N-1);
	for(int i=1; i<=q; i++) {
		auto &[a, b, e, c] = Q[i];

		if((W[e] & P) && !(P & c)) {
			W[e] -= P;
			array<int, 2> op = {a, b};
			insert(1, 0, q, V[e], i-1, op, insert);
		}
		if(!(W[e] & P) && (P & c)) {
			W[e] += P;
			V[e] = i;
		}
	}
	for(int i=0; i<N-1; i++)
		if(W[i] & P)
			insert(1, 0, q, V[i], q, redge[i], insert);
		
	Dsu dsu;

	auto dfs = [&](int v, int l, int r, auto &&dfs) -> void {
		for(auto &[a, b]: t[v]) {
			dsu.unite(a, b);
		}

		if(l == r) {
			ans[l] += dsu.X * P;
		} else {
			int m = (l+r)/2;
			dfs(v*2, l, m, dfs);
			dfs(v*2+1, m+1, r, dfs);
		}

		dsu.rollback(t[v].size());
	};
	dfs(1, 0, q, dfs);
}

signed main(){	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N;
	G = vector(N, vector<int>());
	redge.resize(N-1);
	W.resize(N-1);
	for(int i=0; i<N-1; i++) {
		int a, b, c; cin >> a >> b >> c;
		if(a > b) swap(a, b);
		G[a].push_back(b);
		G[b].push_back(a);
		edge[{a, b}] = i;
		redge[i] = {a, b};
		W[i] = c;
	}

	cin >> q;
	Q.resize(q+1);
	ans.resize(q+1);
	for(int i=1; i<=q; i++) {
		int a, b, c; cin >> a >> b >> c;
		if(a > b) swap(a, b);
		int e = edge[{a, b}];
		Q[i] = {a, b, e, c};
	}

	//solve 1 bit at time
	for(P=1; P < (1 << 30); P*=2)
		solve();

	for(auto &i: ans) cout << i << " ";
}




