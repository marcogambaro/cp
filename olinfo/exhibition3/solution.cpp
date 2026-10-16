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

string S, T;
vector<vector<int>> G, Gr;
vector<int> dg;
vector<int> stat;

void make0(int v) {
	if(S[v] =='0') return;
	S[v] = '0';
	stat[v] = 2;
	for(auto &u: Gr[v]) {
		dg[u]--;
		if(dg[u] == 0 || T[u] == 'C') make0(u);
	}
}

void findc(int v) {
	if(stat[v] == 1 || stat[v] == 2) return;
	stat[v] = 1;

	for(auto &u: G[v]) {
		if(T[u] == 'D') continue;
		if(stat[u] == 1) make0(v);
		else findc(u);
	}
	stat[v] = 2;
}

signed main(){	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);   
    
	int N; cin >> N;
    int M; cin >> M;
	cin >> T;
	S.resize(N, '1');
	G.resize(N);
	dg.resize(N);
	stat.resize(N);
	Gr.resize(N);

	for(int i=0; i<M; i++) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		Gr[b].push_back(a);
		dg[a]++;
	}

	for(int i=0; i<N; i++) {
		if(T[i] == 'C') findc(i);
		if(G[i].size() == 0) make0(i);
	}

	cout << S;
}



