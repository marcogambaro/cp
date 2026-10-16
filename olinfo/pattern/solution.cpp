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

int S, N;
map<pair<int, int>, set<pair<int, int>>> mp;

signed main(){	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<int> sx, sy, mx, my;

    cin >> S;
	sx = sy = mx = my = vector<int>(S);
	int pvc, pvd;
	for(int i=0; i<S; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		sx[i] = c-a, sy[i] = d-b;
		if(i != 0) mx[i] = a-pvc, my[i] = b-pvd;
		pvc = c;
		pvd = d;
	}

	cin >> N;
    for(int i=0; i<N; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		pair<int, int> p1 = {a, b}, p2 = {c, d};
		mp[p1].insert(p2);
		mp[p2].insert(p1);
	}

	int ans = 0;
	for(auto pp: mp) {
		pair<int, int> p = pp.first;

		bool win = 1;
		for(int i=0; i<S; i++) {
			if(i != 0) {
				p.first += mx[i];
				p.second += my[i];
			}
			if(mp[p].count({p.first + sx[i], p.second + sy[i]}) == 0) {
				win = 0;
				break;
			}
			p.first += sx[i];
			p.second += sy[i];
		}

		if(win) ans++;
	}
	cout << ans << "\n";
}




