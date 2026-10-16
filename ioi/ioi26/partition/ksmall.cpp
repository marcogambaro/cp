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

vector<int> add_numbers(vector<int> A, int K, int M) {
    int N = A.size();
    sort(rall(A));

    priority_queue<pll, vec<pll>, greater<pll>> pq;

    for(int i=0; i<N; i++) {
        if(i < K) {
            pq.emplace(A[i], i);
        }
        else {
            auto [t, g] = pq.top();
            pq.pop();
            pq.emplace(t+A[i], g);
        }
    }

    vec<ll> v;
    while(!pq.empty()) {
        v.push_back(pq.top().fi);
        pq.pop();
    }

    vec<int> ans;
    for(int i=0; i<v.size(); i++) {
        if(v[i] != v.back())
            ans.push_back(v.back()-v[i]);
    }

    return ans;
}

vector<int> find_partition(vector<int> B, int K) {
    // consider only last 2K elements
    int N = B.size();

    priority_queue<pll, vec<pll>, greater<pll>> pq, pq2;
    vec<int> ans(N);

    for(int i=N-1; i>=2*K+1; i--) {
        if(pq.size() < K) {
            pq.emplace(B[i], pq.size());
            ans[i] = pq.size()-1;
        }
        else {
            auto [t, g] = pq.top();
            pq.pop();
            pq.emplace(t+B[i], g);
            ans[i] = g;
        }
    }
    pq2 = pq;

    for(int m=0; m<(1 << min(K*2+1, N)); m++) {
        if(__builtin_popcount(m) > K-1) continue;
        pq = pq2;

        for(int i=min(K*2+1, N)-1; i>=0; i--) {
            if(m & (1 << i)) continue;

            if(pq.size() < K) {
                pq.emplace(B[i], pq.size());
                ans[i] = pq.size()-1;
            }
            else {
                auto [t, g] = pq.top();
                pq.pop();
                pq.emplace(t+B[i], g);
                ans[i] = g;
            }
        }

        for(int i=min(K*2+1, N)-1; i>=0; i--) {
            if(!(m & (1 << i))) continue;

            if(pq.size() < K) {
                pq.emplace(B[i], pq.size());
                ans[i] = pq.size()-1;
            }
            else {
                auto [t, g] = pq.top();
                pq.pop();
                pq.emplace(t+B[i], g);
                ans[i] = g;
            }
        }

        ll x = pq.top().fi;
        while(!pq.empty()) {
            if(pq.top().fi != x) x = -1;
            pq.pop();
        }

        if(x != -1) return ans;
    }

    while(1);
    return {};
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
