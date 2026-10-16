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

long long conta(int N, vector<int> A) {
	ll ans = 0;

	stack<pair<ll, ll>> s;
	auto clear = [&]() -> void {
		while(!s.empty()) s.pop();
	};

	vector<int> high(N), low(N);
	
	s.push({2e9, -1});
	for(int i=0; i<N; i++) {
		while(s.top().fi < A[i]) s.pop();
		high[i] = s.top().se;
		s.push({A[i], i});
	}

	clear();

	s.push({-1, -1});
	for(int i=0; i<N; i++) {
		while(s.top().fi > A[i]) s.pop();
		low[i] = s.top().se;
		s.push({A[i], i});
	}

	clear();

	ll ks = 0;

	for(int i=1; i<N; i++) {
		if(A[i] > A[i-1]) {
			int pv = i;
			while(!s.empty() && s.top().fi > high[i]) {
				if(s.top().se) ks -= pv-s.top().fi;
				pv = s.top().fi;
				s.pop();
			}
			if(!s.empty() && s.top().se) ks -= pv-s.top().fi;

			if(!s.empty() && s.top().se) ks += high[i]+1 - s.top().fi;
			s.emplace(high[i]+1, 1);
			s.emplace(i, 0);
			ks += i-high[i]-1;			
		}
		else {
			int pv = i;
			while(!s.empty() && s.top().fi > low[i]) {
				if(s.top().se) ks -= pv-s.top().fi;
				pv = s.top().fi;
				s.pop();
			}
			if(!s.empty() && s.top().se) ks -= pv-s.top().fi;

			if(!s.empty() && s.top().se) ks += low[i]+1 - s.top().fi;
			s.emplace(low[i]+1, 0);
			s.emplace(i, 0);
		}

		ans += ks;
	}

	return ans;
}

#ifndef EVAL
int main() {
    cin.exceptions(istream::failbit);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int& i : A) {
        cin >> i;
    }

    cout << conta(N, A);

    cout << endl;

    return 0;
}
#endif

