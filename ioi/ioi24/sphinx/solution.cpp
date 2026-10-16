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

struct DSU {
	vec<int> t;

	DSU () {}

	DSU(int n) {
		t.resize(n, -1);
	}

	int rep(int v) {
		if(t[v] < 0) return v;
		return t[v] = rep(t[v]);
	}

	void unite(int a, int b) {
		a = rep(a), b = rep(b);
		if(a == b) return;
		if(a > b) swap(a, b);
		t[a] += t[b];
		t[b] = a;
	}
};
DSU dsu;

int n;
vec<vec<int>> G;

int getw(vec<int> Q) {
	vec<bool> vis(n);
	for(int i=0; i<n; i++) {
		if(Q[i] == -1) Q[i] = dsu.rep(i) + 85432;
	}

	auto dfs = [&](int v, auto &&self) {
		if(vis[v] == 1) return;
		vis[v] = 1;

		for(int u: G[v]) {
			if(Q[u] != Q[v]) continue;
			self(u, self);
		}
	};

	int rtn = 0;
	for(int i=0; i<n; i++) {
		if(!vis[i]) {
			rtn++;
			dfs(i, dfs);
		}
	}

	return rtn;
}

vector<int> find_colours(int N, std::vector<int> X, std::vector<int> Y) {
	int M = X.size();

	G.resize(N);
	n = N;

	for(int i=0; i<M; i++) {
		G[X[i]].push_back(Y[i]);
		G[Y[i]].push_back(X[i]);
	}

	dsu = DSU(N);
	vec<bool> vis(N);

	auto dfs = [&](int v, auto &&self) {
		if(vis[v]) return;
		vis[v] = 1;

		vec<int> q(N, N);

		sort(all(G[v]));
		for(int u: G[v]) {
			if(vis[u]) q[u] = -1;
		}
		q[v] = -1;

		set<int> st;
		vec<int> b;

		for(int i: G[v]) {
			if(i == v) continue;
			if(q[i] == -1 && i != v) st.insert(i);
		}
		for(int i: st) b.push_back(i);

		while(!b.empty() && perform_experiment(q) != getw(q)) {
			int l=-1, r=b.size();
			while(r-l > 1) {
				int m = (l+r)/2;

				vec<int> q2 = q;
				for(int j=m+1; j<b.size(); j++)
					q2[b[j]] = N;

				if(perform_experiment(q2) == getw(q2)) l = m;
				else 			r = m;
			}
			if(r == b.size()) break;
			dsu.unite(v, b[r]);

			vec<int> b2;
			for(int j=r+1; j<b.size(); j++) {
				if(dsu.rep(v) == dsu.rep(b[j])) continue;
				b2.push_back(b[j]);
			}
			b2.swap(b);

		}

		for(int u: G[v]) {
			self(u, self);
		}
	};
	dfs(0, dfs);

	vec<vec<int>> C(N);

	for(int i=0; i<M; i++) {
		X[i] = dsu.rep(X[i]);
		Y[i] = dsu.rep(Y[i]);
		if(X[i] == Y[i]) continue;
		C[X[i]].push_back(Y[i]);
		C[Y[i]].push_back(X[i]);
	}

	vec<vec<int>> scc(N);
	for(int i=0; i<N; i++) {
		scc[dsu.rep(i)].push_back(i);
	}

	auto paint = [&](int i, int c, vec<int> &q) {
		i = dsu.rep(i);
		for(int j: scc[i])
			q[j] = c;
		return;
	};

	vec<int> d(N, 1e9);
	d[0] = 0;
	queue<int> q;
	q.push(0);

	while(!q.empty()) {
		int v = q.front();
		q.pop();

		for(int u: C[v]) {
			if(d[u] != 1e9) continue;
			d[u] = d[v]+1;
			q.push(u);
		}
	}

	vec<int> st0, st1;
	for(int i=0; i<N; i++) {
		if(d[i] == 1e9) continue;
		if(d[i] & 1) st1.push_back(i);
		else		 st0.push_back(i);
	}

	if(st1.empty()) {
		vec<int> q(N, -1);

		for(int c=0; c<N; c++) {
			q[0] = c;
			if(perform_experiment(q) == 1)
				return vector<int>(N, c);
		}
	}

	vec<int> ans(N, -1);

	for(int c=0; c<N; c++) {
		for(int z=0; z<2; z++, st0.swap(st1)) {
			vec<int> q(N, N);

			for(int i: st0) paint(i, -1, q);
			if(z == 0) {
				for(int i=0; i<N; i++) {
					if(d[i] == 1e9) continue;
					if(d[i] & 1) paint(i, c, q);
				}
			} else {
				for(int i=0; i<N; i++) {
					if(d[i] == 1e9) continue;
					if(d[i] & 1);
					else paint(i, c, q);
				}
			}

			while(st0.size() && perform_experiment(q) != getw(q)) {
				int l = -1, r = (int)st0.size()-1;

				while(r-l > 1) {
					int m = (l+r)/2;
					vec<int> q2 = q;

					for(int j=m+1; j<st0.size(); j++) {
						paint(st0[j], N, q2);
					}

					if(perform_experiment(q2) == getw(q2)) l = m;
					else r = m;
				}

				paint(st0[r], c, ans);
				paint(st0[r], N, q);

				vec<int> stn;
				for(int i=0; i<st0.size(); i++) {
					if(i == r) continue;
					stn.push_back(st0[i]);
				}
				stn.swap(st0);
			}
		}
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
