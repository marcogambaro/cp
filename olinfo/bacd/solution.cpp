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

int sum(int a, int b){
	return ((ll)a+b+mod)%mod;
}

int mul(int a, int b){
	return((ll)a*b)%mod;
}

int N;
vector<int> V;	
vector<int> C, mina;

struct node{
	node *L, *R;

	int val;
	int s1;
	int lazy;

	node() {
		L = nullptr;
		R = nullptr;
		val = 0;
		s1 = 0;
		lazy = 0;
	}

	void procreate() {
		L = new node;
		R = new node;
	}

	void propagate() {
		if(lazy == 0) return;
		L->val = sum(L->val, mul(L->s1, lazy));
		R->val = sum(R->val, mul(R->s1, lazy));
		L->lazy += lazy;
		R->lazy += lazy;
		lazy = 0;
	}

	void herit() {
		s1 = sum(L->s1, R->s1);
		val = sum(L->val, R->val);
	}

	void padd(int l, int r, int q) { //aumenta di C[i] tutto ciò oltre pos
		if(r <= q) return;
		if(l > q) {
			lazy++;
			val += s1;
			return;
		}

		propagate();
		int m = (l+r)/2;
		L->padd(l, m, q);
		R->padd(m+1, r, q);
		herit();
	}

	void nullify(int l, int r, int q) { //nullifica [q]
		if(l == r) {
			s1 = 0;
			val = 0;
			return;
		}

		propagate();
		int m = (l+r)/2;
		if(q <= m)
			L->nullify(l, m, q);
		else
			R->nullify(m+1, r, q);
		herit();
	}

	pair<int, int> sumc(int l, int r, int q) { //ritorna somma degli elementi oltre pos
		if(r <= q) 	return {0, 0};
		if(l > q) 	return {val, s1};

		propagate();
		int m = (l+r)/2;
		auto [a, b] = L->sumc(l, m, q);
		auto [c, d] = R->sumc(m+1, r, q);
		herit();

		return {sum(a, c), sum(b, d)};
	}

	void start(int l, int r) {
		if(l == r) {
			s1 = C[l];
			return;
		}

		procreate();
		int m = (l+r)/2;
		L->start(l, m);
		R->start(m+1, r);
		herit();
	}
};


void daje()
{
	vector<int> index(N);
	for(int i=0; i<N; i++) index[i] = i;
	sort(all(index), [&](int a, int b) -> bool	{return V[a]<V[b];});

	node *root = new node;
	int ans = 0;

	root->start(0, N-1);

	for(int a: index)
	{
		auto [c, s1] = root->sumc(0, N-1, a);
		ans = sum(ans, c);
		ans = sum(ans, -mul(mina[a], s1));

		root->padd(0, N-1, a);
		root->nullify(0, N-1, a);

		infon("element %d: ans <- %d", a, ans);
	}
	cout << ans << "\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

    cin >> N;
	V.resize(N);
	readv(V);

	C.resize(N);
	mina.resize(N);

	vector<int> fenwick(N+5);
	auto add = [&](int i) -> void
	{
		while(i<fenwick.size()) {
			fenwick[i]++;
			i += i&-i;
		}
	};
	auto calc = [&](int i) -> int
	{
		int res = 0;
		while(i > 0) {
			res += fenwick[i];
			i -= i&-i;
		}
		return res;
	};

	for(int i=N-1; i>-1; i--)
	{
		C[i] = calc(N-V[i]+1);
		add(N-V[i]+1);
	}

	infon("C:");
	if(dbg) for(int i=0; i<N; i++) cout << C[i] _""; cout.flush();
	infon("");

	fenwick = vector<int>(N+5);
	for(int i=0; i<N-1; i++)
	{
		mina[i] = calc(V[i]+1);
		add(V[i]+1);
	}

	infon("mina:");
	if(dbg) for(int i=0; i<N; i++) cout << mina[i] _""; cout.flush();
	infon("");

	daje();
}





