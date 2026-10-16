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

    Dt() {
        n = -1;
        p = 1e18;
    }
};

vec<vec<pll>> G;
vec<vec<int>> rea;
vec<vec<int>> can;
vec<vec<ll>> dist;
vec<int> C;

int goofygreedy(int N, int X, int Y, long long K) {
    rea = can = vector(2, vec<int>(N, 0));
    C = vec<int>(N);

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

        //infof("v = %d, t = %d, d = %d, C[v] = %d", v, t, d, C[v]);

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

int max_score(int N, int X, int Y, long long K, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
    G = vector(N, vec<pll>());
    rea = can = vector(2, vec<int>(N, 0));
    dist = vector(2, vec<ll>(N));
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

    dfs(X, -1, dist[0], dfs);
    dfs(Y, -1, dist[1], dfs);

    ll k = 0;
    ll xy = dist[0][Y];
    infof("XY = %lld", xy);

    priority_queue<Dt> q1, q2;
    int ans = 0;

    for(int i = 0; i < N; i++) {
        if(dist[0][i] + dist[1][i] == xy) {
            int t = dist[0][i] < dist[1][i] ? 0 : 1;
            int t2 = !t;
            ans++;

            k += dist[t][i];
            rea[t][i] = 1;

            q1.emplace(i, t2, dist[t2][i] - dist[t][i]);
        }
        else {
            ll c1 = min(dist[0][i], dist[1][i]);
            ll c2 = max(dist[0][i], dist[1][i]) - c1;

            if(c2 > c1) {
                int t = dist[0][i] < dist[1][i] ? 0 : 1;
                q1.emplace(i, t, c1);
                q1.emplace(i, !t, c2);
            }
            else {
                q2.emplace(i, -1, c1+c2);
                // int t = dist[0][i] < dist[1][i] ? 0 : 1;
                // q1.emplace(i, t, c1);
            }
        }
    }

    if(k > K) return goofygreedy(N, X, Y, K);

    while(1) {
        Dt d10, d11;
        Dt d2;

        while(!q1.empty()) {
            Dt d = q1.top();
            q1.pop();
            if(d.n == -1) continue;
            if(rea[d.t][d.n] == 0) {
                d10 = d;
                break;
            }
        }
        while(!q1.empty()) {
            Dt d = q1.top();
            q1.pop();
            if(d.n == -1) continue;
            if(rea[d.t][d.n] == 0) {
                d11 = d;
                break;
            }
        }
        while(!q2.empty()) {
            Dt d = q2.top();
            q2.pop();
            if(d.n == -1) continue;
            if(rea[0][d.n] == 0 && rea[1][d.n] == 0) {
                d2 = d;
                break;
            }
        }

        if(d10.n == -1 && d2.n == -1) break;

        if(d2.n == -1 || d10.p + d11.p < d2.p) {
            q1.push(d11);
            q2.push(d2);

            auto [v, t, p] = d10;

            if(k+p > K) continue;

            rea[t][v] = 1;
            k += p;
            ans++;

            infof("take %d with %d, cost = %lld", v, t, p);
        }
        else {
            q1.push(d10);
            q1.push(d11);

            auto [v, t, p] = d2;

            if(k+p > K) continue;
            rea[0][v] = rea[1][v] = 1;
            k += p;
            ans += 2;

            infof("ultra take %d, cost = %lld", v, p);
        }
    }

    return max(ans, goofygreedy(N, X, Y, K));
}

#ifdef LOCAL
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
