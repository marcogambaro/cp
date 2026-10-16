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


signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int t; cin >> t;
	while(t--) {
		ll a, b, k;
		cin >> a >> b >> k;
		a += k;

		ll ans = 1;
		ll S = a+b;
		for(ll q = 2; q <= sqrt(S)+1; q++) {
			if(S % q == 0) {
				if(a % q <= k) ans = max(ans, q);
				if(a % (S/q) <= k) ans = max(ans, S/q);
			}
		}
		cout << ans << "\n";
	}
}

