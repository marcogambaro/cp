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

void solve()
{
	string S;	cin >> S;
	string T;
	
	map <char, int> mp;
	
	int p=0;
	char c;
	char lenght = 0;
	
	while(p<S.size())
	{
		if(lenght==0)
		{
			c = S[p];
			p++;
			lenght++;
		}
		else if(S[p]==c)
		{
			lenght++;
			p++;
		}
		else
		{
			if(mp[c]==lenght) //già presente
			{
				cout << -1 << "\n";
				return;
			}
			mp[c]+=lenght;
			for(int i=0; i<lenght; i++)
			{
				if(i==2)	T+=" ";
				T.push_back(c);
			}
			T += " ";
			lenght=0;
			if(mp[c]>3)
			{
				cout << -1 << "\n";
				return;
			}
		}
	}
	
	if(mp[c]==lenght) //già presente
				{
					cout << -1 << "\n";
					return;
				}
				mp[c]+=lenght;
				for(int i=0; i<lenght; i++)
				{
					if(i==2)	T+=" ";
					T.push_back(c);
				}
				T += " ";
				lenght=0;
				if(mp[c]>3)
				{
					cout << -1 << "\n";
					return;
				}
				
	cout << T << "\n";
}

int main()
{
	int t;
	cin >> t;
	while(t--)
		solve();
}

