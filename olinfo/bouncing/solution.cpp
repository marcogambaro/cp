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

ll N, M, px, py, a, b, T, rx, ry;
ll TP; //periodo
ll ans;

void calcTP() {
	TP = M*N*2/gcd(M*a, N*b);
}

pair<ll, ll> extgcd(ll a, ll b) {
	if(b == 0) return {1, 0};
	auto [x, y] = extgcd(b, a%b);
	return {
		y,
		x - (a/b)*y
	};
}

pair<ll, ll> findt(ll k, ll a, ll N) {
	if(k == 0) return {0, N/gcd(a, N)};
	ll g = gcd(N, a);
	if(k % g != 0) return {-1, -1};
	k /= g;
	a /= g;
	N /= g;

	// inv(a) * a + h*N = 1
	auto [i, h] = extgcd(a, N);
	i = (i%N + N)%N;
	return {k*i %N, N};
}

ll calc(ll rx, ll ry) {
	if(a == 0) {
		if(rx != px) return 0;
		return (T*b)/M + ((T*b)%M >= (ry-py+M)%M);
	}
	if(b == 0) {
		if(ry != py) return 0;
		return (T*a)/N + ((T*a)%N >= (rx-px+N)%N);
	}

	auto [ka, ta] = findt((rx-px+N)%N, a, N);
	auto [kb, tb] = findt((ry-py+M)%M, b, M);
	if(ka == -1 || kb == -1) return 0;

	// CRT
	// s = ka + ha*ta
	// s = kb + hb*tb
	ll g = gcd(ta, tb);
	assert(ta*tb/g == TP);
	if(ka%g != kb%g) return 0;
	
	auto [ha, hb] = extgcd(ta, tb);
	ha *= (kb - ka)/g;
	ha = (ha%tb +tb)%tb;

	ll s = ka + ha*ta;
	return T/(TP) + (T%TP >= s%TP);
}


signed main(){	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N >> M >> T >> px >> py >> a >> b >> rx >> ry;
	if(a < 0) {
		a*=-1;
		px = N-px;
		rx = N-rx;
	}
	if(b < 0) {
		b*=-1;
		py = M-py;
		ry = M-ry;
	}
	if(a*b != 0) {
		ll g = gcd(a, b);
		a /= g;
		b /= g;
		T *= g;
		calcTP();
	}

	N*=2; M*=2;
	ans += calc(rx, ry);
	ans += calc(N-rx, ry);
	ans += calc(rx, M-ry);
	ans += calc(N-rx, M-ry);
	cout << ans << "\n";
}




