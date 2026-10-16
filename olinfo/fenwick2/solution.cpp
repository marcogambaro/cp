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

constexpr int M = 1000000007;
//FENWICK TREE

vector <int> t(100005);
int N;

int sum(int k)	//somma [1, k) dove k è la posizione originale dell'elemento analizzato
{
	int ris = 0;
	while(k)
	{
		ris += t[k];
		ris %= M;
		k -= k&-k;
	}

	return ris;
}

void add(int k, int x)	//aggiunge x all'elemento k
{
	while(k<=N)
	{
		t[k]+=x;
		t[k]%=M;
		k += k&-k;
	}
}

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");

	cin >> N;

	vector <pair<int, int>> v(N);
	for(int i=0; i<N; i++)
	{
		int x;
		cin >> x;
		v[i] = {x, i+1};
	}

	sort(v.begin(), v.end()); //gli elementi sono ordinati in ordine crescente

	int ris = 0;
	int pv_x = v[0].first^1;
	int ssx; 	//somma delle s ottenute con x uguali
	for(pair<int, int> pp: v)
	{
		int x = pp.first;
		int i = pp.second;

		if(x==pv_x);
		else	ssx = 0;


		int s = sum(i)+1-ssx;
		ris += s;	ris %=M;
		ssx += s;	ssx %=M;
		add(i, s);

		swap(pv_x, x);
	}

	cout << ris;
}

