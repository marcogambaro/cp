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

#include "boringgame.h"
#define ill __int128

constexpr int Q = 67;
constexpr ll INF = 1e18;

vec<pll> in;

void update_intervals(int q, ll x, bool rt) {
    for(int i=0; i<Q; i++) {
        auto &[l, r] = in[i];

        if(rt ^ (q > i)) l = max(l, x);
        else             r = min(r, x);
    }
}

ill calc(int q, ll x, bool rt) {
    ill ans = 0;

    for(int i=0; i<Q; i++) {
        auto [l, r] = in[i];

        if(rt ^ (q > i)) l = max(l, x);
        else             r = min(r, x);

        ans += max(0LL, r-l);
    }

    return ans;
}

ll get_query(int q) {
    ll l = 1, r = INF;
    ill t1 = calc(q, 1, 0) - calc(q, 1, 1);

    while(r-l > 1) {
        ll m = (l+r)/2;
        ill t = calc(q, m, 0) - calc(q, m, 1);

        if((t1 >= 0) == (t >= 0)) l = m;
        else r = m;
    }

    if(abs(calc(q,l,0) - calc(q,l,1)) <= abs(calc(q,r,0) - calc(q,r,1)))
        return l;
    return r;
}

long long play_game() {
    in.assign(Q, {1, INF + 1});

    for(int q=0; q<Q; q++) {
        ll x = get_query(q);
        cerr << x << lf;
        bool rt = ask(x);
        update_intervals(q, x, rt);
    }

    for(int i=0; i<Q; i++) {
        if(in[i].fi < in[i].se) return in[i].fi;
    }
    return -1;
}

#ifdef LOCAL
namespace {
const int CALLS_CNT_LIMIT = 150;
const long long MAXGUESS = 1'000'000'000'000'000'000LL;

int calls_cnt;
int T, t;
std::vector<long long> S, G;
std::vector<int> K, C;

void quit(const char* message) {
  printf("%s\n", message);
  exit(0);
}
} // namespace

bool ask(long long x) {
  calls_cnt++;
  if (calls_cnt > CALLS_CNT_LIMIT)
    quit("Too many calls");
  if (x < 1ll || x > MAXGUESS)
    quit("Invalid argument");

  return (x <= S[t]) ^ (K[t] < calls_cnt);
}

int main() {
  assert(1 == scanf("%d", &T));
  S.resize(T), K.resize(T);
  for (int i = 0; i < T; i++)
    assert(2 == scanf("%lld %d", &S[i], &K[i]));
  fclose(stdin);

  G.assign(T, 0), C.assign(T, 0);
  for (t = 0; t < T; ++t) {
    calls_cnt = 0;
    G[t] = play_game();
    C[t] = calls_cnt;
  }

  for (t = 0; t < T; ++t)
    printf("%lld %d\n", G[t], C[t]);

  fclose(stdout);

  return 0;
}
#endif
