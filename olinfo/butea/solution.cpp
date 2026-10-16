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

bool triangle(int &a, int &b, int &c, int q) {
    return a <= q-a && b <= q-b && c <= q-c;
}

vec<int> depth, tin, tmid, tout, W, f1, f2, f, f1w, f2w, fw;
vec<vec<int>> tb;

int higher(int a, int b) {
    if(depth[a] < depth[b]) return a;
    return b;
}

int get_lca(int l, int r) {
    l = tin[l], r = tin[r];
    if(l > r) swap(l, r);
    r++;

    int s = 31 - __builtin_clz(r-l);
    return higher(tb[s][l], tb[s][r-(1<<s)]);
}

struct BIT {
    vec<int> t;
    stack<int> history;

    BIT(int N) {
        t.resize(N+5);
    }

    void add(int i) {
        i++;
        history.push(i);
        while(i < t.size()) {
            t[i]++;
            i += i&-i;
        }
    }

    int range(int l, int r) {
        int ans = 0;
        if(l > r) return 0;
        while(l) {
            ans -= t[l];
            l -= l&-l;
        }
        while(r) {
            ans += t[r];
            r -= r&-r;
        }
        return ans;
    }

    void clear() {
        while(history.size()) {
            int i = history.top();
            history.pop();
            while(i < t.size()) {
            t[i]--;
            i += i&-i;
        }
        }
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;
    vec<vec<pii>> G(N);
    depth = tin = tmid = tout = W = vec<int>(N);
    f1 = f2 = f = f1w = f2w = fw = vec<int>(N, -1);
    tb = vector(LOG, vector<int>(N*2));

    for(int i = 0; i < N-1; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        G[a].emplace_back(b, c);
        G[b].emplace_back(a, c);
    }

    vec<vec<int>> Qs(Q);
    vec<set<int>> Qnode(N);

    for(int i = 0; i < Q; i++) {
        int k; cin >> k;
        Qs[i].resize(k);
        for(auto &x: Qs[i]) {
            cin >> x;
            x--;
            Qnode[x].insert(i);
        }
    }

    int root;
    for(int i=0; i<N; i++) if(G[i].size() < 3) root = i;

    // find a suitable starting spot for each query while building lca
    vec<int> start(Q, -1);
    vec<map<int, int>> mp(N);

    auto dfs = [&](int v, int from, auto &&dfs) -> void {
        static int time = 0;
        tin[v] = time;
        tb[0][time++] = v;

        for(auto &[u, w]: G[v]) {
            if(u == from) continue;
            depth[u] = 1+depth[v];
            W[u] = w+W[v];
            dfs(u, v, dfs);
            if(tmid[v] == 0) tmid[v] = time;
            tb[0][time++] = v;
        }
        tout[v] = time;

        if(G[v].size() - (from != -1) == 2) {
            for(auto &[u, w]: G[v]) {
                if(u == from)        f[v] = u, fw[v] = w;
                else if(f1[v] == -1) f1[v] = u, f1w[v] = w;
                else                 f2[v] = u, f2w[v] = w;
            }

            map<int, int> &mp1 = mp[f1[v]], &mp2 = mp[f2[v]];
            if(mp1.size() < mp2.size()) mp2.swap(mp1);
            int a, b, c;

            // try queries and small to large
            for(auto &[q, bb]: mp2) {
                a = mp1[q];
                b = bb;
                c = Qs[q].size() - a - b - Qnode[v].count(q);

                if(triangle(a, b, c, (int)Qs[q].size())) start[q] = v;

                mp1[q] = Qs[q].size() - c;
            }

            // try queries that touch this node
            for(auto &q: Qnode[v]) {
                if(mp2.count(q)) continue;
                a = mp1[q];
                b = 0;
                c = Qs[q].size() - a - b - 1;

                if(triangle(a, b, c, (int)Qs[q].size())) start[q] = v;
                mp1[q]++;
            }

            mp1.swap(mp[v]);
        }
        else if(G[v].size() - (from != -1) == 1) {
            for(auto &[u, w]: G[v]) {
                if(u == from) f[v] = u, fw[v] = w;
                else          f1[v] = u, f1w[v] = w;
            }

            map<int, int> &mp1 = mp[f1[v]];
            int a, b, c;

            // try queries that touch this node
            for(auto &q: Qnode[v]) {
                a = mp1[q];
                b = 0;
                c = Qs[q].size() - a - b - 1;

                if(triangle(a, b, c, (int)Qs[q].size())) start[q] = v;

                mp1[q] = Qs[q].size()-c;
            }

            mp1.swap(mp[v]);
        }
        else {
            if(G[v].size()) f[v] = G[v][0].fi, fw[v] = G[v][0].se;
            for(auto &q: Qnode[v]) {
                if(Qs[q].size() == 1) start[q] = v;
                mp[v][q]++;
            }
        }
    };

    dfs(root, -1, dfs);
    for(int i=1; i<LOG; i++)
        for(int l=0; l+(1<<i) <= 2*N; l++)
            tb[i][l] = higher(tb[i-1][l], tb[i-1][l + (1<<(i-1))]);

    infof("root = {}", root);
    infof("preprocessing terminated. Starting points:");
    infof("{}", start);

    vec<int> vis(N, -1);
    BIT bit(2*N);

    for(int q = 0; q < Q; q++) {
        priority_queue<pll> pq;
        bit.clear();

        ll ans = 0;

        for(auto &u: Qs[q]) {
            int lca = get_lca(u, start[q]);
            ans += W[start[q]] + W[u] - 2*W[lca];
            bit.add(tin[u]);
        }

        pq.emplace(-ans, start[q]);
        ans = 0;
        vis[start[q]] = q;

        auto push = [&](int v, ll ww) -> void {
            int a = bit.range(tin[v]+1, tmid[v]);
            int b = bit.range(tmid[v], tout[v]);
            int k = Qnode[v].count(q);
            int c = Qs[q].size() - a - b - k;

            if(f[v] != -1 && vis[f[v]] != q) {
                vis[f[v]] = q;
                pq.emplace(ww - (a + b + k - c)*fw[v], f[v]);
            }
            if(f1[v] != -1 && vis[f1[v]] != q) {
                vis[f1[v]] = q;
                pq.emplace(ww - (b + c + k - a)*f1w[v], f1[v]);
            }
            if(f2[v] != -1 && vis[f2[v]] != q) {
                vis[f2[v]] = q;
                pq.emplace(ww - (a + c + k - b)*f2w[v], f2[v]);
            }
        };

        infof("+++++++++++\nquery {}", q);
        for(int i = 0; i < Qs[q].size(); i++) {
            auto [w, v] = pq.top();
            infof("- [{}, {}]", v, -w);
            pq.pop();
            ans -= w;
            push(v, w);
        }

        cout << ans << lf;
    }
}

