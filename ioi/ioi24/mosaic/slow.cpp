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

#include "mosaic.h"

vec<long long> mosaic(vec<int> X, vec<int> Y, vec<int> T, vec<int> B, vec<int> L, vec<int> R) {
    int N = X.size();
    int Q = T.size();

    vec<vec<int>> tb(N+1, vec<int>(N+1));
    for(int i=0; i<N; i++) tb[0][i] = X[i];
    for(int i=0; i<N; i++) tb[i][0] = Y[i];

    for(int i=1; i<N; i++) for(int j=1; j<N; j++) {
        tb[i][j] = (tb[i-1][j] == tb[i][j-1] && tb[i-1][j] == 0);
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cerr << tb[i][j] << " ";
        }
        cerr << lf;
    }

    for(int i=0; i<N; i++) for(int j=1; j<=N; j++) tb[i][j] += tb[i][j-1];
    for(int i=0; i<N; i++) for(int j=1; j<=N; j++) tb[j][i] += tb[j-1][i];

    vec<ll> ans(Q);

    for(int i=0; i<Q; i++) {
        ans[i] = tb[B[i]][R[i]];
        if(T[i] > 0) ans[i] -= tb[T[i]-1][R[i]];
        if(L[i] > 0) ans[i] -= tb[B[i]][L[i]-1];
        if(T[i] > 0 && L[i] > 0) ans[i] += tb[T[i]-1][L[i]-1];
    }

    return ans;
}

#ifndef EVAL
int main() {
  int N;
  uniform_int_distribution<int> dis(0, 1);

  assert(1 == scanf("%d", &N));
  std::vector<int> X(N), Y(N);
  for (int i = 0; i < N; i++)
    X[i] = dis(timmy_loves_gambling);
  for (int i = 0; i < N; i++)
    Y[i] =dis(timmy_loves_gambling);
  int Q;
  assert(1 == scanf("%d", &Q));
  std::vector<int> T(Q), B(Q), L(Q), R(Q);
  for (int k = 0; k < Q; k++)
    assert(4 == scanf("%d%d%d%d", &T[k], &B[k], &L[k], &R[k]));
  fclose(stdin);

  std::vector<long long> C = mosaic(X, Y, T, B, L, R);

  int S = (int)C.size();
  for (int k = 0; k < S; k++)
    printf("%lld\n", C[k]);
  fclose(stdout);

  return 0;
}
#endif
