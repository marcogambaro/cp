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

bool attack(int P);

vector<vector<long long>> dp;
int K, N;

void init(int N, int K)
{
    ::K = K;
    ::N = N;

    dp.resize(2);

	//inizializza v[1]
	dp[0].push_back(1);
	for(int i=0; i<=N; i++) {
		dp[1].push_back(i);
	}

    for(int i=2; i<=K; i++)
    {
        vector<ll> v = {0};

        for(int j=1; ;j++)
        {
            if(j < i)       v.push_back(dp[i-1][j]);
            else if(i == j) v.push_back(dp[i-1][j] + 1);
            else            v.push_back(v[j-1] + dp[i-1][j-1] + 1);

            if(v[j] >= N) {
                dp.push_back(v);
                break;
            }
        }
    }
}

int binsearch() {
    int l = -1;
    int r = N-1;

    while(l != r) {
        int m = l + (r-l+1)/2;

        if(m == N) return l+1;

        if(attack(m)) {
            l = m;
        }
        else
            r = m-1;
    }

    return l+1;
}

int new_pokemon() {
    if( ceil(log2(N+1)) <= K) {
		return binsearch();
	}

	int l = -1;
    int r = N-1;

    int i = K;
    int j = dp[i].size()-1;

    while(l != r) {
        int m = l + dp[i][j] - dp[i][j-1];
        bool x = attack(min(m, r));

        if(x) {
            l = min(m, r);
        }
        else {
            i--;
            r = min(m,r)-1;
        }

        j--;
    }

    return l+1;
}

#ifndef EVAL
int main() {
    int n, k;
    cin >> n >> k;

    init(n, k);
    cout << new_pokemon();
}

bool attack(int p) {
    cout << "attacked position "<< p <<"! \n";
    int x;
    cin >> x;
    return (bool)x;
}
#endif

