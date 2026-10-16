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
mt19937 timmy_loves_gambling2(73);

#include "partition.h"

signed main() {
    int N = 10, M = 20;
    uniform_int_distribution<int> dm(1, M);
    uniform_int_distribution<int> dn(2, N);

    while(1) {
        int K = dn(timmy_loves_gambling2);
        cout << N _ K _ M _ lf << "";

        vec<int> A(N);
        for(int &i: A) {
            i = dm(timmy_loves_gambling2);
            cout << i << " ";
        }
        cout << lf;

        vec<int> B = add_numbers(A, K, M);

        for(int i: A) B.push_back(i);
        sort(all(B));
        cout << "B: ";
        for(int i: B) cout << i << " ";
        cout << lf;

        vec<int> ans = find_partition(B, K);
        cout << "ans: ";
        for(int i: ans) cout << i << " ";
        cout << lf;

        vec<ll> s(K, 0);
        for(int i=0; i<B.size(); i++) {
            if(ans[i] == -1) {
                cout << "ERROR\n";
                exit(0);
            }
            s[ans[i]] += B[i];
        }

        cout << "s: ";
        for(ll i: s) cout << i << " ";
        cout << lf;

        for(int i=1; i<K; i++) {
            if(s[i] != s[i-1]) {
                cout << "ERROR\n";
                exit(0);
            }
        }
    }
}
