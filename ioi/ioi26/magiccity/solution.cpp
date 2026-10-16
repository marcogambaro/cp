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

#include "magiccity.h"

pair<vector<int>, vector<pair<int, int>>> construct(int K) {
    vec<int> type;
    vec<pii> edg;

    if(K == 1) {
        type = {0, 1};
        edg = {{0, 1}};
    }
    else if(K == 2) {
        type = {0, 1, 2, 3, 0, 2, 1, 3, 0, 1, 3, 2};
        for(int i=0; i<12; i+=4) {
            edg.emplace_back(i, i+1);
            edg.emplace_back(i+1, i+2);
            edg.emplace_back(i+2, i+3);
            edg.emplace_back(i+3, i);
        }
    }
    else if(K == 3 || K == 4) {
        for(int i=0; i<K*K*2; i+=K*2) {
            for(int j=0; j<K*2; j++)
                type.emplace_back(j);

            for(int a=i; a<i+K; a++) for(int b=a+1; b<i+K; b++)
                edg.emplace_back(a, b), edg.emplace_back(a+K, b+K);

            for(int j=0; j<K; j++) {
                if(i == 0)   edg.emplace_back(i+j, i+K+j);
                if(i == K*2) edg.emplace_back(i+j, i+K+(j+1)%K);
                if(i == K*4) edg.emplace_back(i+j, i+K+(j+2)%K);
                if(i == K*6) edg.emplace_back(i+j, i+K+(j+3)%K);
            }
        }

        for(int j=0; j<K*2; j++)
            type.emplace_back(j);

        for(int i=K*K*2; i<K*K*2+K; i++) for(int j=K*K*2+K; j<K*K*2+K*2; j++)
            edg.emplace_back(i, j);
    }
    else if(K == 5) {
        for(int i=0; i<50; i++)
            type.emplace_back(i%10);

        for(int i=0; i<10; i++) {
            if(i < 5) {
                edg.emplace_back(i, i+5);
                edg.emplace_back(i+10, i+15);
            }
            edg.emplace_back(i, (i+1)%10);
            edg.emplace_back(i, (i+4)%10);
            edg.emplace_back(10+i, 10+(i+2)%10);
            edg.emplace_back(10+i, 10+(i+3)%10);
        }

        for(int i=0; i<10; i++) {
            edg.emplace_back(20+i, 20+(i+2)%10);
            edg.emplace_back(20+i, 20+(i+4)%10);
            if(i%2==0) edg.emplace_back(20+i, 20+(i+1)%10);

            edg.emplace_back(30+i, 30+(i+3)%10);
            edg.emplace_back(30+i, 30+(i+4)%10);
            if(i%2==0) edg.emplace_back(30+i, 30+(i+1)%10);

            edg.emplace_back(40+i, 40+(i+2)%10);
            edg.emplace_back(40+i, 40+(i+3)%10);
            if(i%2==1) edg.emplace_back(40+i, 40+(i+1)%10);
        }
    }
    else {
        bool d = 0;
        if(K&1) d=1, K--;
        K*=2;
        int k = K/4;

        for(int i=0; i<6; i++) {
            for(int j=0; j<K; j++)
                type.push_back(j);
        }

        auto cric = [&](vec<int> v) {
            for(int i=0; i<v.size(); i++) {
                for(int j=i+1; j<v.size(); j++) {
                    edg.emplace_back(v[i], v[j]);
                }
            }
        };

        auto connect = [&](vec<int> a, vec<int> b) {
            for(int i: a) for(int j: b)
                edg.emplace_back(i, j);
        };

        auto vecc = [&](int l) -> vec<int> {
            int r = l+k;
            vec<int> v;
            for(int i=l; i<r; i++)
                v.emplace_back(i);
            return v;
        };

        for(int i=0; i<12; i++)
            cric(vecc(i*(K/4)));

        connect(vecc(0*k), vecc(1*k));
        connect(vecc(2*k), vecc(3*k));
        connect(vecc(4*k), vecc(6*k));
        connect(vecc(5*k), vecc(7*k));
        connect(vecc(8*k), vecc(11*k));
        connect(vecc(9*k), vecc(10*k));

        auto roll = [&](int a, int b, int c, int d) {
            connect(vecc(a*k), vecc(b*k));
            connect(vecc(b*k), vecc(c*k));
            connect(vecc(c*k), vecc(d*k));
            connect(vecc(d*k), vecc(a*k));
        };

        roll(12, 13, 14, 15);
        roll(16, 17, 19, 18);
        roll(20, 22, 21, 23);

        if(d) {
            int n = type.size();

            for(int i=0; i<6; i++)
                type.push_back(K);
            for(int i=0; i<6; i++)
                type.push_back(K+1);

            for(int i=0; i<6; i++)
                edg.emplace_back(n+i, n+i+6);

            auto leg = [&](int i, vec<int> q) {
                for(int j: q) {
                    connect({n+i}, vecc(j*k));
                    connect({n+i+6}, vecc(j*k));
                }
            };

            leg(0, {0, 1});
            leg(1, {2, 3});
            leg(2, {4, 6});
            leg(3, {5, 7});
            leg(4, {8, 11});
            leg(5, {9, 10});
        }
    }

    return {type, edg};
}

#ifndef EVAL
int main() {
  int K;
  assert(1 == scanf("%d", &K));
  fclose(stdin);

  std::pair<std::vector<int>, std::vector<std::pair<int, int>>> result =
      construct(K);
  const std::vector<int> &T = result.first;
  const std::vector<std::pair<int, int>> &E = result.second;
  int N = (int)T.size();
  int M = (int)E.size();

  printf("%d %d\n", N, M);
  for (int i = 0; i < N; i++) {
    printf("%d%c", T[i], " \n"[i + 1 == N]);
  }
  if (N == 0) {
    printf("\n");
  }
  for (int j = 0; j < M; j++) {
    auto &[U, V] = E[j];
    printf("%d %d\n", U, V);
  }
  fclose(stdout);
  return 0;
}
#endif
