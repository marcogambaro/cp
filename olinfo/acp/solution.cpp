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
constexpr int INV_MOD_2 = 500000004;
int N, Q;
vector<int> t, tl, tr, tlr, tmol, lazy;

int mul(int a, int b) {
	if(a < 0 || b < 0) while(1); //non il prob.
	return (ll)a*b % M;
}

int sum(int a, int b) {
	int res = ((ll)a+b+M)%M;
	if(res < 0) res += M;
	return res;
}

int sommatoria(ll a, ll b) {
	if(a > b) swap(a, b);
	int res = mul( sum(a, b), sum(b, -a+1));
	res = mul(res, INV_MOD_2);
	return res;
}

int pow(int b, int e) {
	int ans = 1;

	while(e > 0) {
		if(e & 1) ans = mul(ans, b);

		e >>= 1;
		b = mul(b, b);
	}
	return ans;
}

struct Calc{
	vector<int> pfx;

	Calc() { }

	Calc(bool b) {
		pfx.resize(N);

		pfx[0] = N;
		for(int i=1; i<N; i++)
			pfx[i] = sum(pfx[i-1], mul(i+1, N-i));
	}

	int operator() (int l, int r) {
		int res = pfx[r];
		if(l != 0) res = sum(res, -pfx[l-1]);
		return res;
	}

}; Calc calc;

void herit(int v) {
	t[v] = sum(t[v*2], t[v*2+1]);
	tl[v] = sum(tl[v*2], tl[v*2+1]);
	tr[v] = sum(tr[v*2], tr[v*2+1]);
	tlr[v] = sum(tlr[v*2], tlr[v*2+1]);
	tmol[v] = mul(tmol[v*2], tmol[v*2+1]);
}

void push(int vv, int l0, int r0) {
	int val = lazy[vv];
	if(val == -1) return;

	int m = (l0+r0)/2;
	int v = vv*2, l = l0, r = m;
	int x = mul(val, r - l + 1);
	t[v] = x;
	tl[v] =  mul(val, sommatoria(l+1, r+1));
	tr[v] = mul(val, sommatoria(N-r, N-l));
	tlr[v] = mul(val, calc(l,r) );
	tmol[v] = pow(val+1, r - l + 1);
	lazy[v] = val;

	v++, l = m+1, r = r0;
	x = mul(val, r - l + 1);
	t[v] = x;
	tl[v] =  mul(val, sommatoria(l+1, r+1));
	tr[v] = mul(val, sommatoria(N-r, N-l));
	tlr[v] = mul(val, calc(l,r) );
	tmol[v] = pow(val+1, r - l + 1);
	lazy[v] = val;

	lazy[vv] = -1;
}

void build(int v, int l, int r, vector<int> &V) {
	if(l == r) {
		t[v] = V[l];
		tl[v] = mul(V[l], l+1);
		tr[v] = mul(V[r], N-r);
		tlr[v] = mul(V[r], mul((l+1), (N-r)));
		tmol[v] = V[l] + 1;
	}
	else
	{
		int m = (l+r)/2;

		build(v*2, l, m, V);
		build(v*2+1, m+1, r, V);
		herit(v);
	}
}

int sumquery(int v, int l, int r, int ql, int qr, vector<int> &T) {
	if(ql > qr) return 0;
	if(ql == l && qr == r)	return T[v];

	int m = (l+r)/2;
	push(v, l, r);
	return sum( sumquery(v*2, l, m, ql, min(qr, m), T), sumquery(v*2+1, m+1, r, max(m+1, ql), qr, T) );
}

int molquery(int v, int l, int r, int ql, int qr) { //sempre su tmol
	if(ql > qr) return 1;
	if(ql == l && qr == r)	return tmol[v];

	int m = (l+r)/2;
	push(v, l, r);
	return mul( molquery(v*2, l, m, ql, min(qr, m)), molquery(v*2+1, m+1, r, max(m+1, ql), qr) );
}

void update(int v, int l, int r, int ql, int qr, int val) {
	if(ql > qr) return;
	if(l == ql && r == qr) {
		lazy[v] = val;

		int x = mul(val, qr - ql +1);
		t[v] = x;
		tl[v] =  mul(val, sommatoria(ql+1, qr+1));
		tr[v] = mul(val, sommatoria(N-qr, N-ql));
		tlr[v] = mul(val, calc(l,r));
		tmol[v] = pow(val+1, qr - ql + 1);
		return;
	}

	int m = (l+r)/2;
	push(v, l, r);

	update(v*2, l, m, ql, min(qr, m), val);
	update(v*2+1, m+1, r, max(ql, m+1), qr, val);
	herit(v);
}

int find(int v, int l, int r, int pos, vector<int> &T) {
	if(l == r) {
		return T[v];
	}

	push(v, l, r);
	int m = (l+r)/2;
	if(pos <= m)
		return find(v*2, l, m, pos, T);
	else
		return find(v*2+1, m+1, r, pos, T);
}

int find(int pos, vector<int> &T) {
	return find(1, 0, N-1, pos, T);
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> Q;
	vector<int> V(N);
	readv(V);

	calc = Calc(1);
	t.resize(N*4+5);
	tl.resize(N*4+5);
	tr.resize(N*4+5);
	tlr.resize(N*4+5);
	tmol.resize(N*4+5);
	lazy.resize(N*4+5, -1);

	build(1, 0, N-1, V);

	while(Q--) {
		int x, l, r; cin >> x >> l >> r;

		if(Q==0)
			infon("LAST QUERY!");

		if(x == 1) //update
		{
			int val; cin >> val;
			update(1, 0, N-1, l, r, val);
		}
		else //query
		{
			ll mq = molquery(1, 0, N-1, l, r);
			ll tq = sumquery(1, 0, N-1, l, r, t);
			ll tlq = sumquery(1, 0, N-1, l, r, tl);
			ll trq = sumquery(1, 0, N-1, l, r, tr);
			ll tlrq = sumquery(1, 0, N-1, l, r, tlr);

			tq = mul(tq, mul(l, N-r-1));
			tlq = mul(tlq, N-r-1);
			trq = mul(trq, l);
			tlrq;

			ll ans = sum( sum(-tlq, tq), sum(-trq, tlrq));
			ans = mul(ans, mq);
			ans = mul(ans, INV_MOD_2);
			cout << ans << "\n";

		}
	}
}

