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

#include "classroom.h"

vec<int> beep(int i, int r) {
    if(r%3 == 0)      return {i, 63};
    else if(r%3 == 1) return {63, i};
    else if(r%3 == 2) return {i, 62};
}

int getx(vec<int> v) {
    if(v.empty()) return -1;
    if(v.size() == 1) return v[0];
    if(v[0] == 63 || v[1] == 63) return v[0]^v[1]^63;
    if(v[1] == 62)   return v[0]^v[1]^62;
    return v[0];
}

int getk(vec<int> v) {
    if(v.size() < 2) return -1;
    return getx(v)^v[0]^v[1];
}

vec<int> deduce(int N, int R, vec<vec<int>> A) {
    vec<bool> alive(N);
    vec<int> v(N, -1);

    for(int i=0; i<N; i++) {
        int x = getx(A[i]);
        int k = getk(A[i]);

        if(x == -1) continue;

        if(A[i] == beep(x, R-1)) alive[x] = 1;

        if(k < 62 && k > -1) v[x] = k;
        else if(k == -1) {
            v[i] = R-2;
            v[x] = R-1;
        }
    }

    for(int i=0; i<N; i++) {
        if(v[i] != -1) continue;
        if(alive[i]) v[i] = R;
        else         v[i] = R-1;
    }

    return v;
}

vector<vector<int>> process_step(int N, int M, int R, vector<int> T, vector<vector<int>> A) {
    vec<vec<int>> ans = A;
    vec<int> t(N);
    for(int i: T) t[i]=1;

    if(R == 0) {
        for(int i=0; i<N; i++) {
            if(t[i]) continue;
            ans[i] = beep(i, 0);
        }
        return ans;
    }

    vec<int> v = deduce(N, R, A);

    vec<int> fake(N, -1);
    vec<int> used(N);
    for(int i=0; i<N; i++) {
        int x = getx(A[i]);
        int k = getk(A[i]);
        if(x == -1) continue;

        if(A[i] == beep(x, R) && t[x]) {
            fake[x] = i;

            // search for 2ago that points to 1ago
            bool success = 0;
            for(int j=0; j<N && !success; j++) {
                if(v[j] != R-2 || used[j]) continue;
                for(int k=0; k<N && !success; k++) {
                    int xk = getx(A[k]);
                    if(xk != j || v[k] != R-1 || used[k]) continue;
                    //found!
                    cerr << "YAAAAAAAARRR\n";
                    ans[k] = A[k];
                    ans[j] = {x};
                    used[j] = used[k] = 1;
                    success = 1;
                }
            }
            assert(success);
        }
    }

    for(int i=0; i<N; i++) {
        if(used[i] || t[i]) continue;
        if(v[i] == R)  ans[i] = beep(i, R);
        else           ans[i] = {i, v[i]};
    }

    return ans;
}

vector<int> determine_steps(int N, int M, vector<vector<int>> A) {
    vec<int> ans = deduce(N, M, A);
    for(int &i: ans) if(i == M) i = -1;
    return ans;
}

#ifdef LOCAL
int main() {
  int T;
  assert(1 == scanf("%d", &T));

  for (int t = 0; t < T; ++t) {
    int N, M;
    assert(2 == scanf("%d%d", &N, &M));

    std::vector<int> Q(N);
    for (int i = 0; i < N; ++i) {
      assert(1 == scanf("%d", &Q[i]));
    }

    std::vector<int> P(N);
    for (int i = 0; i < N; ++i) {
      assert(1 == scanf("%d", &P[i]));
    }

    std::vector<std::vector<int>> A(N, std::vector<int>());
    int C = 0;
    for (int R = 0; R < M; ++R) {
      std::vector<int> T;
      for (int i = 0; i < N; ++i) {
        if (Q[i] == R) {
          T.push_back(i);
        }
      }

      std::vector<std::vector<int>> B = process_step(N, M, R, T, A);
      int K = (int)B.size();
      std::vector<int> L(K);
      for (int i = 0; i < K; ++i) {
        L[i] = (int)B[i].size();
        C = std::max(C, L[i]);
      }

      printf("%d\n", K);
      for (int i = 0; i < K; ++i) {
        printf("%d", L[i]);
        for (int j = 0; j < L[i]; ++j) {
          printf(" %d", B[i][j]);
        }
        printf("\n");
      }
      printf("\n");

      assert(K == (int)P.size());

      for (int i = 0; i < N; ++i) {
        A[P[i]] = B[i];
      }
    }

    std::vector<int> D = determine_steps(N, M, A);
    int H = (int)D.size();

    printf("%d %d\n", C, H);
    for (int i = 0; i < H; ++i) {
      printf("%d%c", D[i], " \n"[i == H - 1]);
    }
  }
  fclose(stdout);

  return 0;
}
#endif
