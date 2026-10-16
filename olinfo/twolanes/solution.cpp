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

int main() {
    int N;
    cin >> N;

    string L;
    cin >> L;

    string R;
    cin >> R;

    int ans = N;

    // INSERT YOUR CODE HERE
    for(int n=0; n<N; n++)
    {
        if(L[n]=='R' && R[n]=='R'){
            ans=n;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}

