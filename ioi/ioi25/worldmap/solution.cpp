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

#include "worldmap.h"

std::vector<std::vector<int>> create_map(int N, int M, std::vector<int> A, std::vector<int> B) {
	vec<int> vis(N+1);
	vec<vec<int>> g(N+1), tb(2*N, vec<int>(2*N));
	vec<vec<bool>> win(N+1, vec<bool>(N+1));
	for(int i=0; i<M; i++) {
		g[A[i]].push_back(B[i]);
		g[B[i]].push_back(A[i]);
		win[A[i]][B[i]] = win[B[i]][A[i]] = 1;
	}

	vec<vec<pair<int, int>>> av(N+1);
	vector<int> analize;
	int time = 0;
	int col = 1;

	auto dfs = [&](int v, auto &&self) -> void {
		vis[v] = 1;
		tb[0][time] = v;
		int l = time;
		time++;
		int r = l;
		for(auto &u: g[v]) {
			if(vis[u]) continue;
			win[u][v] = win[v][u] = 0;
			self(u, self);
			tb[0][time++] = v;
			r = time;
		}

		analize.push_back(v);
		if(r == l) return;

		for(int i=l; i<r; i++) {
			tb[col][i] = tb[col+1][i] = v;
		}
		for(int i=l+1; i<r; i+=2) av[v].push_back({col+1, i});
		
		col += 2;
	};
	dfs(1, dfs);

	for(int i: analize) {
		for(int j=1; j<=N; j++) {
			if(win[i][j]) {
				win[i][j] = win[j][i] = 0;
				if(av[j].size() == 0) exit(1);
				auto [x, y] = av[j].back();
				av[j].pop_back();
				
				if(x != 2*N-1) tb[x+1][y] = tb[x][y];
				tb[x][y] = i;
			}
		}
	}

	for(int i=1; i<tb.size(); i++)
		for(int j=0; j<tb.size(); j++) 
			if(tb[i][j] == 0) tb[i][j] = tb[i-1][j];
	for(int i=0; i<N*2; i++) tb[i][2*N-1] = tb[i][2*N-2];

	return tb;
}

#ifdef LOCAL
int main() {
  int T;
  assert(1 == scanf("%d", &T));

  std::vector<int> Nt(T), Mt(T);
  std::vector<std::pair<std::vector<int>, std::vector<int>>> AB;

  for (int t = 0; t < T; ++t) {
    assert(2 == scanf("%d %d", &Nt[t], &Mt[t]));

    int M = Mt[t];
    std::vector<int> A(M), B(M);

    for (int i = 0; i < Mt[t]; i++) {
      assert(2 == scanf("%d %d", &A[i], &B[i]));
    }
    AB.push_back(make_pair(A, B));
  }

  fclose(stdin);

  std::vector<std::vector<std::vector<int>>> Ct;

  for (int t = 0; t < T; t++) {
    int N = Nt[t], M = Mt[t];
    std::vector<int> A = AB[t].first, B = AB[t].second;

    auto C = create_map(N, M, A, B);
    Ct.push_back(C);
  }

  for (int t = 0; t < T; t++) {
    auto& C = Ct[t];
    int P = (int)C.size();

    std::vector<int> Q(P);
    for (int i = 0; i < P; ++i)
      Q[i] = (int)C[i].size();

    printf("%d\n", P);
    for (int i = 0; i < P; ++i)
      printf("%d%c", Q[i], " \n"[i + 1 == P]);
    printf("\n");
    for (int i = 0; i < P; i++) {
      for (int j = 0; j < Q[i]; j++) {
        printf("%d%c", C[i][j], " \n"[j + 1 == Q[i]]);
      }
    }
    if (t < T - 1)
      printf("\n");
  }

  fclose(stdout);

  return 0;
}
#endif
