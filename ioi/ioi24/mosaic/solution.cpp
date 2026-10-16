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

#include "mosaic.h"

vec<long long> mosaic(vec<int> X, vec<int> Y, vec<int> T, vec<int> B, vec<int> L, vec<int> R) {
    int N = X.size();
    int Q = T.size();

	vec<ll> ans(Q);

	vec<vec<int>> Qs(N);
	for(int i=0; i<Q; i++) {
		Qs[B[i]].push_back(i);
	}

	deque<ll> sfx(N+7);
	deque<ll> cs(N+7), ds(N+7);
	const int RC = min(N, 5);

	auto recalc = [&](deque<ll> &v, int pos) {
		for(int i=min(pos, (int)v.size()-1); i>=0; i--) {
			sfx[i] = sfx[i+1] + v[i];
			ds[i] = ds[i+1] + sfx[i+1] + v[i];
			cs[i] = cs[i+1] + v[i] * (cs.size() - i);
		}
	};

	auto query = [&](int l, int r, int h) -> ll {
		if(h == 0) return 0;
		r += h-1;
		int s = min(r-l-h, h-1);
		int ml = l+s, mr = r-s;

		ll ans = 0;
		ans += ds[l] - ds[ml] - sfx[ml] * (ml-l);
		ans += (sfx[ml] - sfx[mr])*(s+1);
		ans += cs[mr] - cs[r] - (sfx[mr] - sfx[r]) * (cs.size()-r);

		return ans;
	};

	deque<ll> x(N);
	for(int i=0; i<N; i++)
		x[i] = X[i];

	recalc(x, N-1);

	for(int q=0; q<Q; q++) {
		if(T[q] <= 0 && 0 <= B[q])
			ans[q] += sfx[max(L[q], RC)] - sfx[max(R[q]+1, RC)];
	}

	for(int i=1; i<N; i++) {
		if(i < RC) {
			// recocompute the whole thingy
			deque<ll> x2(N);
			x2[0] = Y[i];
			for(int i=1; i<N; i++)
				x2[i] = (x2[i-1] == x[i] && x[i] == 0);

			x2.swap(x);
			recalc(x, x.size()-1);

			for(int q=0; q<Q; q++) {
				if(T[q] <= i && i <= B[q])
					ans[q] += sfx[max(L[q], RC)] - sfx[max(R[q]+1, RC)];
			}
		}
		else {
			x.push_front(Y[i]);
			sfx.push_front(0);
			cs.push_front(0);
			ds.push_front(0);

			for(int j=1; j<RC; j++) {
				x[j] = (x[j-1] == x[j+1] && x[j+1] == 0);
			}

			recalc(x, RC);

			for(int q: Qs[i]) {
				int t = max(RC, T[q]);
				int b = max(RC, B[q]+1);
				int l = max(RC, L[q]);
				int r = max(RC, R[q]+1);

				int h = b-t;
				ans[q] += query(l, r, h);
			}
		}
	}

	sfx = cs = ds = deque<ll>(N+7);

	deque<ll> y(N);
	for(int i=0; i<N; i++)
		y[i] = Y[i];

	recalc(y, N-1);
	for(int q=0; q<Q; q++) {
		if(L[q] <= 0 && 0 <= R[q])
		ans[q] += query(T[q], B[q]+1, 1);
	}

	for(int i=1; i<RC; i++) {
		deque<ll> y2(N);
		y2[0] = X[i];
		for(int i=1; i<N; i++)
			y2[i] = (y2[i-1] == y[i] && y[i] == 0);

		y2.swap(y);

		recalc(y, N-1);

		for(int q=0; q<Q; q++) {
			if(L[q] <= i && i <= R[q])
				ans[q] += query(T[q], B[q]+1, 1);
		}
	}

	return ans;
}

#ifndef EVAL
int main() {
  int N;
  assert(1 == scanf("%d", &N));
  std::vector<int> X(N), Y(N);
  for (int i = 0; i < N; i++)
	cin >> X[i];
  for (int i = 0; i < N; i++)
	cin >> Y[i];
  int Q;
  assert(1 == scanf("%d", &Q));
  std::vector<int> T(Q), B(Q), L(Q), R(Q);
  for (int k = 0; k < Q; k++)
    assert(4 == scanf("%d%d%d%d", &T[k], &B[k], &L[k], &R[k]));
  fclose(stdin);

  std::vector<long long> C = mosaic(X, Y, T, B, L, R);

  int S = (int)C.size();
  for (int k = 0; k < S; k++)
    printf("%lld\n", C[k]);
  fclose(stdout);

  return 0;
}
#endif
