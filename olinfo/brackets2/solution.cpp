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

    vector<int> A(N);
    for (int i = 0; i < N; ++i)
        cin >> A[i];


    vector<vector<int>> ops;
    vector<int> vold = {-100};
    for(int x: A)
    {
        vector<int> vnew(vold.size() + x, -1);
        static int j = 0;
        j++;

        for(int i=0; i<vold.size(); i++) {
            if(vold[i] == -1) continue;

            vnew[i+x] = i;
            if(i-x >= 0) vnew[i-x] = i;

        }

        ops.push_back(vold);
        vnew.swap(vold);

        if(j == N) ops.push_back(vold);
    }

    if(ops[N][0] == -1) {
        cout << -1 << "\n";
        return 0;
    }

    //eseguo operazioni a ritroso
    stack<int> s;
    int p = 0;
    for(int i = N; i>0; i--) {
        s.push(p - ops[i][p]);
        p = ops[i][p];
    }


    while(!s.empty()) {
        int x = s.top();
        s.pop();

        if(x > 0) {
            for(int i=0; i<x; i++) cout << "(";
        }
        else
        {
            for(int i=0; i<-x; i++) cout << ")";
        }
    }

    return 0;
}

