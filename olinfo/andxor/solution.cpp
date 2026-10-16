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

int main() {
    int N; cin >> N;
  int Q; cin >> Q;
  vector<int> V(N);
  for(auto &i: V) cin >> i;

  int k = 23;

  vector<int> x(k), f(k);

  for(int i: V) {
    for(int b=1, j=0; j<k; b*=2, j++) {
      if(b & i) {
        f[j]++;
        x[j] ^= i;
      }
    }
  }

  // for(int j=0; j < k; j++) {
  //   cout << f[j] << " " << x[j] << "\n";
  // }

  int ans = 0;

  ans = 0;
  for(int i=0; i<k; i++) {
     if(f[i] != 0) {
       ans = max(ans, f[i] - (x[i]==0));
     }
  }
  cout << ans << "\n";

  while(Q--) {
    int pos, val;
    scanf("%d%d", &pos, &val);
    pos--;

    int i = V[pos];
    for(int b=1, j=0; j<k; b*=2, j++) {
      if(b & i) {
        f[j]--;
        x[j] ^= i;
      }
    }

    i = val;
    V[pos] = val;
    for(int b=1, j=0; j<k; b*=2, j++) {
      if(b & i) {
        f[j]++;
        x[j] ^= i;
      }
    }


    ans = 0;
  for(i=0; i<k; i++) {
     if(f[i] != 0) {
       ans = max(ans, f[i] - (x[i]==0));
     }
  }
  cout << ans << "\n";
  }
}

