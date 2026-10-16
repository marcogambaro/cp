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

int N, Q;

int prev(int i) {
	if(i == 0) return N-1;
	return i-1;
}

int suc(int i) {
	if(i == N-1) return 0;
	return i+1;
}

signed main(){	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	cin >> Q;

    vector<int> V(N);
	readv(V);

	int ans = 0;
	map<int, int> mp;

	int act = 1;
	for(int i=1; i<N; i++) {
		if(V[i] <= V[i-1]) {
			mp[i-1] = act;
			act = 1;
		}
		else act++;
	}

	if(V[0] <= V[N-1]) {
		mp[N-1] = act;
	}
	else {
		auto it = mp.begin();
		it->second += act;
	}

	for(auto &[k, v]: mp) ans += v/2;
	cout << ans << " ";

	while(Q--) {
		int k, x; cin >> k >> x;

		auto it = mp.lower_bound(k);
		if(it == mp.end()) it = mp.begin();

		//rapporto con elemento precedente
		if(V[prev(k)] < x) {
			//i range si uniscono se non lo erano già
			auto pv = it;
			if(it == mp.begin()) pv=mp.end();
			pv--;

			if(pv->first == prev(k)) {
				if(it == pv) {
					mp.erase(it);
					mp[k] = N;
					ans = N/2;
					it = mp.end();
				}
				else {
					ans -= it->second/2;
					it->second += pv->second;
					ans += it->second/2;
					ans -= pv->second/2;
					mp.erase(pv);
				}
			}
		}
		else {
			//i range si separano se non lo erano già
			auto pv = it;
			if(it == mp.begin()) pv=mp.end();
			pv--;

			if(pv->first != prev(k)) {
				mp[prev(k)] = (prev(k) - pv->first + N)%N;
				ans += mp[prev(k)]/2;
				ans -= it->second/2;
				it -> second -= (prev(k) - pv->first + N)%N;
				ans += it->second/2;
			}
		}

		//rapporto con elemento successivo
		if(it != mp.end() && x < V[suc(k)]) {
			//unisco i range, se non lo erano già
			auto sc = it;
			sc++;
			if(sc == mp.end()) sc = mp.begin();

			if(it->first == k) {
				ans -= it->second/2;
				ans -= sc->second/2;
				sc->second += it->second;
				ans += sc->second/2;
				mp.erase(it);
			}
		}
		else if(it != mp.end()){
			//i range si separano, se non lo erano già
			auto pv = it;
			if(it == mp.begin()) pv=mp.end();
			pv--;

			auto sc = it;
			// sc++;
			// if(sc == mp.end()) sc = mp.begin();

			if(it->first != k) {
				mp[k] = (k - pv->first +N)%N;
				ans += mp[k]/2;
				ans -= sc->second/2;
				sc->second -= (k - pv->first +N)%N;
				ans += sc->second/2;
			}
		}

		V[k] = x;
		cout << ans << " ";
	}
}
/*
4 2
1 2 3 4
0 5
1 6
*/




