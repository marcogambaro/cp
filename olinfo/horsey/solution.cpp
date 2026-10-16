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

string NOPE = "NO\n", YUP = "YES\n";


bool are_primes(ll x, ll y) {
	if(gcd(x,y) == 1) return 1;
	return 0;
}

void solve() {
	ll n, m, a, b;
	cin >> n >> m >> a >> b;

	if(n < m) swap(n, m);
	if(a < b) swap(a, b);

	if((a+b)%2 == 0) {
		cout << "NO\n";
	}
	else if(gcd(a, b) != 1) {
		cout << "NO\n";
	}
	else if(m < a+b) {
		cout << "NO\n";
	}
	else if(n < a*2) {
		cout << "NO\n";
	}
	else cout << "YES\n";
}


int main()
{	
	ios_sync();
	int t; cin >> t;
	while(t--) solve();
	
}




