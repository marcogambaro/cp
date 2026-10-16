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


int N, M;
struct Dt{
	int n, from;
	ll p;

	bool operator<(Dt other) const{
		return p > other.p;
	}
};


int main()
{	
	cin >> N;

	ll ans = 0;
	for(int i=0; i<N; i++)
	{

int x; cin >> x;
ans += max(0, x-1);

	}

	cout << ans;
}


