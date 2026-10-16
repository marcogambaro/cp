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

#include "aplusb.h"

vec<int> a, b;

void initialize(vector<int> A, vector<int> B) {
    a = A, b = B;
}

int answer_question(int i, int j) {
    return a[i] + b[j];
}

#ifdef LOCAL
int main() {
  int N;
  assert(1 == scanf("%d", &N));
  std::vector<int> A(N), B(N);
  for (int k = 0; k < N; k++)
    assert(1 == scanf("%d", &A[k]));
  for (int k = 0; k < N; k++)
    assert(1 == scanf("%d", &B[k]));

  int Q;
  assert(1 == scanf("%d", &Q));
  std::vector<int> i(Q), j(Q);
  for (int k = 0; k < Q; k++)
    assert(2 == scanf("%d %d", &i[k], &j[k]));

  fclose(stdin);

  std::vector<int> S(Q);

  initialize(A, B);

  for (int k = 0; k < Q; k++)
    S[k] = answer_question(i[k], j[k]);

  for (int k = 0; k < Q; k++)
    printf("%d\n", S[k]);

  fclose(stdout);

  return 0;
}
#endif
