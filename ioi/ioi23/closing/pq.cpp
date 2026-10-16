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
#define readv(v) do{ for(auto &i: v) cin >> i; }while(0)
#ifdef LOCAL
bool DBG = 1;
#define infor(...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)
#else
bool DBG = 0;
#define infor(...)
#define infof(...)
#endif
mt19937 timmy_loves_gambling(73);

#include "closing.h"

struct Dt {
    int n;
    int t;
    ll p;

    bool operator<(const Dt &other) const {
        return p > other.p;
    }

    Dt(int a, int b, ll c) {
        n = a, t = b, p = c;
    }
};

vec<vec<pll>> G;
vec<vec<int>> rea;
vec<int> C;

int max_score(int N, int X, int Y, long long K, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
    G = vector(N, vec<pll>());
    rea = vector(2, vec<int>(N, 0));
    C = vec<int>(N);

    for(int i = 0; i<N-1; i++) {
        G[U[i]].push_back({V[i], W[i]});
        G[V[i]].push_back({U[i], W[i]});
    }

    auto dfs = [&](int v, int f, vec<ll> &dist, auto &&self) -> void {
        for(auto [u, w]: G[v]) {
            if(u == f) continue;
            dist[u] = dist[v] + w;
            self(u, v, dist, self);
        }
        return;
    };

    vec<vec<ll>> dist = vector(2, vec<ll>(N));
    dfs(X, -1, dist[0], dfs);
    dfs(Y, -1, dist[1], dfs);

    priority_queue<Dt> pq;
    pq.push(Dt(X, 0, 0));
    pq.push(Dt(Y, 1, 0));

    int ans = 0;

    while(!pq.empty()) {
        auto [v, t, d] = pq.top();
        pq.pop();

        if(rea[t][v]) continue;
        C[v] += d;
        rea[t][v] = 1;

        infof("v = %d, t = %d, d = %d, C[v] = %d", v, t, d, C[v]);

        K -= d;
        if(K < 0) break;
        ans++;

        int t2 = !t;

        for(auto [u, w]: G[v]) {
            if(rea[t][u] == 0) {
                pq.emplace(u, t, dist[t][u]-C[u]);
            }

            if(rea[t2][v] == 0 && rea[t2][u] == 1) {
                pq.emplace(v, t2, dist[t2][v]-C[v]);
            }

            if(rea[t2][v] == 1 && rea[t2][u] == 0) {
                pq.emplace(u, t2, dist[t2][u]-C[u]);
            }
        }
    }

    return ans;
}

#ifdef EVAL
int main()
{
    int Q;
    assert(1 == scanf("%d", &Q));

    std::vector<int> N(Q), X(Q), Y(Q);
    std::vector<long long> K(Q);
    std::vector<std::vector<int>> U(Q), V(Q), W(Q);

    for (int q = 0; q < Q; q++)
    {
        assert(4 == scanf("%d %d %d %lld", &N[q], &X[q], &Y[q], &K[q]));

        U[q].resize(N[q] - 1);
        V[q].resize(N[q] - 1);
        W[q].resize(N[q] - 1);
        for (int i = 0; i < N[q] - 1; ++i)
        {
            assert(3 == scanf("%d %d %d", &U[q][i], &V[q][i], &W[q][i]));
        }
    }
    fclose(stdin);

    std::vector<int> result(Q);
    for (int q = 0; q < Q; q++)
    {
        result[q] = max_score(N[q], X[q], Y[q], K[q], U[q], V[q], W[q]);
    }

    for (int q = 0; q < Q; q++)
    {
        printf("%d\n", result[q]);
    }
    fclose(stdout);

    return 0;
}
#endif
