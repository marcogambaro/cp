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

long long aggiorna(int N, vector<int> A, vector<int> B) {
    long long ris=0;

    int p=N-2;

    while(p!=-1)
    {
        if(A[p]+B[p] <= A[p+1])
        {
            int n = (A[p+1]-A[p]) / B[p];
            A[p] += B[p]*n;
            ris += n;
        }
        else
            p--;
    }

    return ris;
}

