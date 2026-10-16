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

#include "nile.h"

ll K = 0;

struct DSU {
	vector<ll> dsu, m, m0, m1;
	int N;

	DSU(vector<int> &v, vector<int> &a) {
		N = v.size();

		dsu = vector<ll>(N, -1);
		m = m0 = m1 = vector<ll>(N, 1e17);
		for(int i=0; i<N; i++) {
			if(i%2) m1[i] = a[i];
			else m0[i] = a[i];
		}
	}

	int rep(int n) {
		if(dsu[n] < 0) return n;
		return dsu[n] = rep(dsu[n]);
	}

	int size(int n) {
		return -dsu[rep(n)];
	}

	ll calc(int n) {
		if(size(n)%2 == 0) return 0;
		if(n%2) return min(m1[n], m[n]);
		else return min(m0[n], m[n]);
	}

	void join(int a, int b, ll t) {
		a = rep(a);
		b = rep(b);

		assert(a != b);
		if(a > b) swap(a, b);
		K -= calc(a);
	    K -= calc(b);

		m0[a] = min(m0[a], m0[b]);
		m1[a] = min(m1[a], m1[b]);
		dsu[a] += dsu[b];
		dsu[b] = a;


		m[a] = min(m[a], m[b]);
		K += calc(a);
	}

	void upd(int n, ll t) {
		n = rep(n);

		K -= calc(n);
		m[n] = min(m[n], t);
		K += calc(n);
	}
};

std::vector<long long> calculate_costs(vector<int> W, vector<int> A,  vector<int> B, vector<int> E) 
{
	int N = A.size();
	ll ansb = 0;

	for(int i=0; i<N; i++) A[i] -= B[i], ansb += B[i];

	vector<int> id(N);
	iota(all(id), 0);
	sort(all(id), [&](int &i, int &j){return W[i]<W[j];});

	vector<int> W2(N), A2(N);
	for(int i=0; i<N; i++) {
		W2[i] = W[id[i]];
		A2[i] = A[id[i]];
	}
	swap(W, W2);
	swap(A, A2);

	// all weigths sorted - much better!

	K = accumulate(all(A), 0LL);
	DSU dsu(W, A);

	int Q = E.size();
	id.resize(Q);
	iota(all(id), 0);
	sort(all(id), [&](int &i, int &j){return E[i]<E[j];});
	vector<ll> ans(Q, ansb);


	vector<int> diff(N-1);
	iota(all(diff), 0);
	sort(all(diff), [&](int &i, int &j){return W[i+1]-W[i] > W[j+1]-W[j];});

	priority_queue<array<ll, 3>> pq;
	for(int i=1; i<N-1; i++) {
		pq.push( {-(W[i+1]-W[i-1]), i, A[i]});
	}

	for(auto &i: id) {
		ll q = E[i];

		while(!diff.empty() && W[diff.back()+1] - W[diff.back()] <= q) {
			dsu.join(diff.back(), diff.back()+1, W[diff.back()+1] - W[diff.back()]);
			diff.pop_back();
		}

		while(!pq.empty()) {
			auto [t, n, qt] = pq.top();
			t /= -1;
			if(t > q) break;
			pq.pop();

			dsu.upd(n, qt);
		}

		ans[i] += K;
	}

	return ans;
}


#ifdef LOCAL
int main() {
  int N;
  assert(1 == scanf("%d", &N));
  std::vector<int> W(N), A(N), B(N);
  for (int i = 0; i < N; i++)
    assert(3 == scanf("%d%d%d", &W[i], &A[i], &B[i]));
  int Q;
  assert(1 == scanf("%d", &Q));
  std::vector<int> E(Q);
  for (int j = 0; j < Q; j++)
    assert(1 == scanf("%d", &E[j]));
  fclose(stdin);

  std::vector<long long> R = calculate_costs(W, A, B, E);

  int S = (int)R.size();
  for (int j = 0; j < S; j++)
    printf("%lld\n", R[j]);
  fclose(stdout);

  return 0;
}
#endif
