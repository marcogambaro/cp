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

#include "migrations.h"

constexpr int MAXN = 10000;

vec<vec<int>> G(MAXN);
vec<int> dist(MAXN);

int farthest(int n) {
	fill(all(dist), -1);	
	queue<int> q;
	q.emplace(n);
	dist[n] = 0;

	int ans;
	while(!q.empty()) {
		int v = q.front();
		q.pop();

		for(auto &u: G[v]) {
			if(dist[u] == -1) {
				dist[u] = dist[v]+1;
				q.push(u);
			}
		}
		ans = v;
	}

	return ans;
}

int d1, d2, d;
int A, B;

void update(int i) {
	int f = farthest(d1);
	if(dist[f] > d) {
		assert(f == i);
		d2 = f;
		d = dist[f];
		return;
	}

	f = farthest(d2);
	if(dist[f] > d) {
		assert(f == i);
		d1 = f;
		d = dist[f];
		return;
	}
}
int find(vec<int> &v, int x) {
	int ans = 0;
	while(v[ans] != x && ans < v.size()) ans++;
	return ans;
}

vec<int> v1 = {0}, v2 = {0}; 
int q;

vec<int> C = {9666, 9956, 9981, 9993, 9995};
vec<int> K = {34, 10, 7, 3};
int PRESS = 0;

void search(vec<int> &v, int x, int k) {
	vec<int> n;

	for(int i=x; i<v.size(); i+=k)
		n.emplace_back(v[i]);

	n.swap(v);
}

int send_message(int N, int i, int Pi) {
	G[Pi].push_back(i);
	G[i].push_back(Pi);

	v1.push_back(i);
	v2.push_back(i);
	
	if(i < C[0]) return 0;
	else if(i == C[0]) {
		d1 = farthest(0);
		d2 = farthest(d1);
		d = dist[d2];
	} 
	else update(i);

	if(C[0] <= i && i < C.back()) {
		for(int k = 0; k < 4; k++) {
			if(C[k] != i) continue;
			
			int a = find(v1, d1) % K[k];
			int b = find(v2, d2) % K[k];

			search(v1, a, K[k]);
			search(v2, b, K[k]);

			PRESS = b*K[k] + a;
			break;
		}

		if(1 <= PRESS && PRESS <= 4) {
			PRESS -= 4;
			return PRESS+4;			
		}

		PRESS -= 4;
		return 0;
	}

	
	if(i < N-2) {
		if(v1.size() > 10 || v2.size() > 10) exit(1);

		int a = find(v1, d1) % 2;
		int b = find(v2, d2) % 2;

		search(v1, a, 2);
		search(v2, b, 2);

		return b*2 + a;
	}
	else if(i == N-2) {
		if(v1.size() > 3 || v2.size() > 3) exit(1);
		assert(v1.size() <= 3 && v2.size() <= 3);

		if(d1 == i) return 0;
		if(d2 == i) {
			v1.swap(v2);
			swap(d1, d2);
			return 1;
		}
		if(d1 == v1[0]) return 2;
		if(d1 == v1[1]) return 3;

		assert(0);
	}
	else if(i == N-1) {
		if(d1 == i) {
			if(d2 == v2[0]) return 3;
			if(d2 == v2[1]) return 4;
		}
		else {
			if(d2 == v2[0]) return 0;
			if(d2 == v2[1]) return 1;
			if(d2 == i) return 2;
		}

		assert(0);
	}

	return 0;
}

std::pair<int, int> longest_path(std::vector<int> S) {
	int N = S.size();
	int nr = 1;

	for(int k = 0; k < 4; k++) {
		int c = 0;
		
		for(int i = C[k]; i < C[k+1]; i++) {
			if(S[i]) c += (i - C[k])*4 + S[i];
		}

		int a = c%K[k];
		int b = c/K[k];

		while(nr <= C[k]) {
			v1.emplace_back(nr);
			v2.emplace_back(nr);
			nr++;
		}

		search(v1, a, K[k]);
		search(v2, b, K[k]);
	}

	v1.emplace_back(nr);
	v2.emplace_back(nr);
	nr++;

	while(nr < N-2) {
		v1.emplace_back(nr);
		v2.emplace_back(nr);

		int a = S[nr]%2;
		int b = S[nr]/2;

		search(v1, a, 2);
		search(v2, b, 2);

		nr++;
	}

	while(v1.size() < 2) v1.emplace_back(N-2);
	while(v2.size() < 2) v2.emplace_back(N-2);
	assert(v1.size() <= 2 && v2.size() <= 2);

	int V, U;
	vec<int> w;

	if(S[N-2] == 0) V = N-2, w = v2;
	if(S[N-2] == 1) V = N-2, w = v1;
	if(S[N-2] == 2) V = v1[0], w = v2;
	if(S[N-2] == 3) V = v1[1], w = v2;
	
	if(S[N-1] >= 3) {
		V = N-1;
		U = w[S[N-1]-3];
	}
	else if(S[N-1] == 2) {
		U = N-1;
	}
	else {
		U = w[S[N-1]];
	}

	return {V, U};
}

#ifdef LOCAL
int main() {
  int N;
  N = 1e4;

  std::vector<int> P(N, 0);
  for (int i = 1; i < N; ++i) {
    P[i] = 0;
  }

  std::vector<int> S(N, 0);
  for (int i = 1; i < N; ++i) {
    S[i] = send_message(N, i, P[i]);
  }
  for (int i = 1; i < N; ++i) {
    printf("%d%c", S[i], " \n"[i + 1 == N]);
  }

  v1 = v2 = {0};

  auto [U, V] = longest_path(S);
  printf("%d %d\n", U, V);
  fclose(stdout);

  return 0;
}
#endif
