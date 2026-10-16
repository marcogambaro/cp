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

int N;
vector<vector<int>> G;
vector<bool> route; //indica i nodi da percorrere
long long ans;

bool ok = 0;

bool esplora(int n, int from)
{
	bool res = 0;
	if(n == N-1)
	{
		res = 1;
	}
	
	for(int n2: G[n])
	{
		if(n2 == from) continue;
		
		res |= esplora(n2, n);
	}
	
	route[n] = res;
	if(res == 0) ok = 1;
	return res;
}

vector<int> calcola;
vector<bool> done;

queue<int> q;
ll t;

bool go() //ritorna false se ho finito
{
	int n = q.front();
	q.pop();
	
	
	
	if(n == -1)
	{
		t++;
		if(q.size() == 0) return false;
		q.push(-1);
		return true;
	}
	
	if(done[n]) return true;
	
	ans += t;
	calcola[n] = t;
	done[n] = 1;
	
	for(int n2: G[n])
	{
		//if(done[n2]) continue;
		
		q.push(n2);
	}
	
	return true;
}

long long atterra(int N, vector<int> U, vector<int> V)
{
	G.resize(N);
	::N = N;
	for(int i=0; i<N-1; i++)
	{
		int a = U[i];
		int b = V[i];
		
		G[a].push_back(b);
		G[b].push_back(a);
	}
	
	route.resize(N);
	route[0] = 1;
	esplora(0, -1);
	
	if(ok == 0)
		return -1;
	
	
	
	for(int i=0; i<N; i++)
	{
		if(route[i] == 0)
		{
			q.push(i);
		}
			
	}
	q.push(-1);
	t = 0;
	
	
	calcola.resize(N);
	done.resize(N);
	while(go());
	
		
	
	
	return ans;
}
//
//int main(void) {
//    ios::sync_with_stdio(0);
//    cin.tie(0), cout.tie(0);
//
//    int N; cin >> N;
//
//    vector<int> U(N - 1), V(N - 1);
//    for(int i = 0; i < N - 1; ++i)
//        cin >> U[i] >> V[i];
//
//    cout << atterra(N, U, V) << endl;
//}

