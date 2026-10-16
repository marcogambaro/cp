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

#include "fish.h"

vec<vec<pll>> sfx;
int N, M;
vec<int> X, Y, W;

void calcsfx() {
    sfx.resize(N+1);
    for(int i = 0; i < M; i++) {
        sfx[X[i]].push_back({Y[i], W[i]});
    }

    for(int i = 0; i < N; i++) {
        sort(all(sfx[i]));
        for(int j = sfx[i].size()-2; j >= 0; j--)
            sfx[i][j].se += sfx[i][j+1].se;
    }
}

ll get(int i, int y) {
    pll p = {y, -1};
    int j = lower_bound(all(sfx[i]), p) - sfx[i].begin();
    if(j == sfx[i].size()) return 0;
    return  sfx[i][j].se;
}

ll get(int i, int yl, int yr) {
	if(i < 0 || i >= N) return 0;
    return max(get(i, yl) - get(i, yr), 0LL);
}

void chmax(ll &a, ll b) {
	a = max(a, b);
}

ll solve() {
    vec<ll> AB, Ab, aB, ab, pos;
    AB = Ab = aB = ab = {{0}};
	pos = {-1};

    for(int i=0; i<N; i++) {
        vec<ll> AB2, Ab2, aB2, ab2;
        ll nAB = 0, nAb = 0, naB = 0, nab = 0;

        vec<ll> p = {-1};
        if(i > 0) for(pll x: sfx[i-1]) p.push_back(x.fi);
        if(i < N-1) for(pll x: sfx[i+1]) p.push_back(x.fi);

        sort(all(p));

        int j = 0;

        for(int h: p) {
            while(j < pos.size() && pos[j] <= h) {
				ll extra = get(i-1, 0, pos[j]+1);
				nAB = max(nAB, AB[j]);
				nAb = max(nAb, Ab[j]);
				naB = max(naB, aB[j] - extra);
				nab = max(nab, ab[j] - extra);
				j++;
			}

			AB2.push_back(nAB);
			Ab2.push_back(nAb);
			aB2.push_back(naB + get(i-1, 0, h+1));
			ab2.push_back(nab + get(i-1, 0, h+1));
        }

		nAB = 0, nAb = 0, naB = 0, nab = 0;
		j = pos.size()-1;

		for(int ii = p.size()-1; ii >= 0; ii--) {
			int h = p[ii];

			while(j >= 0 && pos[j] >= h) {
				ll extra = get(i, 0, pos[j]+1);
				nAB = max(nAB, AB[j] + extra);
				nAb = max(nAb, Ab[j]);
				naB = max(naB, aB[j] + extra);
				nab = max(nab, ab[j]);
				j--;
			}

			chmax(AB2[ii], nAB - get(i, 0, h+1));
			chmax(Ab2[ii], nAb);
			chmax(aB2[ii], naB - get(i, 0, h+1));
			chmax(ab2[ii], nab);
		}

		AB = Ab = aB = ab = vec<ll>(p.size());

		infof("------ i = %d", i);
		for(int ii = 0; ii < p.size(); ii++) {
			AB[ii] = max(AB2[ii], aB2[ii]);
			Ab[ii] = max(AB2[ii], aB2[ii]);
			aB[ii] = max(Ab2[ii], ab2[ii]);
			ab[ii] = max(Ab2[ii], ab2[ii]);
			infof("h = %lld: - AB = %lld, Ab = %lld, aB = %lld, ab = %lld", p[ii], AB[ii], Ab[ii], aB[ii], ab[ii]);
		}

		p.swap(pos);
    }

	ll ans = max({
		*max_element(all(AB)),
		*max_element(all(Ab)),
		*max_element(all(aB)),
		*max_element(all(ab))
	});

    return ans;
}

long long max_weights(int N, int M, vector<int> X, vector<int> Y, vector<int> W) {
    ::N = N;
    ::M = M;
    ::X.swap(X);
    ::Y.swap(Y);
    ::W.swap(W);

    calcsfx();
    return solve();
}

#ifndef EVAL
signed main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));

  std::vector<int> X(M), Y(M), W(M);
  for (int i = 0; i < M; ++i) {
    assert(3 == scanf("%d %d %d", &X[i], &Y[i], &W[i]));
  }

  long long result = max_weights(N, M, X, Y, W);
  printf("%lld\n", result);
  return 0;
}
#endif
