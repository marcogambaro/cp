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

#include "message.h"

void send_message(std::vector<bool> M, std::vector<bool> C) {
	int N = M.size();
	M.push_back(1);
	M.resize(1025);

	vector<vector<bool>> tb(66, vector<bool>(31));

	int pos = 0;
	for(int i=0; i<31; i++) {
		if(C[i]) continue;

		int j = 0;
		for(; ;j++) {
			if(C[(i+j+1)%31] == 0) {
				tb[j++][i] = 1;
				break;
			}
			tb[j][i] = 0;
		}

		while(j < 66) tb[j++][i] = M[pos++];
	}

	infof("pos = %d", pos);
	assert(pos == 1025);

	for(auto &a: tb) send_packet(a);
}

std::vector<bool> receive_message(std::vector<std::vector<bool>> R) {
	vector<bool> ans;
	ans.reserve(1025);

	vector<int> cy(31);
	vector<int> cc;
	auto find = [&](int i, int t, auto &&find) -> bool {
		if(cy[i] == 0 && t == 16) return 1;
		if(cy[i] > 0) return 0;

		cy[i] = t;
		cc.push_back(i);
		int nx = 0;
		while(nx < 37 && R[nx][i] == 0) nx++;
		nx++;

		return find((i+nx)%31, t+1, find);
	};

	for(int i=0; i<31; i++) {
		fill(all(cy), -1);
		cc.clear();

		if(find(i, 0, find)) break;
	}

	for(int &j: cc) {
		int i = 0;
		while(R[i][j] == 0) i++;
		i++;

		while(i < 66) ans.push_back(R[i++][j]);
	}

	while(ans.back() == 0) ans.pop_back();
	ans.pop_back();
	return ans;
}
