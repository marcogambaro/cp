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

#include "souvenirs.h"

int n;
vector<ll> tot, V;

pair<vector<int>, ll> query(ll x) {
	auto [t, m] = transaction(x);
	for(int i: t) tot[i]++;

	return {t, m};
}

void finish() {
	for(int i=0; i<n; i++) 
		while(tot[i] < i) query(V[i]);
}
/*
10
900
560
340
9
8
7
6
5
4
3
*/

void recurse(vector<int> &f, ll mn, ll r) {
	if(V[f.front()] != -1) exit(1);

	int i = f.front();

	while(1) {
		vector<int> t;
		ll xt = 0;

		for(int j: f) {
			if(j == i) continue;
			if(V[j] == -1) t.push_back(j);
			else  xt += V[j];
		}

		if(t.size() == 0) {
			//we know the value of i
			V[i] = mn-r-xt;

			if(i == n-1 || V[i+1] != -1) return;
			auto [f2, r2] = query(V[i]-1);
			recurse(f2, V[i]-1, r2);
			return;
		}
		else {
			ll mn2 = (mn - r - xt - t.size()*(t.size()+1)/2 ) / (t.size()+1);
			auto [f2, r2] = query(mn2);
			recurse(f2, mn2, r2);
		}
	}
}

void buy_souvenirs(int N, long long P0) {
	n = N;
	ll p0 = P0;
  	tot.resize(N);
	V.resize(N, -1);
	
	auto [f, r] = query(p0-1);
	recurse(f, P0-1, r);

	finish();
}


#ifdef LOCAL
namespace {
const int CALLS_CNT_LIMIT = 10'000;

int calls_cnt;
int N;
std::vector<long long> P;
std::vector<int> Q;

void quit(const char* message) {
  printf("%s\n", message);
  exit(0);
}
} // namespace

std::pair<std::vector<int>, long long> transaction(long long M) {
  calls_cnt++;
  if (calls_cnt > CALLS_CNT_LIMIT)
    quit("Too many calls");
  if (M >= P[0] || M < P[N - 1])
    quit("Invalid argument");

  std::vector<int> L;
  long long R = M;
  for (int i = 0; i < N; i++) {
    if (R >= P[i]) {
      R -= P[i];
      Q[i]++;
      L.push_back(i);
    }
  }
  return {L, R};
}

int main() {
  assert(1 == scanf("%d", &N));
  P.resize(N);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%lld", &P[i]));
  fclose(stdin);

  Q.assign(N, 0);
  calls_cnt = 0;
  buy_souvenirs(N, P[0]);
  for (int i = 0; i < N; i++)
    printf("%s%d", i ? " " : "", Q[i]);
  printf("\n");
  fclose(stdout);

  return 0;
}
#endif
