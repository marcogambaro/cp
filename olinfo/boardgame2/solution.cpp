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

vector<vector< pii >> rG;
vector<int> dp;
vector<bool> fg;
vector<ll> prizew, prizel;
queue<int> q;

ll smin(ll a, ll b) //fuznione min che ritorna b se a == -1
{
	//if(a == LLONG_MAX) return b;
	return min(a, b);
}

void gestisci_dp(int& x, int n2, int n1, ll p)
{
	if(dp[n1] == 0) //il prossimo dp varrà sicuramente 1
	{
		if(x == 1)
		{
			x = 1;
			q.push(n2);
			prizew[n2] = p + prizel[n1];
			prizel[n2] = prizew[n1];
		}
		else if(x == -1)
		{
			x = 1;
			q.push(n2);	
			prizew[n2] = smin(prizew[n2], p + prizel[n1]);
			prizel[n2] = max(prizel[n2], prizew[n1]);
		}
		
		else
		{
			if(x>0)
			{
				x = -x + 1;	
				prizew[n2] = p + prizel[n1];
				prizel[n2] = prizew[n1];
			}
			else
			{
				x++;
				prizew[n2] = smin(prizew[n2], p + prizel[n1]);
				prizel[n2] = max(prizel[n2], prizew[n1]);
			}
		}
	}
	
	else if(dp[n1] == 1)
	{
		if(x == 1)
		{
			x = 0;
			q.push(n2);	
			prizew[n2] = smin(prizew[n2], p + prizel[n1]);
			prizel[n2] = max(prizel[n2], prizew[n1]);
		}	
		else if(x == -1)
		{
			x = 1;
			q.push(n2);
		}
		
		else
		{
			if(x>0)
			{
				x--;
				prizew[n2] = smin(prizew[n2], p + prizel[n1]);
				prizel[n2] = max(prizel[n2], prizew[n1]);	
			}
			else
				x++;
		}	
	}
}

void resplora()
{
	int n = q.front(); q.pop();
	
	for(pii pp: rG[n])
	{
		int n2 = pp.first;
		ll p = pp.second;
		gestisci_dp(dp[n2], n2, n, p);
	}
}

int main() {
	int n, m;
	//freopen("input3.txt", "r", stdin);
	cin >> n >> m;
	rG.resize(n);
	dp.resize(n);
	fg.resize(n, 1);
	prizew.resize(n, LLONG_MAX);
	prizel.resize(n);
	for(int i=0; i<m; i++)
	{
		ll a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		dp[a]++;
		rG[b].push_back({a, c});
		fg[a] = 0;
	}


    //dp[i] = 0  --> i è una foglia
    for(int i=0; i<n; i++)
		if(fg[i])
		{
			q.push(i);
			prizew[i] = 0;
		}	
	
	while(!q.empty())
	{
		//cout << q.front()+1;
		resplora();
		
//		cout << ":\n";
//		for(int i: dp) cout << i << " ";
//		cout << "\n";
//		for(int i: prizew) cout << i << " ";
//		cout << "\n";
//		for(int i: prizel) cout << i << " ";
//		cout << "\n";
	}
		


	if(dp[0])	 cout << "Alice\n" << prizew[0];
	else    	cout << "Bob\n" << prizel[0];

}

