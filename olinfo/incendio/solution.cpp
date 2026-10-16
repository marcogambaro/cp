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

ll ans = LLONG_MAX;
int N;

ll calc(pair<int, int> a, pair<int, int> b) {
	int dx = abs(a.first - b.first);
	int dy = abs(a.second - b.second);

	return (dx+dy - ((dx!=0 && dy!=0) ? 1: 0))/2;
}

struct dt {
	ll x, y;

	ll proc(dt dt1) {
		if(x < 0 && dt1.x < 0) return 1e17;

		if(dt1.x == -1) return min(y, N-1-x);
		if(x == -1) return min(dt1.y, N-1-dt1.x);

		if(x == -2) return min(dt1.x, N-1-dt1.y);
		if(dt1.x == -2) return min(x, N-1-y);


		return calc({x, y}, {dt1.x, dt1.y});
	}

	bool operator<(dt &o) const {
		if(x != o.x) return x<o.x;
		return y<o.y;
	}
};


int alzati(int N, int M, int X[], int Y[])
{
	::N = N;

	vector<dt> nodi;
	vector<ll> d;
	for(int i=0; i<M; i++) {
		nodi.push_back({X[i], Y[i]});
		d.push_back(1e17);
	}

	d.push_back(0);
	nodi.push_back({-1, -1});
	d.push_back(1e17);
	nodi.push_back({-2, -2});

	vector<bool> done(M+2);

	for(int i=0; i<M+2; i++) {
		pair<ll, ll> m = {1e17, -1};

		for(int j=0; j<M+2; j++) {
			if(done[j]) continue;
			if(d[j] < m.first) m = {d[j], j};
		}

		done[m.second] = 1;
		for(int j=0; j<M+2; j++) {
			d[j] = min(d[j], max(d[m.second], nodi[j].proc(nodi[m.second])));
		}
	}

	return d.back()-1;
}

#ifdef LOCAL
int main() {

  int N, M;

  assert(2==scanf("%d %d", &N, &M));

  int *X = (int*) malloc(M * sizeof(int));
  int *Y = (int*) malloc(M * sizeof(int));

  for(int i=0; i<M; i++)
    assert(2==scanf("%d %d", X+i, Y+i));

  printf("%d\n", alzati(N, M, X, Y));
  return 0;
}
#endif

