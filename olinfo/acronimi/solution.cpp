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

string S, A;
vector <vector <int>> posc; //assegna a ciascun carattere le posizioni che occupa in A
vector <int> nc; 	    	//indica gli acronimi lunghi i presenti nella stringa

void get_posc()
{
	posc.resize(26);
	for(int i=0; i<A.size(); i++)
	{
		int c = A[i]-97;
		posc[c].push_back(i+1);
	}
}

void get_nc()
{
	nc.resize(A.size()+1,0);
	nc[0] = 1;
}

unsigned long long calcola()
{
	int maxnc = 1; //indica il massimo indice di nc che mi interessa analizzare
	for(char item: S)
	{
		int c = item-97;
		
		bool increase_maxnc = false;
		vector <int> nc2 = nc;
		for(int i=0; i<posc[c].size(); i++)
		{
			int posizione = posc[c][i];
			if(posizione>maxnc)  break;
			if(posizione==maxnc) increase_maxnc=true;
			
			nc2[posizione] += nc[posizione-1];
			nc2[posizione] %=M;
		}
		
		nc.swap(nc2);
		if(increase_maxnc)	maxnc++;
	}
	
	return nc[A.size()];
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
	cin >> A >> S;
	
	get_posc();
	get_nc();
	
	cout << calcola();
}

