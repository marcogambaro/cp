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

#include "overtaking.h"

struct node {
    int l = 0, r = 0;
    ll lazy = -1;
    ll x = 0, y = 0;
};
vec<node> t(2);

int make() {
    t.emplace_back();
    return t.size()-1;
}

void push(int v, ll l, ll m, ll r) {
    if(t[v].l == 0) {
        t[v].l = make();
        t[v].r = make();

        t[t[v].l].x = l;
        t[t[v].l].y = m-1;
        t[t[v].r].x = m;
        t[t[v].r].y = r-1;
    }

    if(t[v].lazy != -1) {
        t[t[v].l].x = t[t[v].l].y = t[t[v].l].lazy = t[v].lazy;
        t[t[v].r].x = t[t[v].r].y = t[t[v].r].lazy = t[v].lazy;
    }
    t[v].lazy = -1;
}

void pull(int v) {
    t[v].x = min(t[t[v].l].x, t[t[v].r].x);
    t[v].y = max(t[t[v].l].y, t[t[v].r].y);
}

void upd(int v, ll l, ll r, ll kl, ll kr) {
    if(t[v].x >= kr || t[v].y < kl) return;
    if(kl <= t[v].x && t[v].y <= kr) {
        t[v].lazy = kr;
        t[v].x = t[v].y = kr;
        return;
    }

    ll m = (l+r)/2;
    push(v, l, m, r);
    upd(t[v].l, l, m, kl, kr);
    upd(t[v].r, m, r, kl, kr);
    pull(v);
}

ll get(int v, ll l, ll r, ll q) {
    if(r-l == 1) return t[v].x;
    ll m = (l+r)/2;
    push(v, l, m, r);
    if(q < m) return get(t[v].l, l, m, q);
    else      return get(t[v].r, m, r, q);
}

constexpr ll MAXT = 1e18 + 7;
ll add;

void init(int L, int N, vector<long long> T, vector<int> W, int X, int M, vector<int> S) {
    vec<vec<ll>> dp(M, vec<ll>(N));

    t[1].x = 0;
    t[1].y = MAXT - 1;
    add = (ll)X * L;

    vec<int> P;

    for(int i = 0; i < N; i++) {
        if(W[i] <= X) continue;
        dp[0][i] = T[i];
        P.push_back(i);
    }

    sort(all(P), [&](int i, int j){
        if(dp[0][i] != dp[0][j]) return dp[0][i] < dp[0][j];
        return W[i] < W[j];
    });

    for(int s = 1; s < M; s++) {
        ll t = 0;

        for(int i: P) {
            t = max(t, dp[s-1][i] + (ll)W[i] * (S[s] - S[s-1]));
            dp[s][i] = t;
        }

        sort(all(P), [&](int i, int j){
            if(dp[s][i] != dp[s][j]) return dp[s][i] < dp[s][j];
            return W[i] < W[j];
        });
    }

    for(int s = 1; s < M; s++) {
        sort(all(P), [&](int i, int j){
            if(dp[s-1][i] != dp[s-1][j]) return dp[s-1][i] > dp[s-1][j];
            return W[i] > W[j];
        });

        infof("-----------");
        for(int i: P) {
            infof("kl = %lld, kr = %lld", dp[s-1][i]+1 - (ll)S[s-1]*X, dp[s][i] - (ll)S[s]*X);
            upd(1, 0, MAXT, dp[s-1][i]+1 - (ll)S[s-1]*X, dp[s][i] - (ll)S[s]*X);
        }
    }
}

long long arrival_time(long long Y) {
    return get(1, 0, MAXT, Y) + add;
}

#ifndef EVAL
int main()
{
    int L, N, X, M, Q;
    assert(5 == scanf("%d %d %d %d %d", &L, &N, &X, &M, &Q));
    std::vector<long long> T(N);
    for (int i = 0; i < N; i++)
        assert(1 == scanf("%lld", &T[i]));
    std::vector<int> W(N);
    for (int i = 0; i < N; i++)
        assert(1 == scanf("%d", &W[i]));
    std::vector<int> S(M);
    for (int i = 0; i < M; i++)
        assert(1 == scanf("%d", &S[i]));
    std::vector<long long> Y(Q);
    for (int i = 0; i < Q; i++)
        assert(1 == scanf("%lld", &Y[i]));

    fclose(stdin);

    init(L, N, T, W, X, M, S);
    std::vector<long long> res(Q);
    for (int i = 0; i < Q; i++)
        res[i] = arrival_time(Y[i]);

    for (int i = 0; i < Q; i++)
        printf("%lld\n", res[i]);
    fclose(stdout);
    return 0;
}
#endif
