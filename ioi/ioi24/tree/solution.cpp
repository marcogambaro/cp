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

#include "tree.h"

vector<vector<int>> G;
int N;
vector<int> W;
vector<int> tin, tout, depth;

ll leafw, leafn;

void gett(int v, int d) {
	static int tt = 0;
	tin[v] = tt++;
	depth[v] = d;
	for(auto &u: G[v]) {
		gett(u, d+1);
	}
	tout[v] = tt;
}

vector<ll> t;
void update(int v, int l, int r, int q, ll x) {
	if(r-l == 1) {
		t[v] += x;
		return;
	}
	int m = (l+r)/2;
	if(q < m) update(v*2, l, m, q, x);
	else update(v*2+1, m, r, q, x);
	t[v] = t[v*2] + t[v*2+1];
}
ll sum(int v, int l, int r, int ql, int qr) {
	if(qr <= l || r <= ql) return 0;
	if(ql <= l && r <= qr) return t[v];
	int m = (l+r)/2;
	return sum(v*2, l, m, ql, qr) + sum(v*2+1, m, r, ql, qr);
} 

vector<ll> ans1;
struct dt1{
	vector<ll> x, d;

	dt1(int k = 1e6+3) {
		x.resize(k*4);
		d.resize(k*4);
		ans1.resize(k);
	}

	void push(int v, int l, int m, int r) {
		x[v*2+1] += x[v];
		d[v*2+1] += d[v];

		x[v*2] += x[v] + d[v]*(r-m);
		d[v*2] += d[v];

		x[v] = 0;
		d[v] = 0;
	}

	void add(int v, int l, int r, int ql, int qr, ll k) {
		if(qr <= l || r <= ql) return;
		if(ql <= l && r <= qr) {
			x[v] += k*(qr-r+1);
			d[v] += k;
			return;
		}

		int m = (l+r)/2;
		add(v*2, l, m, ql, qr, k);
		add(v*2+1, m, r, ql, qr, k);
	}
	void add(int ql, int qr, ll k) {
		add(1, 0, 1e6+3, ql, qr, k);
	}

	void trans(int v, int l, int r) {
		if(r-l == 1) {
			ans1[l] = x[v];
			return;
		}
		int m = (l+r)/2;
		push(v, l, m, r);
		trans(v*2, l, m);
		trans(v*2+1, m, r);
	}
	void trans() {
		trans(1, 0, 1e6+3);
	}
};

struct dt2{
	vector<int> t;

	dt2() {
		t.resize(N*4, -1);
	}

	void push(int v) {
		if(t[v] == -1) return;
		for(int u = v*2; u < v*2+2; u++) {
			if(t[u] == -1 || depth[t[u]] < depth[t[v]]) 
				t[u] = t[v];
		}
	}

	void update(int v, int l, int r, int ql, int qr, int p) {
		if(qr <= l || r <= ql) return;
		if(ql <= l && r <= qr) {
			if(t[v] == -1 || depth[t[v]] < depth[p]) {
				t[v] = p;
			}
			return;
		}

		int m = (l+r)/2;
		push(v);
		update(v*2, l, m, ql, qr, p);
		update(v*2+1, m, r, ql, qr, p);
	}

	int get(int v, int l, int r, int q) {
		if(r-l == 1) return t[v];
		int m = (l+r)/2;
		push(v);
		if(q < m) return get(v*2, l, m, q);
		return get(v*2+1, m, r, q);
	}
	int get(int q) {
		return get(1, 0, N, q);
	}
};

void init(std::vector<int> P, std::vector<int> W) {
	N = P.size();
	
	G.resize(N);	
	t.resize(N*4);

	for(int i=1; i<N; i++) {
		G[P[i]].emplace_back(i);
	}
	tin = tout = depth = vector<int>(N);
	gett(0, 0);
	
	vector<int> V;
	for(int i=0; i<N; i++) {
		if(G[i].empty()) {
			leafw+=W[i];
		 	leafn++;
			update(1, 0, N, tin[i], 1);
		}
		else V.push_back(i);
	}

	sort(all(V), [&](int &i, int &j){return W[i] < W[j];});
	dt1 sgans;
	dt2 hh;

	int solved = leafn;

	for(auto &v: V) {
		int p = hh.get(tin[v]);
		int sub = sum(1, 0, N, tin[v], tout[v]);

		if(p == -1) {
			// move solved by sub-1!
			sgans.add(0, solved, W[v]);
			sgans.add(0, solved-sub+1, -W[v]);

			solved -= sub-1;

			update(1, 0, N, tin[v], -sub+1);
			for(auto &u: G[v]) {
				hh.update(1, 0, N, tin[u], tout[u], u);
			}
		}
		else {
			// recover p by stealing the size of sub
			int subp = sum(1, 0, N, tin[p]+1, tout[p]);
			int wp = W[P[p]];
			sgans.add(0, subp, W[v]-wp);
			#ifdef MARCO
			sgans.trans();
			#endif
			sgans.add(0, subp-sub+1, +wp-W[v]);

			#ifdef MARCO
			sgans.trans();
			#endif

			hh.update(1, 0, N, tin[v], tout[v], v);
			update(1, 0, N, tin[v], -sub+1);
			update(1, 0, N, tin[P[p]], +sub-1);
			for(auto &u: G[v]) {
				hh.update(1, 0, N, tin[u], tout[u], u);
			}
		}

		#ifdef MARCO
		sgans.trans();
		#endif
	}

	assert(solved == 1);
	sgans.trans();
	::W.swap(W);
}

long long query(int L, int R) {
	return ans1[R/L]*L - (ans1[R/L] - ans1[R/L+1])*(R%L) + L*leafw; 
}


#ifdef LOCAL
int main() {
  int N;
  assert(1 == scanf("%d", &N));
  std::vector<int> P(N);
  P[0] = -1;
  for (int i = 1; i < N; i++)
    assert(1 == scanf("%d", &P[i]));
  std::vector<int> W(N);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%d", &W[i]));
  int Q;
  assert(1 == scanf("%d", &Q));
  std::vector<int> L(Q), R(Q);
  for (int j = 0; j < Q; j++)
    assert(2 == scanf("%d%d", &L[j], &R[j]));
  fclose(stdin);


  init(P, W);
  std::vector<long long> A(Q);
  for (int j = 0; j < Q; j++)
    A[j] = query(L[j], R[j]);

  for (int j = 0; j < Q; j++)
    printf("%lld\n", A[j]);
  fclose(stdout);

  return 0;
}
#endif
