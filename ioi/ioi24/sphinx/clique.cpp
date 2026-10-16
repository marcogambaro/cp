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

#include "sphinx.h"

vec<int> solve2() {
	int N = 2;
	vec<int> ans(N);

	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			vec<int> q(N, j);
			q[i] = -1;
			if(perform_experiment(q) == 1)
				ans[i] = j;
		}
	}

	return ans;
}

int getw(vec<int> &Q) {
	int rtn = 1;

	for(int i=1; i<Q.size(); i++) {
		if(Q[i] == -1 || Q[i] != Q[i-1]) rtn++;
	}

	return rtn;
}

vector<int> find_colours(int N, std::vector<int> X, std::vector<int> Y) {
	if(N == 2) return solve2();

	vec<int> ans(N, 0);

	for(int i=0; i<N; i++) {
		vec<int> q(N, N);

		q[i] = -1;
		for(int j=1; j<N; j++) {
			q[(i+j)%N] = j;
		}

		int l = 0, r = N;
		while(r-l > 1) {
			int m = (l+r)/2;
			vec<int> q2 = q;

			for(int j=m+1; j<N; j++)
				q2[(i+j)%N] = N;

			if(perform_experiment(q2) == (m == N-1 ? N : m+2)) l = m;
			else	r = m;
		}

		ans[i] = r%N;
	}

	return ans;
}


#ifndef EVAL
namespace {

const int CALLS_CNT_LIMIT = 2750;

int calls_cnt;

int N, M;
std::vector<int> C;
std::vector<int> X, Y;
std::vector<std::vector<int>> adj;

void quit(const char* message) {
  printf("%s\n", message);
  exit(0);
}

int count_components(const std::vector<int>& S) {
  int components_cnt = 0;
  std::vector<bool> vis(N, false);
  for (int i = 0; i < N; i++) {
    if (vis[i])
      continue;
    components_cnt++;

    std::queue<int> q;
    vis[i] = true;
    q.push(i);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      for (int nxt : adj[cur])
        if (!vis[nxt] && S[nxt] == S[cur]) {
          vis[nxt] = true;
          q.push(nxt);
        }
    }
  }
  return components_cnt;
}

} // namespace

int perform_experiment(std::vector<int> E) {
  calls_cnt++;
  if (calls_cnt > CALLS_CNT_LIMIT)
    quit("Too many calls");
  if ((int)E.size() != N)
    quit("Invalid argument");
  for (int i = 0; i < N; i++)
    if (!(-1 <= E[i] && E[i] <= N))
      quit("Invalid argument");

  std::vector<int> S(N);
  for (int i = 0; i < N; i++)
    S[i] = (E[i] == -1 ? C[i] : E[i]);

  return count_components(S);
}

int main() {
  assert(2 == scanf("%d%d", &N, &M));
  C.resize(N);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%d", &C[i]));
  X.resize(M), Y.resize(M);
  for (int j = 0; j < M; j++)
    assert(2 == scanf("%d%d", &X[j], &Y[j]));
  fclose(stdin);

  adj.assign(N, std::vector<int>());
  for (int j = 0; j < M; j++) {
    adj[X[j]].push_back(Y[j]);
    adj[Y[j]].push_back(X[j]);
  }

  calls_cnt = 0;
  std::vector<int> G = find_colours(N, X, Y);

  int L = G.size();
  printf("%d %d\n", L, calls_cnt);
  for (int i = 0; i < L; i++)
    printf("%s%d", (i == 0 ? "" : " "), G[i]);
  printf("\n");
  fclose(stdout);

  return 0;
}
#endif
