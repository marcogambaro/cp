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

constexpr int LOG = 30;

int main() {
    // uncomment the two following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int N, Q;
    cin >> N >> Q;

    vector<int> V(N + 1);
    for (int i = 1; i <= N; ++i)
        cin >> V[i];

    vector<vector<int>> queries(Q + 1, vector<int>(2));
    for (int j = 1; j <= Q; ++j) {
        for (int i = 0; i < 2; ++i)
            cin >> queries[j][i];
    }

    vector<int> ans(Q + 1);

	vector<int> reach(22); //ciò che può essere raggiunto dal bit i
	for(int i=0; i<22; i++) {
		reach[i] = (1 << i);
		for(int x: V) {
			if(x & (1<<i))	reach[i] |= x;
		}
	}

	int i=-1;
    for(auto &v: queries) {
		i++;
		int a = V[v[0]];
		int b = V[v[1]];

		ans[i] = 1;

		while(ans[i] < 20) {
			if(a & b) 	break;

			int c = a;
			for(int j=0; j<22; j++) {
				if(a & (1 << j)) c |= reach[j];
			}
			a = c;
			ans[i]++;
		}

		if(ans[i] == 20) ans[i] = -1;
	}


    for ( i = 1; i <= Q; ++i)
        cout << ans[i] << "\n";

    return 0;
}

