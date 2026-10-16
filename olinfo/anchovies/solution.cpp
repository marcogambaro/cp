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


signed main()
{
    int N; cin >> N;
    vector<int> v(N);
    readv(v);

    if(N == 1) {cout << 0; return 0;}

    int m = v[0];
    int ans = 0;
    for(int i=1; i<N; i++)
    {
        ans = max(ans, v[i]-m);
        m = min(m, v[i]);
    }
    cout << ans;
}

