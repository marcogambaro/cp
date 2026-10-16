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

array<int, 3> ans = {0, 0, 0};
vector<pair<ll, ll>> V;
ll N, S, F;

struct node{
    int L = 0, R = 0;
    int x = 0;
    int lazy = 0;
};
vector<node> t(4e6);
int ttt;
int make() {
    t[++ttt] = node();
    return ttt;
}
void push(int v) {
    if(t[v].L == 0) {
        t[v].L = make();
        t[v].R = make();
    }
    if(t[v].lazy == 0) return;
    int k = t[v].lazy;
    t[t[v].L].x += k;
    t[t[v].R].x += k;
    t[t[v].L].lazy += k;
    t[t[v].R].lazy += k;
    t[v].lazy = 0;
}
void pull(int v) {
    t[v].x = max(t[t[v].L].x, t[t[v].R].x);
}
void add(int v, int l, int r, int ql, int qr, int w) {
    if(r <= ql || qr <= l) return;
    if(ql <= l && r <= qr) {
        t[v].x += w;
        t[v].lazy += w;
        return;
    }
    int m = (l+r)/2;
    push(v);
    add(t[v].L, l, m, ql, qr, w);
    add(t[v].R, m, r, ql, qr, w);
    pull(v);
}
int find(int v, int l, int r, ll k) {
    if(t[v].x < k) return -1;
    if(r-l == 1) return l;
    int m = (r+l)/2;
    push(v);
    int c = find(t[v].L, l, m, k);
    if(c != -1) return c;
    return find(t[v].R, m, r, k);
}

bool check(ll m) {
    int p = 0, pp = 0;
    int ly = 0, ry = 0;
    int acty = -1;

    ttt = 1;
    t[1] = node();

    while(1) {
        int nxty = max(0LL, min(V[ry].fi - m, V[pp].fi));
        if(nxty >= S) return 0;

        while(V[p].fi == acty) {
            add(1, 0, S, V[p].se-m, V[p].se, -1);
            add(1, 0, S, V[p].se+1, V[p].se+m+1, -1);
            p++;
        }

        while(V[pp].fi == nxty) {
            add(1, 0, S, V[pp].se-m, V[pp].se, 1);
            add(1, 0, S, V[pp].se+1, V[pp].se+m+1, 1);
            pp++;
        }

        while(V[ry].fi <= nxty+m) {
            add(1, 0, S, V[ry].se, V[ry].se+1, 1);
            ry++;
        }

        while(V[ly].fi < nxty-m) {
            add(1, 0, S, V[ly].se, V[ly].se+1, -1);
            ly++;
        }

        acty = nxty;

        int k = find(1, 0, S, m*4 + 1 - F);
        if(k != -1) {
            ans = {(int)m, nxty, k};
            return 1;
        }
    }
}


array<int, 3> find_plus(int N, int S, int F, vector<int> y, vector<int> x) {
	::N = N;
	::S = S;
	::F = F;
    ans = {(F-1)/4, 0, 0};

    for(int i=0; i<N; i++) {
        V.push_back({y[i], x[i]});
    }
    sort(all(V));
    V.push_back({2e9, 2e9});

    ll l = (F-1)/4 + 1, r = 5e8;
    while(r-l > 1) {
        ll m = (l+r)/2;

        if(check(m)) l = m;
        else         r = m;
    }
    if(l != (F-1)/4) check(l);
    return ans;
}

#ifndef EVAL
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, S, F;
    assert(cin >> N >> S >> F);
    vector<int> y(N), x(N);
    for (int i = 0; i < N; i++) {
        assert(cin >> y[i] >> x[i]);
    }
    array<int, 3> ans = find_plus(N, S, F, move(y), move(x));
    cout << ans[0] << " " << ans[1] << " " << ans[2] << "\n";
}
#endif

