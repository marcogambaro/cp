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
vec<pii> V;
vec<vec<int>> G;

vec<int> ma, mi;
vec<int> leaf; // in how many ways this thing can be seen as a leaf
vec<array<int, 3>> inv;
vec<vec<int>> check_l, check_r;

int nleaf = 0;
int l = 0, r = -1;

void expand() {
    r++;
    if(leaf[r]) nleaf--;
    for(int id: check_r[r]) {
        auto [i, a, v] = inv[id];

        if(l <= i && a <= r)
            if(leaf[v]++ == 0 && (v < l || v > r)) nleaf++;
    }
}

void contract() {
    if(leaf[l]) nleaf++;
    for(int id: check_l[l]) {
        auto [i, a, v] = inv[id];

        if(l <= i && a <= r)
            if(--leaf[v] == 0 && (v < l || v > r)) nleaf--;
    }
    l++;
}

void dfs(int v, int f) {
    ma[v] = mi[v] = v;
    for(int u: G[v]) {
        if(u == f) continue;
        dfs(u, v);
        ma[v] = max(ma[v], ma[u]);
        mi[v] = min(mi[v], mi[u]);
    }
}

void calc(int v, int f, int mfa, int mfi) {
    vec<pii> d;

    for(int u: G[v]) {
        if(u == f) continue;
        d.emplace_back(ma[u], mi[u]);
    }
    if(f != -1) d.emplace_back(mfa, mfi);

    pii pa = {-1, -1};
    pii pi = {1e9, 1e9};

    if(d.size() == 1) {
        leaf[v] = 1;
        nleaf++;
    }
    else {
        for(auto [a, i]: d) {
            if(a > pa.se) swap(a, pa.se);
            if(pa.se > pa.fi) swap(pa.se, pa.fi);

            if(i < pi.se) swap(i, pi.se);
            if(pi.se < pi.fi) swap(pi.se, pi.fi);
        }

        for(auto [a, i]: d) {
            int aa = pa.fi;
            int ii = pi.fi;
            if(a == pa.fi) aa = pa.se;
            if(i == pi.fi) ii = pi.se;

            if(ii < v && aa > v) continue;
            check_l[ii].push_back(inv.size());
            check_r[aa].push_back(inv.size());
            inv.push_back({ii, aa, v});
        }
    }

    for(int u: G[v]) {
        if(u == f) continue;
        int aa = pa.fi;
        int ii = pi.fi;
        if(ma[u] == pa.fi) aa = pa.se;
        if(mi[u] == pi.fi) ii = pi.se;

        calc(u, v, max(aa, v), min(v, ii));
    }
}

int solve(int N, int D, std::vector<int> C, std::vector<int> A, std::vector<int> B) {
    if(N == 1) return 0;
    ::N = N;
    V.resize(N);

    for(int i=0; i<N; i++) V[i] = {i, C[i]};
    sort(all(V), [&](pii &a, pii &b){return a.se < b.se;});

    vec<int> posv(N);
    for(int i=0; i<N; i++) {
        posv[V[i].fi] = i;
    }

    G.resize(N);
    for(int i=0; i<N-1; i++) {
        G[posv[A[i]]].push_back(posv[B[i]]);
        G[posv[B[i]]].push_back(posv[A[i]]);
    }

    ma = mi = leaf = vec<int>(N);
    check_l = check_r = vector(N, vec<int>());
    dfs(0, -1);
    calc(0, -1, -1, -1);

    // fake Mo
    int ans = 1e9;

    while(l < N) {
        while(r < N-1 && V[r+1].se <= V[l].se+D) expand();
        ans = min(ans, nleaf);
        infof("l = {}, r = {}, nleaf = {}", l, r, nleaf);
        contract();
    }

    return (ans+1)/2;
}

#ifdef LOCAL
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int n, d;
    std::cin >> n >> d;
    std::vector<int> c(n);
    for (auto& e : c) std::cin >> e;
    std::vector<int> p(n - 1), q(n - 1);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> p[i] >> q[i];
    }

    std::cout << solve(n, d, c, p, q) << "\n";
}
#endif
