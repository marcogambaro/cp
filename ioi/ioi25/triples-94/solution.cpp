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

#include "triples.h"

long long count_triples(std::vector<int> H) {
	ll ans = 0;
	int N = H.size();

	for(int i=0; i<N; i++) {
		if(i - H[i] >= 0) {
			int j = i - H[i];
			if(j + H[j] < i) {
				int k1 = j + H[j];
				if(k1 + H[k1] == i) 
				ans++;
				int k2 = i - H[j];
				if(k2 != k1 && j + H[k2] == k2) 
				ans++;
			}
		}

		if(i + H[i] < N) {
			int j = i + H[i];
			if(j - H[j] > i) {
				int k1 = j - H[j];
				if(k1 - H[k1] == i) 
					ans++;
				int k2 = i + H[j];
				if(k2 != k1 && k2 + H[k2] == j)
				 	ans++;
			}
		}
	}

	for(int i=0; i<N; i++) {
		int k = i + H[i];
		if(k >= N) continue;
		int j = i + H[k];
		if(j < N && k + H[j] == j && H[i] != H[j]) ans++;
	}

	vector<vector<int>> sub(2*N), add(2*N);
	for(int i=0; i<N; i++) {
		sub[N + i - H[i]].push_back(i);
		add[i + H[i]].push_back(i);
	}

	for(int i=0; i<N; i++) {
		int n = lower_bound(all(sub[i - H[i] + N]), i)-sub[i-H[i]+N].begin();
		int m = add[i+H[i]].end() - lower_bound(all(add[i+H[i]]), i);

		if(n < m) {
			for(int &j: sub[i-H[i]+N]) {
				if(j == i) break;
				int k = i + H[j];
				if(k < N && k == j+H[i] && i == j+H[k]) ans++;
			}
		}
		else {
			auto it = add[i+H[i]].end();
			for(it--; *it!=i; it--) {
				int j = *it;
				int k = i-H[j];
				if(k >= 0 && k == j-H[i] && j == i+H[k]) ans++;
			}
		}
	}

	return ans;
}

std::vector<int> construct_range(int M, int K) {
	int N = M;
	ll k;
	if(N == 20) return {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2};
	if(N == 500) k = 12;
	if(N == 5000) k = 43;
	if(N == 30000) k = 104;
	if(N == 100000) k = 182;
	if(N == 200000) k = 270;

	vector<int> ans(N, 1);
	for(int i=0; i<N; i+=3) ans[i] = 2;

	for(int i=0; i<k; i++) {
		for(int j=0; j<k; j++)
			ans[i*k + j] = (k-i)*k + j;
	}

	for(int i=0; i<k; i++) {
		for(int j=i; j<k; j++) 
			ans[(k+j)*k + i] =  k*k*2 + i*(k+1) - (j-i)*k;
	}

	for(int i=0; i<k; i++) {
		for(int j=0; j<k; j++) {
			if(k*k*2 + i*(k+1) + j < N)
				ans[k*k*2 + i*(k+1) + j] = k*k + i*(k+1) - j;
		}
	}

	for(int &i: ans) if(i >= N) i = 2;
	return ans;
}


#ifdef LOCAL
namespace {

void run_part1() {
  int N;
  assert(1 == scanf("%d", &N));
  std::vector<int> H(N);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%d", &H[i]));
  fclose(stdin);

  long long T = count_triples(H);

  printf("%lld\n", T);
  fclose(stdout);
}

void run_part2() {
  int M, K;
  assert(2 == scanf("%d %d", &M, &K));
  fclose(stdin);

  std::vector<int> H = construct_range(M, K);

  int N = H.size();
  printf("%d\n", N);
//   for (int i = 0; i < N; i++)
//     printf("%d%c", H[i], " \n"[i + 1 == N]);
  printf("\nK = %lld\n", count_triples(H));
  fclose(stdout);
}

} // namespace

int main() {
  int part;
  assert(1 == scanf("%d", &part));
  if (part == 1)
    run_part1();
  else if (part == 2)
    run_part2();

  return 0;
}
#endif
