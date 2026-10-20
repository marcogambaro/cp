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


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vec<int> ins = {5, 7, 13, 19, 23, 31, 47, 61, 83, 97};

    for(int i=0; i<ins.size(); i++) {
        ofstream out("output_00" + to_string(i) + ".txt");
        int N = ins[i];

        for(int s = 0; s < N; s++) {
            for(int k = 0; k < N; k++) {
                for(int i = 0; i < N; i++) {
                    out << i*N + (k+s*i)%N << " ";
                }
                out << N*N+s << lf;
            }
        }

        for(int i = 0; i < N*N+N; i++) {
            out << i << " ";
            if(i % N == N-1) out << N*N+N << lf;
        }
    }
}
