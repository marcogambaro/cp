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

struct PAIR
{
	int a, b;
	int pos;
	
	bool operator <(PAIR o) const{
		if(a!=o.a)
			return a<o.a;
		return b<o.b;
	}
};

vector <int> ans;

vector<int> count(int N, vector<int> S, vector<int> P)
{
	vector<PAIR> v(N);
	for(int i=0; i<N; i++)	
		v[i] = { S[i], 1e6+5-P[i], i};
		
	sort(v.begin(), v.end());
	
//	deque <int> dp(N); //dp[i] = -1 se il materiale i è sempre ottimale,
//					   //      = n se l'unico materiale sovrastante i è n
//					   //      = -2 se ci sono due o + materiali che sovrastano i
	
	int tot = 0; //numero totale di -1;
	vector <int> ns(N);
	map <int, int> sty; //y già uscite sulle x precedenti
	int high_y = -1;
	
	int p = N-1;
	
	while(p+1)
	{
		int nowx = v[p].a;
		stack<pair<int, int>> sk;
		while(v[p].a == nowx)
		{
			sk.push({v[p].b, v[p].pos});
			auto it = sty.upper_bound(v[p].b);
			
			if(it == sty.end()) //materiale pos è sempre ottimale
			{
				//dp[v[p].pos] = -1;
				tot++;
				ns[v[p].pos]--;
			}
			else if(it->first == high_y) //materiale pos è ottimale solo quando viene scelto un elemento specifico
			{
				//dp[v[p].pos] = it->second.second;
				ns[it->second]++;
			}
			else; //materiale pos non è mai ottimale
			p--;
		}
		
		while(!sk.empty())
		{
			sty[sk.top().first] = sk.top().second;
			high_y = max(high_y, sk.top().first);
			sk.pop();
		}
	}
		
	
	for(int item: ns) ans.push_back(tot + item);
	
	return ans;
}


