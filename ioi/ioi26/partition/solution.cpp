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

#include "partition.h"

struct DSU {
    vec<int> t, r;

    DSU(int N) {
        t.resize(N+1, -1);
        r.resize(N+1);
        iota(all(r), 0);
    }

    int rep(int v) {
        if(t[v] < 0) return v;
        return t[v] = rep(t[v]);
    }

    void unite(int a, int b) {
        if(a < 0 || a >= t.size() || b < 0 || b >= t.size()) return;
        a = rep(a), b = rep(b);
        if(a == b) return;
        if(t[a] > t[b]) swap(a, b);
        t[a] += t[b];
        r[a] = max(r[a], r[b]);
        t[b] = a;
    }

    int right(int v) {
        return r[rep(v)];
    }
};

vector<int> add_numbers(vector<int> A, int K, int M) {
    int N = A.size();
    sort(all(A));

    ll L = A.back()-1, R = 1e16;

    while(R-L > 1) {
        ll T = (L+R)/2;
        infof("trying with T = {}", T);

        ll t = 0;
        int k = 0;

        for(int i=0; i<N; i++) {
            if(t + A[i] <= T) t += A[i];
            else {
                t = A[i];
                k++;
            }
        }
        k++;

        if(k > K) L = T;
        else R = T;
    }

    ll T = R;
    cerr << "exited T = " << T << lf;

    vec<int> ans;
    int k = 0;
    ll t = 0;

    for(int i=0; i<N; i++) {
        if(t + A[i] <= T) t += A[i];
        else {
            if(t != T) {
                ans.push_back(T-t);
            }
            t = A[i];
            k++;
        }
    }

    while(k < K) {
        while(t < T) {
            ans.push_back(min((ll)M, T-t));
            t += min((ll)M, T-t);
        }
        k++;
        t = 0;
    }

    assert(ans.size() < K);
    return ans;
}

vector<int> find_partition(vector<int> A, int K) {
    reverse(all(A));
    int N = A.size();
    DSU dsu(N);

    ll T = accumulate(all(A), 0LL)/K;
    vec<int> ans(N);

    for(int k=0; k<K; k++) {
        int p = dsu.right(0);
        ll t = 0;

        while(t < T) {
            t += A[p];
            ans[p] = k;
            dsu.unite(p, p+1);

            int l=-1, r=N;
            while(r-l > 1) {
                int m = (l+r)/2;
                if(A[m] > T-t) l = m;
                else    r = m;
            }

            p = dsu.right(r);
        }
    }

    reverse(all(ans));
    return ans;
}

#ifdef LOCAL
int main() {
  int N, K, M;
  assert(3 == scanf("%d%d%d", &N, &K, &M));
  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &A[i]));
  }
  fclose(stdin);

  std::vector<int> C = add_numbers(A, K, M);

  std::vector<int> B = A;
  for (int x : C) {
    B.push_back(x);
  }
  std::sort(B.begin(), B.end());

  int S = (int)C.size();
  printf("%d\n", S);
  for (int i = 0; i < S; ++i) {
    printf("%d%c", C[i], " \n"[i + 1 == S]);
  }
  for (int i = 0; i < N + S; ++i) {
    printf("%d%c", B[i], " \n"[i + 1 == N + S]);
  }
  printf("\n");

  std::vector<int> P = find_partition(B, K);

  int L = (int)P.size();
  printf("%d\n", L);
  for (int i = 0; i < L; ++i) {
    printf("%d%c", P[i], " \n"[i + 1 == L]);
  }
  fclose(stdout);

  return 0;
}
#endif
