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

constexpr int LOG = 20;

vec<vec<int>> G;
vec<int> tin, tout, depth;
vec<vec<int>> tour;

void dfs(int v, int f) {
    static int time = 0;
    tin[v] = time;
    tour[0][time++] = v;

    for(int u: G[v]) {
        if(u == f) continue;
        depth[u] = depth[v]+1;
        dfs(u, v);
        tour[0][time++] = v;
    }
    tout[v] = time;
}

int high(int a, int b) {
    if(depth[a] < depth[b]) return a;
    return b;
}

bool anc(int p, int f) {
    return tin[p] <= tin[f] && tout[f] <= tout[p];
}

int lca(int l, int r) {
    l = tin[l], r = tin[r];
    if(l > r) swap(l, r);
    r++;

    int s = 31 - __builtin_clz(r-l);
    return high(tour[s][l], tour[s][r - (1 << s)]);
}

int dist(int a, int b) {
    int c = lca(a, b);
    return depth[a] + depth[b] - 2*depth[c];
}

vec<vec<array<int, 3>>> Qs;
vec<vec<int>> dp;
vec<pii> par;

void solve(int v, int f) {
    vec<int> ch;

    for(int u: G[v]) {
        if(u == f) continue;
        ch.push_back(u);
        solve(u, v);
    }

    int C = ch.size();
    dp[v].resize(1<<C);

    int pu = 0;
    for(int u: ch) {
        Qs[v].push_back({u, v, 0});
        par[u] = {v, 1<<pu};
        pu++;
    }

    for(auto [a, b, c]: Qs[v]) {
        pii pa = {a, 0};
        pii pb = {b, 0};

        while(pa.fi != v) {
            c += dp[pa.fi][pa.se];
            pa = par[pa.fi];
        }
        while(pb.fi != v) {
            c += dp[pb.fi][pb.se];
            pb = par[pb.fi];
        }

        int mc = pa.se + pb.se;

        for(int m = mc; m < (1<<C); m = (m+1)|mc) {
            dp[v][m-mc] = max(dp[v][m-mc], dp[v][m]+c);
        }
    }
}

signed main() {
    int N, M; cin >> N >> M;
    int totc = 0;
    vec<array<int, 3>> V;

    G.resize(N);
    tin = tout = depth = vec<int>(N);
    tour = vector(LOG, vec<int>(N*2));

    for(int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        totc += c;
        if(c == 0) {
            G[a].push_back(b);
            G[b].push_back(a);
        }
        else {
            V.push_back({a, b, c});
        }
    }

    dfs(0, -1);

    for(int i = 1; i < LOG; i++) {
        for(int l = 0; l + (1 << i) <= 2*N; l++) {
            tour[i][l] = high(tour[i-1][l], tour[i-1][l + (1 << (i-1))]);
        }
    }

    Qs.resize(N);
    dp.resize(N);
    par.resize(N);
    for(auto [a, b, c]: V) {
        if(dist(a, b)%2 == 1) continue;
        Qs[lca(a, b)].push_back({a, b, c});
    }

    solve(0, -1);
    cout << totc-dp[0][0] << lf;
}
