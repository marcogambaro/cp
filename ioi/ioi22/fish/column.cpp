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

#include "fish.h"

vec<vec<pll>> sfx;
int N, M;
vec<int> X, Y, W;

void calcsfx() {
    sfx.resize(N+1);
    for(int i = 0; i < M; i++) {
        sfx[X[i]].push_back({Y[i], W[i]});
    }

    for(int i = 0; i < N; i++) {
        sort(all(sfx[i]));
        for(int j = sfx[i].size()-2; j >= 0; j--)
            sfx[i][j].se += sfx[i][j+1].se;
    }
}

ll get(int i, int y) {
    pll p = {y, -1};
    int j = lower_bound(all(sfx[i]), p) - sfx[i].begin();
    if(j == sfx[i].size()) return 0;
    return  sfx[i][j].se;
}

ll get(int i, int yl, int yr) {
    return max(get(i, yl) - get(i, yr), 0LL);
}

void see(map<pii, ll> &mp) {
    if(!DBG) return;
    for(auto [p, k]: mp) {
        infof("[%d, %d] = %lld", p.fi, p.se, k);
    }
}

ll solve() {
    map<pii, ll> dp;

    dp[{-1, -1}] = 0;
    for(auto [y, x]: sfx[1])
        dp[{-1, y}] = 0;

    infof("----0:");
    see(dp);

    for(int i=1; i<N; i++) {
        map<pii, ll> dp2;

        vec<int> tc = {-1};

        for(auto [y, x]: sfx[i-1])
            tc.push_back(y);
        for(auto [y, x]: sfx[i+1])
            tc.push_back(y);


        for(auto [p, k]: dp) {
            auto [a, b] = p;

            for(int c: tc) {
                dp2[{b, c}] = max(dp2[{b, c}], k + get(i-1, b+1, max(a, c)+1));
            }
        }

        dp2.swap(dp);
        infof("----%d:", i);
        see(dp);
    }

    ll ans = 0;

    for(auto [p, k]: dp) {
        ans = max(ans, k + get(N-1, p.se+1, p.fi+1));
    }

    return ans;
}

long long max_weights(int N, int M, vector<int> X, vector<int> Y, vector<int> W) {
    ::N = N;
    ::M = M;
    ::X.swap(X);
    ::Y.swap(Y);
    ::W.swap(W);

    calcsfx();
    return solve();
}

#ifndef EVAL
signed main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));

  std::vector<int> X(M), Y(M), W(M);
  for (int i = 0; i < M; ++i) {
    assert(3 == scanf("%d %d %d", &X[i], &Y[i], &W[i]));
  }

  long long result = max_weights(N, M, X, Y, W);
  printf("%lld\n", result);
  return 0;
}
#endif
