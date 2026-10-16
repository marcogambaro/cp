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

vector<vector<int>> G;
int N;
ll ans;

struct LCA{
	vector<int> tin, depth;
	vector<vector<int>> table;
	vector<int> lg2;
	int time = 0;

	void dfs(int n, int f, int d) {
		tin[n] = time;
		table[0][time] = n;
		depth[n] = d+1;
		time++;

		for(int v: G[n]) {
			if(v == f) continue;
			dfs(v, n, d+1);
			table[0][time] = n;
			time++;
		}
	}

	int better(int v, int u) {
		if(depth[v] < depth[u]) return v;
		else return u;
	}

	LCA() {
		tin.resize(N);
		depth.resize(N);
		table = vector(LOG, vector<int>(N*2));
		lg2.resize(N*2+2);
		lg2[0] = lg2[1] = 0;
		for(int i=2; i<lg2.size(); i++)
			lg2[i] = lg2[i/2]+1;

		dfs(0, -1, 0);

		for(int i=1; i<LOG; i++) {
			int pw = 1<<i;
			for(int l=1; l+pw<=N*2; l++) {
				table[i][l] = better(table[i-1][l], table[i-1][l + pw/2]);
			}
		}
	}

	int find(int v, int u) {
		if(tin[v] > tin[u]) swap(v, u);
		int l = tin[v];
		int r = tin[u];
		int s = lg2[r - l +1];
		int pw = 1<<s;
		return better(table[s][l], table[s][r - pw + 1]);
	}

	int dist(int v, int u) {
		int k = find(v, u);
		return depth[v] + depth[u] - 2*depth[k];
	}
};


signed main(){	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);   
    
    cin >> N;
	G.resize(N);
	for(int i=0; i<N-1; i++) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	int TK = 6;
	vector<unordered_map<int, ll>> mp;

	auto dfs = [&](int v, int from, int t, int d, auto &&self) -> void {
		int bigc = -1;
		for(int u: G[v]) {
			if(u == from) continue;
			self(u, v, t, d+1, self);
			if(bigc == -1 || mp[bigc].size() < mp[u].size()) 
				bigc = u;
		}

		mp[v][d - t*v] = 1;
		
		if(bigc == -1) return;
		mp[v].swap(mp[bigc]);

		for(int u: G[v]) {
			if(u == from) continue;
			
			for(auto &[x, k]: mp[u]) {
				if(mp[v].count(2*d - x))
					ans += mp[v][2*d - x] * k;
			}

			for(auto &[x, k]: mp[u]) {
				mp[v][x] += k;
			}
		}
	};


	LCA lca;

	TK++;
	for(int i=0; i*TK<N; i++) {
		for(int j=i+1; j*TK + i*TK < N; j++) {
			if(lca.dist(i, j) % (i+j) == 0 && lca.dist(i, j)/(i+j) >= TK) 
				ans++;
		}
	}

    cout << ans << "\n";
}
