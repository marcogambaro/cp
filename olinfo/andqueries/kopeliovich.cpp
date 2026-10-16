// stolen from Bamber
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#define ff endl
#define lf "\n"
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 30;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

struct Kopeliovich {
    using adj_t = vector<int>;
    struct query_t {
        query_t(int l, int r, int u, int v): l(l), r(r), u(u), v(v) {}

        int l, r;
        int u, v;
    };

    static constexpr int LOG = 20;

    Kopeliovich(int N, int Q): ans(Q) {
        for(int lg = 0; lg < LOG; ++lg) {
            szs[lg].reserve(N);
            ccs[lg].reserve(N);
            intrs[lg].reserve(N);
            adjs[lg].reserve(N);
            Qss[lg].reserve(Q);
        }
    }

    void solve(
        const int N,
        int l,
        int r,
        const int d = 0,
        ll cnt = 0
    ) {
        const auto &sz = szs[d];
        const auto &Qs = Qss[d];

        auto &cc = ccs[d];
        auto &intr = intrs[d];
        auto &adj = adjs[d];

        auto &nsz = szs[d + 1];
        auto &nQs = Qss[d + 1];

        cc.resize(N);
        intr.resize(N);
        adj.resize(N);

        for(int i = 0; i < N; ++i) {
            cc[i] = -1;
            intr[i] = 0;
            adj[i].clear();
        }

        nsz.clear();
        nQs.clear();

        infof("======= solve(%d, %d, %d, Qs, sz, %lld) =======", N, l, r, cnt);
        infor("... sz =");
        for(auto x: sz) {
            infor(" %d", x);
        }
        infof("");

        infof("... Qs = {");
        for(auto [ql, qr, u, v]: Qs) {
            infof("...   [%d, %d) | %d -- %d", ql, qr, u, v);
        }

        infof("... }\n");

        for(const auto &qry: Qs) {
            auto [ql, qr, u, v] = qry;

            if(ql <= l && qr >= r) {
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
            } else if(ql < r && qr > l) {
                intr[u] = intr[v] = 1;
                nQs.emplace_back(qry);
            }
        }

        auto get_ccs = [&](int v, auto &&get_ccs) -> pii {
            cc[v] = nsz.size();

            pii ret = {sz[v], intr[v]};
            auto &[vsz, vintr] = ret;

            for(auto u: adj[v]) {
                if(cc[u] >= 0) continue;

                auto [usz, uintr] = get_ccs(u, get_ccs);

                vsz += usz;
                vintr |= uintr;
            }

            return {vsz, vintr};
        };

        for(int i = 0; i < N; ++i) {
            if(cc[i] >= 0) continue;

            auto [isz, iintr] = get_ccs(i, get_ccs);

            if(iintr) {
                nsz.emplace_back(isz);
            } else {
                cnt += (ll)isz * (isz - 1) / 2;
            }
        }

        int n = nsz.size(), q = nQs.size();
        if(n == 0) {
            for(; l < r; ++l) {
                ans[l] = cnt;
            }

            return;
        }

        for(auto &[ql, qr, u, v]: nQs) {
            u = cc[u];
            v = cc[v];

            assert(u != v);
        }


        int m = (l + r) / 2;
        solve(n, l, m, d + 1, cnt);
        solve(n, m, r, d + 1, cnt);
    }

    vector<ll> ans;

    array<vector<int>, LOG> szs;
    array<vector<int>, LOG> ccs;
    array<vector<bool>, LOG> intrs;
    array<vector<adj_t>, LOG> adjs;
    array<vector<query_t>, LOG> Qss;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    const vector<int> sz(N, 1);
    array<vector<Kopeliovich::query_t>, LOG> Qs;

    array<map<pii, int>, LOG> st;

    for(int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;

        if(u > v) swap(u, v);

        for(int lg = 0; lg < LOG; ++lg, w >>= 1) {
            if(!(w&1)) continue;

            st[lg][{u, v}] = 0;
        }
    }

    int Q; cin >> Q;
    for(int q = 1; q <= Q; ++q) {
        int u, v, w; cin >> u >> v >> w;

        if(u > v) swap(u, v);

        for(int lg = 0; lg < LOG; ++lg, w >>= 1) {
            auto it = st[lg].find({u, v});

            if(w&1) {
                if(it == st[lg].end()) {
                    st[lg][{u, v}] = q;
                }

                continue;
            } else {
                if(it == st[lg].end()) continue;

                Qs[lg].emplace_back(it->second, q, u, v);
                st[lg].erase(it);
            }
        }
    }

    for(int lg = 0; lg < LOG; ++lg) {
        for(const auto &[ed, l]: st[lg]) {
            auto [u, v] = ed;

            Qs[lg].emplace_back(l, Q + 1, u, v);
        }
    }

    vector<ll> ans(Q + 1);
    Kopeliovich solver(N, Q + 1);

    for(int lg = 0; lg < LOG; ++lg) {
        infof("===========================================");
        infof("============= solving lg = %2d =============", lg);
        infof("===========================================");

        solver.szs[0] = sz;
        solver.Qss[0] = Qs[lg];

        solver.solve(N, 0, Q + 1);

        for(int i = 0; i <= Q; ++i) {
            ans[i] += solver.ans[i] << lg;
        }

        infof("\n\n");
    }

    for(auto x: ans) {
        cout << x << " ";
    }

    cout << lf;
}
