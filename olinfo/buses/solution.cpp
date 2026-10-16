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

constexpr ll mod = 1e9 + 7;

ll add(ll a, ll b) {
    return (a+b+mod)%mod;
}
ll mul(ll a, ll b) {
    return a*b%mod;
}
ll fe(ll b, ll e) {
    ll ans = 1;
    while(e) {
        if(e&1) ans = mul(ans, b);
        b = mul(b, b);
        e >>= 1;
    }
    return ans;
}

vec<ll> t0, t1, lz0, lz1, tp;

void swoop() {
    t0.swap(t1);
    lz0.swap(lz1);
}

void pull(int v) {
    t0[v] = add(t0[v*2], t0[v*2+1]);
    t1[v] = add(t1[v*2], t1[v*2+1]);
    tp[v] = add(tp[v*2], tp[v*2+1]);
}

void push(int v, int l, int m, int r) {
    for(int h=0; h<2; h++, swoop()) {
        if(lz0[v] != 0) {
            int x = lz0[v];

            t0[v*2] = add(t0[v*2], mul(m-l, x));
            lz0[v*2] = add(lz0[v*2], x);
            tp[v*2] = add(tp[v*2], mul(x, t1[v*2]));

            t0[v*2+1] = add(t0[v*2+1], mul(r-m, x));
            lz0[v*2+1] = add(lz0[v*2+1], x);
            tp[v*2+1] = add(tp[v*2+1], mul(x, t1[v*2+1]));
        }
        lz0[v] = 0;
    }
}

void build(int v, int l, int r, vec<int> &A) {
    if(r-l == 1) {
        t0[v] = A[l];
        tp[v] = mul(t0[v], t1[v]);
        return;
    }
    int m = (l+r)/2;
    build(v*2, l, m, A);
    build(v*2+1, m, r, A);
    pull(v);
}

void upd(int v, int l, int r, int ql, int qr, int x) {
    if(qr <= l || r <= ql) return;
    if(ql <= l && r <= qr) {
        lz0[v] = add(lz0[v], x);
        t0[v] = add(t0[v], mul(r-l, x));
        tp[v] = add(tp[v], mul(x, t1[v]));
        return;
    }

    int m = (l+r)/2;
    push(v, l, m, r);
    upd(v*2, l, m, ql, qr, x);
    upd(v*2+1, m, r, ql, qr, x);
    pull(v);
}

ll sum(int v, int l, int r, int ql, int qr) {
    if(qr <= l || r <= ql) return 0;
    if(ql <= l && r <= qr) return t0[v];

    int m = (l+r)/2;
    push(v, l, m, r);
    return add(sum(v*2, l, m, ql, qr), sum(v*2+1, m, r, ql, qr));
}

ll sump(int v, int l, int r, int ql, int qr) {
    if(qr <= l || r <= ql) return 0;
    if(ql <= l && r <= qr) return tp[v];

    int m = (l+r)/2;
    return add(sump(v*2, l, m, ql, qr), sump(v*2+1, m, r, ql, qr));
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    vec<int> A(N), B(N);
    for(auto &i: A) cin >> i;
    for(auto &i: B) cin >> i;

    t0 = t1 = lz0 = lz1 = tp = vector<ll>(N*4);

    build(1, 0, N, A);
    swoop();
    build(1, 0, N, B);
    swoop();

    int Q; cin >> Q;
    while(Q--) {
        int t, l, r, k; cin >> t >> l >> r >> k;
        l--;

        if(t < 3) {
            if(t == 2) swoop();
            upd(1, 0, N, l, r, k);
            if(t == 2) swoop();
        }
        else {
            ll a = sum(1, 0, N, l, r);
            swoop();
            ll b = sum(1, 0, N, l, r);
            swoop();
            ll c = sump(1, 0, N, l, r);

            infof("a = {}, b = {}, c = {}", a, b, c);
            cout << mul(mul(a, b), fe(c, k-1)) << lf;
        }
    }
}

