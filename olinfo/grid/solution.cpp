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

void end()
{
	cout << "NO";
	exit(0);
}

bool cmp(pair<int, char> a, pair<int, char> b)
{
	return a.first > b.first;
}

int main() {
    // uncomment the two following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int N, M;
    cin >> N >> M;

    vector<pair<int, char>> v;
    for(int i=1; i<4; i++)
    {
		int x; cin >> x;
		char c;
		if(i==1) c = 'R';
		if(i==2) c = 'G';
		if(i==3) c = 'B';
		v.push_back({x, c});
	}

    sort(v.begin(), v.end(), cmp);

    if(v[0].first > (N*M + 1)/2 )
		end();	
	cout << "YES";
	
	//adesso v[2].first mi indicherà quanti v[0].second devo sostituire in v[2].second
	v[2].first = (N*M + 1)/2 - v[0].first;
	
	if(N>M)
	{	
	bool b = ((M%2)==0);
	for(int cas = 0; cas < N*M; cas++)
	{
		if(cas%M == 0) //si va a capo
		{
			cout << "\n";
			if(M%2 == 0) b ^= 1;
		}
		
		//stampa il risultato:
		if(b ^ ((cas%2)==0)) //stampa il valore maggiore
		{
			if(v[2].first) {
				cout <<	v[2].second;
				v[2].first--;
			}
			else
				cout << v[0].second;	
		}
		else //stampa il valore minore
		{
			if(v[1].first) {
				cout << v[1].second;
				v[1].first--;
			}
			else
				cout << v[2].second;
		}
	}
	return 0;
	}
	
	////////////////////////////////////////////////////////////////////////////// M>N
	
	swap(N, M);
	char mtx[N][M];
	
	bool b = ((M%2)==0);
		for(int cas = 0; cas < N*M; cas++)
		{
			if(cas%M == 0) //si va a capo
			{
				//cout << "\n";
				if(M%2 == 0) b ^= 1;
			}
			
			//stampa il risultato:
			if(b ^ ((cas%2)==0)) //stampa il valore maggiore
			{
				if(v[2].first) {
					mtx[cas/M][cas%M] =	v[2].second;
					v[2].first--;
				}
				else
					mtx[cas/M][cas%M] = v[0].second;	
			}
			else //stampa il valore minore
			{
				if(v[1].first) {
					mtx[cas/M][cas%M] = v[1].second;
					v[1].first--;
				}
				else
					mtx[cas/M][cas%M] = v[2].second;
			}
		}
		
	cout << "\n";
	for(int i = M-1; i>=0; i--)
	{
		for(int j=0; j<N; j++)
			cout << mtx[j][i];
		cout << "\n";
	}
}

