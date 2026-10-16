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

struct func {
    ll x0, p;

    func() {x0 = 1e18, p = 0;}

    func(ll a, ll b) {
        x0 = a, p = b;
    }

    ll operator()(ll k) {
        if(k <= p) return x0 - k*2;
        return x0 - p*2 - (k-p);
    }
};

struct node {
    int l=0, r=0;
    func f;
};

vec<node> t(2);

void add(int v, ll l, ll r, func f) {
    ll m = (l+r)/2;
    if(f(m) < t[v].f(m)) swap(f, t[v].f);

    if(r-l == 1) return;
    if(t[v].l == 0) {
        t[v].l = t.size();
        t[v].r = t.size()+1;
        t.emplace_back();
        t.emplace_back();
    }

    if(f(l) < t[v].f(l)) add(t[v].l, l, m, f);
    else                 add(t[v].r, m, r, f);
}

ll get(int v, ll l, ll r, ll q) {
    ll m = (l+r)/2;
    ll g = t[v].f(q);
    if(r-l == 1) return g;

    if(q < m) return min(g, get(t[v].l, l, m, q));
    else      return min(g, get(t[v].r, m, r, q));
}

vector<long long> shorten(int N, int M, int Q, vector<long long> K, vector<int> A, vector<int> B, vector<int> C) {
    vec<vec<pii>> G(N);

    for(int i = 0; i < M; i++) {
        G[A[i]].emplace_back(B[i], C[i]);
        G[B[i]].emplace_back(A[i], C[i]);
    }

    auto dij = [&](int n, vec<ll> &dist) {
        dist.resize(N, 1e18);
        dist[n] = 0;

        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.emplace(0, n);

        while(!pq.empty()) {
            auto [d, v] = pq.top();
            pq.pop();

            if(dist[v] < d) continue;

            for(auto [u, du]: G[v]) {
                if(dist[u] > d + du) {
                    dist[u] = d+du;
                    pq.emplace(d+du, u);
                }
            }
        }
    };

    vec<ll> d0, d1, d2;
    dij(0, d0);
    dij(1, d1);
    dij(2, d2);

    ll KMAX = 1e15 + 7;

    for(int i = 0; i < N; i++) {
        add(1, 0, KMAX, func(d0[i]+d1[i]*2+d2[i], d1[i]));
    }

    vec<ll> ans(Q);

    for(int i=0; i<Q; i++) {
        ans[i] = max(0LL, get(1, 0, KMAX, K[i]));
    }

    return ans;
}

#ifndef EVAL
int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<long long> K(Q);
    for (int i = 0; i < Q; i++) {
        cin >> K[i];
    }
    vector<int> A(M), B(M), C(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }

    vector<long long> soluzione = shorten(N, M, Q, K, A, B, C);
    cout << soluzione.size() << "\n";
    for (int i = 0; i < soluzione.size(); i++) {
        cout << soluzione[i] << ' ';
    }
    cout << "\n";
}
#endif

