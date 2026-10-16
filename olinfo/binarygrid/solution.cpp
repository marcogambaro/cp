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

#define ch(a, b, c) check(a, b, c, i-2)

int calc(vec<vec<bool>> &tb, int N, int M) {
	int x00 = 0, x01 = 1, x10 = 1, x11 = 2;

	auto check = [&](bool b0, bool b1, bool b2, int y) ->bool {
		for(int x=0; x<N; x++) {
			if((tb[x][y]^b0) == (tb[x][y+1]^b1) && (tb[x][y+1]^b1) == (tb[x][y+2]^b2)) return 0;
		}
		return 1;
	};

	for(int i=2; i<M; i++) {
		int n00, n01, n10, n11;
		n00 = n01 = n10 = n11 = 1e6;

		if(ch(0, 0, 0)) n00 = min(n00, x00);
		if(ch(0, 0, 1)) n01 = min(n01, x00+1);
		if(ch(0, 1, 0)) n10 = min(n10, x01);
		if(ch(0, 1, 1)) n11 = min(n11, x01+1);
		if(ch(1, 0, 0)) n00 = min(n00, x10);
		if(ch(1, 0, 1)) n01 = min(n01, x10+1);
		if(ch(1, 1, 0)) n10 = min(n10, x11);
		if(ch(1, 1, 1)) n11 = min(n11, x11+1);

		x00 = n00, x01 = n01, x10 = n10, x11 = n11;
	}

	return min({x00, x01, x10, x11});
}

void solve() {
	int N, M; cin >> N >> M;
	vector tb = vector(N, vector<bool>(M));
	vector tb2 = vector(M, vector<bool>(N));

	for(int i=0; i<N; i++) {
		string S; cin >> S;
		for(int j=0; j<M; j++)
			tb[i][j] = tb2[j][i] = S[j] - '0';
	}

	int k = calc(tb, N, M) + calc(tb2, M, N);
	if(k >= 1e6) cout << "-1\n";
	else cout << k << lf;
}

signed main(){	
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--) solve();
}

