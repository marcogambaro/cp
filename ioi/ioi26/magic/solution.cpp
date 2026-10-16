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

#include "magic.h"

vector<int> Amina(std::vector<int> P) {
    int N = 256;
    vector<vector<int>> dp(N);

    for(int i=0; i<N; i++) {
        dp[i] = {i};

        for(int j=0; j<i; j++) {
            if(P[j] < P[i]) {
                if(dp[j].size() >= dp[i].size()) {
                    dp[i] = dp[j];
                    dp[i].push_back(i);
                }
            }
        }

        if(dp[i].size() == 16) {
            for(int j: dp[i]) P[j] = -1;
            return P;
        }
    }

    for(int i=0; i<N; i++) {
        dp[i] = {i};

        for(int j=0; j<i; j++) {
            if(P[j] > P[i]) {
                if(dp[j].size() >= dp[i].size()) {
                    dp[i] = dp[j];
                    dp[i].push_back(i);
                }
            }
        }

        if(dp[i].size() == 17) {
            for(int j: dp[i]) P[j] = -1;
            return P;
        }
    }
}

vector<int> Billura(std::vector<int> Q) {
    int N = 256;

    set<int> st;
    for(int i=1; i<=N; i++) st.insert(i);
    for(int i: Q) st.erase(i);

    if(st.size() == 16) {
        for(int i=0; i<N; i++) {
            if(Q[i] == -1) {
                Q[i] = *st.begin();
                st.erase(st.begin());
            }
        }
    }
    else {
        for(int i=0; i<N; i++) {
            if(Q[i] == -1) {
                Q[i] = *prev(st.end());
                st.erase(prev(st.end()));
            }
        }
    }

    return Q;
}

#ifdef LOCAL
int main() {
  int N;
  assert(1 == scanf("%d", &N));

  std::vector<int> P(N, 0);
  for (int i = 0; i < N; i++) {
    assert(1 == scanf("%d", &P[i]));
  }

  fclose(stdin);

  std::vector<int> Q = Amina(P);

  int S = (int)Q.size();
  printf("%d\n", S);
  for (int i = 0; i < S; i++) {
    printf("%d%c", Q[i], " \n"[i == S - 1]);
  }

  std::vector<int> B = Billura(Q);

  int T = (int)B.size();
  printf("%d\n", T);
  for (int i = 0; i < T; i++) {
    printf("%d%c", B[i], " \n"[i == T - 1]);
  }

  fclose(stdout);

  return 0;
}
#endif
