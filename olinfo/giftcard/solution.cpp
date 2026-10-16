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

#define i2 __int128

array<i2, 2> extgcd(i2 a, i2 b) { //ax + by = gcd(a, b)
	//if(b == 0) return {1, 0};
	if(a%b == 0) return {0, 1};
	auto [x, y] = extgcd(b, a%b);
	return {
		y,
		x - y*(a/b)
	};
}

int solve(){
    i2 n, a, b;
	u64 q1, q2, q3; cin >> q1 >> q2 >> q3;
	n = q1, a = q2, b = q3;

	i2 g = gcd(a, b);
	assert(n%g == 0);
	a /= g;
	b /= g;
	n /= g;
	n -= a+b;

	if(n == 0) {
		cout << "1 1\n";
		return 0;
	}

	bool sw = 0;
	if(a > b) swap(a, b), sw = 1;

	auto [x, y] = extgcd(a, b);
	x *= n, y *= n;

	i2 k;
	if(x < 0) {
		k = (-x-1)/b+1;
	}
	else {
		k = x/b*-1;
	}

	i2 ans1 = x+k*b;
	i2 ans2 = y-k*a;

	if(sw) swap(ans1, ans2);
	cout << (ll)ans1+1 _ (ll)ans2+1 << "\n";
	return 0;
}

signed main() {
	int t=1;
	if(DBG) {
		cin  >> t;
	}

	while(t--) solve();
}

