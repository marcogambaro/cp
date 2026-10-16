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

#include "tiling.h"

vec<vec<int>> tb;
int n, m;

// vec<pii> tl, tr, bl, br;

bool occ(int i, int j) {
    if(i < 0) return 1;
    if(j < 0) return 1;
    if(i >= n) return 1;
    if(j >= m) return 1;

    return tb[i][j];
}

void init(int N, int M) {
    tb = vector(N, vec<int>(M));
    n = N;
    m = M;
}

std::pair<int, int> receive_block(int TL, int TR, int BL, int BR) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            bool ok = 1;

            if(TL == 0) {
                if(occ(i, j)) ok = 0;
                if(!occ(i+1, j)) ok = 0;
                if(!occ(i, j+1)) ok = 0;
            }
            else if(TR == 0) {
                if(occ(i, j)) ok = 0;
                if(!occ(i+1, j)) ok = 0;
                if(!occ(i, j-1)) ok = 0;
            }
            else if(BL == 0) {
                if(occ(i, j)) ok = 0;
                if(!occ(i-1, j)) ok = 0;
                if(!occ(i, j+1)) ok = 0;
            }
            else if(BR == 0) {
                if(occ(i, j)) ok = 0;
                if(!occ(i-1, j)) ok = 0;
                if(!occ(i, j-1)) ok = 0;
            }
            else exit(1);

            if(ok) {
                tb[i][j] = 1;
                return {i*2, j*2};
            }
        }
    }

    exit(-1);
}

#ifdef LOCAL
int main() {
  int N, M;
  assert(2 == scanf("%d%d", &N, &M));

  std::vector<int> TL(N * M), TR(N * M), BL(N * M), BR(N * M);
  for (int k = 0; k < N * M; ++k) {
    assert(4 == scanf("%d%d%d%d", &TL[k], &TR[k], &BL[k], &BR[k]));
  }
  fclose(stdin);

  init(N, M);

  for (int k = 0; k < N * M; ++k) {
    auto [R, C] = receive_block(TL[k], TR[k], BL[k], BR[k]);
    printf("%d %d\n", R, C);
  }
  fclose(stdout);

  return 0;
}
#endif
