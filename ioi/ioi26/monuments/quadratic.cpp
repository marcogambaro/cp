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

#include "monuments.h"

void chmin(ll &a, ll b) {
    a = min(a, b);
}

long long get_cost(std::vector<int> X, std::vector<int> P) {
    int N = X.size();
    vec<int> stat(N, 1);
    for(int i: P) stat[i] = 0;

    map<int, queue<int>> mp;
    for(int i=0; i<N; i++) {
        if(stat[i]) continue;

        if(X[i] == 0) stat[i] = -1;
        else if(mp[-X[i]].size()) {
            stat[i] = stat[mp[-X[i]].front()] = -1;
            mp[-X[i]].pop();
        }
        else mp[X[i]].push(i);
    }

    vec<int> v0, v1;

    for(int i=0; i<N; i++) {
        if(stat[i] == 0) v0.push_back(X[i]);
        else if(stat[i] == 1) v1.push_back(X[i]);
    }
    sort(all(v0), [&](int i, int j){return abs(i) > abs(j);});
    // sort(all(v1));
    int n0 = v0.size();
    int n1 = v1.size();

    if(n0 > n1) return -1;

    // dp[top (in absolute value) chosen fragile][pairs of movable]
    vector dp = vector(n0+1, vec<ll>(n1/2+2, 1e18));
    dp[0][0] = 0;
    ll ans = 1e18;

    int S = 0, s = 0;
    for(int i = 0; i <= n0; i++) {
        for(int j = 0; i + 2*j <= n1; j++) {
            if(i > 0) {
                if(v0[i-1] > 0) chmin(dp[i][j], dp[i-1][j] + abs(v0[i-1]+v1[j+S-1]));
                else            chmin(dp[i][j], dp[i-1][j] + abs(v0[i-1]+v1[n1-j-s]));
            }

            if(j > 0) chmin(dp[i][j], dp[i][j-1] + abs(v1[j+S-1]+v1[n1-j-s]));

            if(i == n0 && i+2*j == n1)   chmin(ans, dp[i][j]);
            if(i == n0 && i+2*j == n1-1) chmin(ans, dp[i][j] + abs(v1[S+j]));
        }

        if(i < n0) v0[i] > 0 ? S++ : s++;
    }

    //infof("{}", dp);
    return ans;
}

#ifdef LOCAL
int main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));

  std::vector<int> X(N);
  for (int i = 0; i < N; i++) {
    assert(1 == scanf("%d", &X[i]));
  }

  std::vector<int> P(M);
  for (int i = 0; i < M; i++) {
    assert(1 == scanf("%d", &P[i]));
  }
  fclose(stdin);

  long long res = get_cost(X, P);

  printf("%lld\n", res);
  fclose(stdout);
  return 0;
}
#endif
