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

struct arco {
	int a, b;
};

struct operation {
	vector<int> V;
	int m;
	bool stat;

	operation(int _m, bool _stat) {
		m = _m;
		stat = _stat;
	}

	operation(int u, int size_u, int v, int m2_v, int _m, bool _stat) {
		V = {u, size_u, v, m2_v};
		m = _m;
		stat = _stat;
	}

	int operator() (int i) {
		return V[i];
	}
};

vector<arco> edge;
int N, M;

void get() {
	cin >> N >> M;
	edge.reserve(M);

	for(int i=0; i<M; i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		edge.push_back({a, b});
	}
}

struct rollback_DSU{
	vector<int> rep, sz;
	vector<bool> m2;
	stack<operation> ops;
	int cnt_a;

	rollback_DSU() {
		rep.resize(N);
		sz.resize(N);
		m2.resize(N);
		cnt_a = 0;

		for(int i=0; i<N; i++)
			rep[i] = i, sz[i] = 1;
	}

	pair<int, bool> findrep(int n) {
		if(n == rep[n]) return {n, 0};
		auto [r, m] = findrep(rep[n]);
		return {r, m^m2[n]};
	}

	void unite(int u, int v, int ma, int mb, int m, bool stat) {
		if(stat == 0) cnt_a++;

		if(u == v) {
			ops.push( operation(m, stat) );
			return;
		}

		if(sz[u] < sz[v]) swap(u, v);
		ops.push( operation(u, sz[u], v, m2[v], m, stat) );
		sz[u] += sz[v];
		rep[v] = u;
		m2[v] = 1 ^ ma ^ mb;
	}

	bool can_insert(int m, bool stat, bool unisci = 0) {
		int a = edge[m].a, b = edge[m].b;
		auto [u, ma] = findrep(a);
		auto [v, mb] = findrep(b);

		if(u != v) {
			if(unisci) unite(u, v, ma, mb, m, stat);
			return 1;
		}
		else {
			if(ma ^ mb) {
				if(unisci) unite(u, v, ma, mb, m, stat);
				return 1;
			}
			return 0;
		}
	}

	void rollback(int K = 1) {
		while(K--) {
			//undo the top of the stack
			operation undo = ops.top(); ops.pop();
			if(undo.stat == 0) cnt_a--;
			if(undo.V.empty()) continue;

			sz[ undo(0) ] = undo(1);
			rep[ undo(2) ] = undo(2);
			m2[ undo(2) ] = undo(3);
		}
	}

	void ribalta() {
		queue<int> q;

		while(!ops.empty()) {
			q.push(ops.top().m);
			rollback();
		}

		while(!q.empty()) {
			int m = q.front();
			q.pop();
			can_insert(m, 0, 1);
		}
	}

	void popfront() {
		//poppa il primo a.
		stack<int> sa, sb;

		if(cnt_a == 0) {
			ribalta();
		}

		int a = 0, b = 0;
		while(a <= b && cnt_a > 0) {
			operation undo = ops.top();
			rollback();
			if(undo.stat == 1) 	sb.push(undo.m), b++;
			else				sa.push(undo.m), a++;
		}

		while(!sb.empty()) {
			can_insert(sb.top(), 1, 1);
			sb.pop();
		}

		while(!sa.empty()) {
			can_insert(sa.top(), 0, 1);
			sa.pop();
		}
		rollback();
	}


	void check() {
		if(!DBG) return;
		infon("CHEKING...");
		info("rep: "); for(int i: rep) cout << i _""; cout << "\n";
		info("sz: "); for(int i: sz) cout << i _""; cout << "\n";
		info("m2: "); for(bool i: m2) cout << i _""; cout << "\n";
		infon("------------------------------");
	}
};


signed main() {
	get();

	rollback_DSU dsu;
	ll ans = 0;

	int l = 0;
	for(int r=0; r<M; r++) {
		infon(" ======= r = %d", r);
		dsu.check();
		while(!dsu.can_insert(r, 1, 1)) {
			dsu.popfront();
			l++;
			dsu.check();
		}
		infon("min l for r=%d is %d", r, l);
		ans += (r-l+1);
	}
	cout << ans << "\n";
}

/*
16 15
1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 10 10 11 11 12 12 13 13 14 14 15
15 16
*/

