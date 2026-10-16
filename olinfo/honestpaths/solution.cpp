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

int N, M;
struct Dt{
	int n, from;
	ll p;

	bool operator<(Dt other) const{
		return p > other.p;
	}
};


int main()
{	
	ios_sync();
	
	cin >> N >> M;
	vector<vector<pair<int, int>>> G(N+1);
	bitset<500005> done;
	vector<ll> dist(N+1);
	priority_queue<Dt> pq;
	pq.push({N, 0, 0});

	for(int i=0; i<M; i++) {
		int a, b, c; cin >> a >> b >> c;
		G[a].push_back({b, c});
		G[b].push_back({a, c});
	}

	deque<pair<int, ll>> dp;
	while(!pq.empty())
	{
		Dt node = pq.top(); pq.pop();
		if(done[node.n]) continue;
		done[node.n] = 1;
		dp.push_back({node.n, node.p});
		dist[node.n] = node.p;

		for(auto [n2, p2]: G[node.n]) {
			if(!done[n2]) 
				pq.push({n2, node.n, node.p+p2});
		}
	}

	infon("dp contents:");
	if(dbg) for(auto[a, b]: dp) infon(a, " ", b);
	infon("================");

	//dp indica l'ordine dei nodi secondo dijstra
	vector<pair<int, ll>> best(N+1, {-1, -1}); //nodo a cui punta, lungh. percorso
	int start = 0;
	dp.pop_front();
	best[N] = {0, 0};
	for(auto [n, p]: dp)
	{
		for(auto [n2, p2]: G[n]) 
		{
			if(best[n2].first == -1) continue;
			if(dist[n2] >= dist[n]) continue;
			
			if(best[n2].second+p2 > best[n].second) {
				best[n] = {n2, best[n2].second + p2};
			}
		}
	
		if(best[n].second > best[start].second)
			start = n;
	}

	if(dbg) {
		for(int i=1; i<=N; i++) {
			infon("best ", i, ": ", best[i].first, " ", best[i].second);
		}
	}

	cout << best[start].second << " ";
	queue<int> st;
	while(start != N) {
		st.push(start);
		start = best[start].first;
	}
	st.push(N);

	cout << st.size() << "\n";
	while(!st.empty()) cout << st.front() _"", st.pop();
}


