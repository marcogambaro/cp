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

#define data aooo

ll N, M;
vector<vector<ll>> Vm; //V[m] contine i valori che hanno modulo i, sortati
vector<ll> start_pt;
vector<vector<ll>> G;

void get() {
	Vm.resize(M);
	start_pt.resize(M);
	G.resize(M, vector<ll>(M, -1));
}

struct data{
	pair<ll, ll> n;
	ll p;
	vector<ll> pt; 		//puntatori sul vettore Vm

	data(vector<ll> &start, pair<ll, ll> node) {
		p = 0;
		n.swap(node);
		pt.swap(start);
	}

	data(ll peso, pair<ll, ll> node, vector<ll> old, ll inc) {
		p = peso;
		n = node;
		pt = old;
		pt[inc]++;
	}

	bool operator<(data o) const{
		return p > o.p; //simulo dijstrka
	}
};

priority_queue<data> q;

int main() {
	cin >> N >> M;
	get();

	if(M > N) {
		cout << 0;
		return 0;
	}

	ll sum = 0;
	for(int i=0; i<N; i++) {
		ll x; 	cin >> x;
		sum += x;
		Vm[x%M].push_back(x);
	}

	//sorta Vm
	for(int i=0; i<M; i++)
		sort(Vm[i].begin(), Vm[i].end());

	//creo il "grafo" e runno dijstrika
	q.push(data(start_pt, {N % M, sum % M}));

	while(!q.empty() && G[0][0] == -1)
	{
		data dt = q.top(); q.pop();
		if(G[dt.n.first][dt.n.second] != -1) continue;
		G[dt.n.first][dt.n.second] = dt.p;


		for(int i=0; i<M; i++) {
			if(dt.pt[i] == Vm[i].size()) continue;

			ll c = Vm[i][ dt.pt[i] ];
			ll a = (dt.n.first + M - 1) %M;
			ll b = (dt.n.second + M - c) %M;

			if(G[a][b] != -1) continue;
			q.push( data(dt.p + c, {a, b}, dt.pt, i) );
		}
	}

	if(G[0][0] == -1) 	cout << 0;
	else 				cout << sum - G[0][0];
}

