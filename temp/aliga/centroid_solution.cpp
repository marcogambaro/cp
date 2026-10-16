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

int N;
ll ans=0;
vector<vector<int>> G, Gp, table;
vector<int> depth, tin, lg2;

void make_table0(int v, int from, int d) {
	static int time = 0;
	tin[v] = time;
	table[0][time++] = v;
	depth[v] = d;
	for(int u: G[v]) {
		if(u == from) continue;
		make_table0(u, v, d+1);
		table[0][time++] = v;
	}
}

int higher(int a, int b) {
	if(depth[a] < depth[b]) return a;
	return b;
}

void init_table() {
	for(int s=1; s<20; s++) {
		int pw = 1<<s;
		for(int l=0; l+pw<=2*N; l++)
			table[s][l] = higher(table[s-1][l], table[s-1][l +pw/2]);
	}
}

int get_lca(int a, int b) {
	a = tin[a];
	b = tin[b];
	if(a > b) swap(a, b);
	int s = lg2[b-a+1];
	int pw = 1 << s;
	return higher(table[s][a], table[s][b+1-pw]);
}

int dist(int a, int b) {
	int c = get_lca(a, b);
	return depth[a] + depth[b] - 2*depth[c];
}

vector<int> par, sz;

int decompose(int n, int pvc) {
	if(sz[n] == -1) return -1; //already decomposed

	auto dfs = [&](int v, int from, auto &&dfs) -> int {
		int k = 0;
		for(int &u: G[v]) {
			if(u == from) continue;
			if(sz[u] == -1) continue;
			k += dfs(u, v, dfs);
		}
		return sz[v] = k+1;
	};

	int ctr = -1;
	auto dfs2 = [&](int v, int from, auto &&dfs2) -> int {
		int k = 0;
		bool win = 1;
		for(int &u: G[v]) {
			if(u == from) continue;
			if(sz[u] == -1) continue;
			int x = dfs2(u, v, dfs2);
			if(x*2 > sz[n]) win = 0;
			k += x;
		}
		if(win && (sz[n]-1-k)*2 <= sz[n]) ctr = v;
		return sz[v];
	};

	dfs(n, -1, dfs);
	dfs2(n, -1, dfs2);
	assert(ctr != -1);
	infon("ctr=%d finished", ctr);
	par[ctr] = pvc;
	sz[ctr] = -1;
	for(int n2: G[ctr]) decompose(n2, ctr);
	return ctr;
}

vector<int> f;
stack<array<int, 2>> hs;
void rollback(int k=1) {
	while(k--) {
		auto [p, x] = hs.top();
		hs.pop();
		f[p] -= x;
	}
}

void solve(int v, int t) {
	auto dfs = [&](int v, vector<int> &s, auto &&self) -> void {
		s.push_back(v);
		for(int &u: Gp[v]) self(u, s, self);
	};

	int x = -0 + t*v + N+7;
	if(x>=0 && x<f.size()) {
		f[x]++;
		hs.push({x, 1});
	}

	for(int &u: Gp[v]) {
		vector<int> s;
		dfs(u, s, dfs);

		for(int &a: s) {
			x = dist(a, v) - t*a + N+7;
			if(x<0 || x>=f.size()) continue;
			ans += f[x];
		}

		for(int &a: s) {
			x = -dist(a, v) + t*a + N+7;
			if(x<0 || x>=f.size()) continue;
			f[x]++;
			hs.push({x, 1});
		}
	}

	rollback(hs.size());
}

void explore(int v, int t) {
	solve(v, t);
	for(int &u: Gp[v]) 
		explore(u, t);
}

signed main(){	
	ios::sync_with_stdio(false);
	cin.tie(nullptr); 
	
	lg2.resize(200000);
	lg2[1] = 0;
	for(int i=2; i<lg2.size(); i++)
		lg2[i] = lg2[i/2]+1;
    
    cin >> N;
	G.resize(N);
	Gp.resize(N);
	depth.resize(N);
	tin.resize(N);
	table = vector(20, vector<int>(N*2));
	par.resize(N);
	sz.resize(N);

	for(int i=0; i<N-1; i++) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	make_table0(0, -1, 0);
	init_table();
	int root = decompose(0, -1);
	infon("par:");
	if(dbg) for(int i: par) info("%d ", i); infon("");
	for(int i=0; i<N; i++)
		if(par[i] != -1) Gp[par[i]].push_back(i);

	int C = 18;
	f.resize(600000);

	for(int t=1; t<=C; t++)
		explore(root, t);

	C++;
	for(int i=0; i*C<=N; i++)
		for(int j=i+1; j*C+i*C<=N; j++) {
			int d = dist(i, j);
			if(d%(i+j)==0 && d/(i+j)>=C) ans++;
		}
	
	cout << ans << "\n";
}



