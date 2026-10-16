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

// input data
int N, M, V;
vector<int> H;

vector<int> t;

void build(int v, int tl, int tr, vector<int> & h)
{
	if(tl == tr)
	{
		t[v] = h[tl];
		return;
	}

	int mt = (tl+tr)/2;
	build(v*2, tl, mt, h);
	build(v*2+1, mt+1, tr, h);

	t[v] = max(t[v*2], t[v*2+1]);
}

int find(int v, int tl, int tr, int pos, int val) //trova il primo indice > pos il cui valore sia almeno val
{
	if(tr <= pos) return N;
	if(t[v] < val) return N;
	if(tl == tr)
	{
		return tr;
	}

	int mt = (tl+tr)/2;
	int lchild = find(v*2, tl, mt, pos, val);
	if(lchild != N) return lchild;

	int rchild = find(v*2+1, mt+1, tr, pos, val);
	return rchild;
}

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    cin >> N >> M >> V;
    H.resize(N);
    for (int i=0; i<N; i++)
        cin >> H[i];

    // insert your code here
    int maxdelta = V*V/20;
    t.resize(N*4 + 5);
    build(1, 0, N-1, H);

    int limit = maxdelta+1;

    for(int i=0; i<N; i++)
    	cout << min(find(1, 0, N-1, i, H[i]+limit)-1, N-1) << " ";

}

