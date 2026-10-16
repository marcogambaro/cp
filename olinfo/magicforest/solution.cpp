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

constexpr int M = 1e9 + 7;

struct Sentiero
{
	int magic, a, b;
	bool operator< (Sentiero o) const
	{
		if(magic!=o.magic)
			return magic > o.magic;
		else if(a!=o.a)
			return a<o.a;
		return b<o.b;
	}	
};

int N, S;
priority_queue <Sentiero> q; 
int ris;

void get_G()
{
	while(S--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		q.push({c, a, b});
	}	
}

int calcola()
{
	unordered_map <int, int> mp1, mp2; //associa ad ogni nodo le sue possibilità
	int magic2 = -1;
	while(!q.empty())
	{
		Sentiero sentiero=q.top(); 	q.pop();
		int magic=sentiero.magic;
		int a = sentiero.a;
		int b = sentiero.b;
		
		//se devo, cambio l'attuale grado di magicità
		if(magic==magic2);
		else if(magic==magic2+1)
		{
			magic2 = magic;
			mp2.swap(mp1);
			unordered_map <int, int> w;
			mp2.swap(w);
		}
		else if(magic>magic2+1)
		{
			magic2 = magic;
			unordered_map <int, int> w1, w2;
			mp1.swap(w1);
			mp2.swap(w2);
		}
		else cout << "ERROR";
		
		int pos = 1;
		//analizzo a->b
		int old_a = mp1[a];
		pos += old_a;
		mp2[b] = (mp2[b]+old_a+1)%M;
		//analizzo b->a
		int old_b = mp1[b];
		pos += old_b;
		mp2[a] = (mp2[a]+old_b+1)%M;
		
		//aggiorno ris
		pos %=M;
		ris = (ris+pos)%M;
	}
	
	return ris;
}

int main()
{
	cin >> N >> S;
	
	//gestisco S sentieri
	get_G();
	
	cout << calcola();
}

