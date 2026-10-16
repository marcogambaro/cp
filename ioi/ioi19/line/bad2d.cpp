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

struct seg {
    vec<int> tmin, tmax, tx;

    seg() {}

    seg(int N) {
        tmin.resize(N*4, 2e9);
        tmax.resize(N*4, -2e9);
        tx.resize(N*4);
    }

    void pull(int v) {
        tmin[v] = min(tmin[v*2], tmin[v*2+1]);
        tmax[v] = max(tmax[v*2], tmax[v*2+1]);
        tx[v] = tx[v*2] + tx[v*2+1];
    }

    void add(int v, int l, int r, int q, int k) {
        if(r-l == 1) {
            tmin[v] = tmax[v] = k;
            tx[v]++;
            return;
        }
        int m = (l+r)/2;
        if(q < m) add(v*2, l, m, q, k);
        else      add(v*2+1, m, r, q, k);
        pull(v);
    }

    void rem(int v, int l, int r, int q) {

        if(r-l == 1) {
            tmin[v] = 2e9;
            tmax[v] = -2e9;
            tx[v] = 0;
            return;
        }
        int m = (l+r)/2;
        if(q < m) rem(v*2, l, m, q);
        else      rem(v*2+1, m, r, q);
        pull(v);
    }

    pii before(int v, int l, int r, int q, int kl, int kr) {
        if(tmin[v] > kr || tmax[v] < kl) return {-1, -1};
        if(q <= l) return {-1, -1};
        if(r-l == 1) return {l, tmin[v]};
        int m = (l+r)/2;
        pii c = before(v*2+1, m, r, q, kl, kr);
        if(c.fi != -1) return c;
        return before(v*2, l, m, q, kl, kr);
    }

    pii after(int v, int l, int r, int q, int kl, int kr) {
        if(tmin[v] > kr || tmax[v] < kl) return {-1, -1};
        if(r <= q) return {-1, -1};
        if(r-l == 1) return {l, tmin[v]};
        int m = (l+r)/2;
        pii c = after(v*2, l, m, q, kl, kr);
        if(c.fi != -1) return c;
        return after(v*2+1, m, r, q, kl, kr);
    }
};

struct seg2d {
    struct node {
        int l=0, r=0;
        int yl=0, yr=0;
        int x=0;
    };
    vec<node> t;
    int W;

    seg2d() {}

    seg2d(int N){
        t.resize(2);
        W = N;
    }

    int make() {
        t.emplace_back();
        return t.size()-1;
    }
    void pull(int v) {
	    t[v].x = t[t[v].l].x + t[t[v].r].x;
    }

    int updx(int v, int l, int r, int qx, int k) {
	    if(!v) v = make();
        if(r-l == 1) {
            t[v].x += k;
            return v;
        }
        int m = (l+r)/2;
        if(qx < m) t[v].l = updx(t[v].l, l, m, qx, k);
        else       t[v].r = updx(t[v].r, m, r, qx, k);
        pull(v);
        return v;
    }
    int updy(int v, int l, int r, int qx, int qy, int k) {
        if(!v) v = make();

        updx(v, 0, W, qx, k);
        if(r-l == 1) return v;

        int m = (l+r)/2;
        if(qy < m) t[v].yl = updy(t[v].yl, l, m, qx, qy, k);
        else       t[v].yr = updy(t[v].yr, m, r, qx, qy, k);
        return v;
    }
    void upd(int x, int y, int k) {
        updy(1, 0, W, x, y, k);
    }

    int cntx(int v, int l, int r, int ql, int qr) {
        if(qr <= l || r <= ql) return 0;
        if(ql <= l && r <= qr) return t[v].x;
        int m = (l+r)/2;
        return cntx(t[v].l, l, m, ql, qr) + cntx(t[v].r, m, r, ql, qr);
    }
    int cnty(int v, int l, int r, int qly, int qry, int qlx, int qrx) {
        if(qry <= l || r <= qly) return 0;
        if(qly <= l && r <= qry) return cntx(v, 0, W, qlx, qrx);
        int m = (l+r)/2;
        return cnty(t[v].yl, l, m, qly, qry, qlx, qrx) +
            cnty(t[v].yr, m, r, qly, qry, qlx, qrx);
    }
    int cnt(int xl, int xr, int yl, int yr) {
        return cnty(1, 0, W, yl, yr, xl, xr);
    }
};

struct Dt {
    seg sx, sy;
    seg2d cn;
    int n;

    Dt(int N) {
        sx = seg(N);
        sy = seg(N);
        cn = seg2d(N);
        n = N;
    }

    void add(int x, int y) {
        sx.add(1, 0, n, x, y);
        sy.add(1, 0, n, y, x);
        cn.upd(x, y, 1);
    }
    void rem(int x, int y) {
        sx.rem(1, 0, n, x);
        sy.rem(1, 0, n, y);
        cn.upd(x, y, -1);
    }

    pii beforex(int x, int kl, int kr) {
        return sx.before(1, 0, n, x, kl, kr);
    }

    pii afterx(int x, int kl, int kr) {
        return sx.after(1, 0, n, x, kl, kr);
    }

    pii beforey(int y, int kl, int kr) {
        auto [a, b] = sy.before(1, 0, n, y, kl, kr);
        return {b, a};
    }

    pii aftery(int y, int kl, int kr) {
        auto [a, b] = sy.after(1, 0, n, y, kl, kr);
        return {b, a};
    }

    int count(int xl, int xr, int yl, int yr) {
        return cn.cnt(xl, xr, yl, yr);
    }
};

///////////////////////////////////////////////////////////////////

void solve(ifstream &cin, ofstream &cout) {
    int N; cin >> N;
    Dt dt(N+3);

    vec<int> cx = {0}, cy = {0};
    vec<pii> P;
    set<pii> st;

    for(int i=0; i<N; i++) {
        int x, y; cin >> x >> y;
        P.emplace_back(x, y);
        cx.push_back(x);
        cy.push_back(y);
    }

    sort(all(cx));
    sort(all(cy));

    for(auto &[x, y]: P) {
        x = lower_bound(all(cx), x)-cx.begin();
        y = lower_bound(all(cy), y)-cy.begin();
        st.emplace(x, y);
        dt.add(x, y);
    }

    vec<pii> v = {{0, 0}, {1, 0}};

    auto move = [&](int x, int y) -> void {
        if(v.back().fi == v[v.size()-2].fi) {
            if(v.back().fi != x)
                v.emplace_back(v.back().fi, y);
            v.emplace_back(x, y);
        }
        else {
            if(v.back().se != y)
                v.emplace_back(x, v.back().se);
            v.emplace_back(x, y);
        }
    };
    auto calc = [&]() -> vec<pii> {
        vec<pii> ans;
        ans.push_back(v[0]);
        ans.push_back(v[1]);

        for(int i=2; i<v.size(); i++) {
            if(ans.back() == v[i]) continue;

            if(ans.back().fi == ans[ans.size()-2].fi && v[i].fi == ans.back().fi) {
                if( (ans[ans.size()-2].se < ans.back().se) == (ans.back().se < v[i].se))
                    ans.pop_back();
            }

            else if(ans.back().se == ans[ans.size()-2].se && v[i].se == ans.back().se) {
                if( (ans[ans.size()-2].fi < ans.back().fi) == (ans.back().fi < v[i].fi))
                    ans.pop_back();
            }

            ans.push_back(v[i]);
        }

        return ans;
    };

    while(st.size() > 6) {
        int x = v.back().fi, y = v.back().se;
        pii nw;
        int a, b;

        if(v.back().fi == v[v.size()-2].fi) {
            if(v.back().se > v[v.size()-2].se) {
                // up
                a = dt.count(x, 1e9, y, 1e9);
                b = dt.count(-1, x, y, 1e9);
                if(a > b)
                    nw = dt.afterx(x, y, 1e9);
                else
                    nw = dt.beforex(x, y, 1e9);
            }
            else {
                // down
                a = dt.count(x, 1e9, -1, y);
                b = dt.count(-1, x, -1, y);
                if(a > b)
                    nw = dt.afterx(x, -1, y);
                else
                    nw = dt.beforex(x, -1, y);
            }
        }
        else {
            if(v.back().fi > v[v.size()-2].fi) {
                // right
                a = dt.count(x, 1e9, y, 1e9);
                b = dt.count(x, 1e9, -1, y);
                if(a > b)
                    nw = dt.aftery(y, x, 1e9);
                else
                    nw = dt.beforey(y, x, 1e9);
            }
            else {
                // left
                a = dt.count(-1, x, y, 1e9);
                b = dt.count(-1, x, -1, y);
                if(a > b)
                    nw = dt.aftery(y, -1, x);
                else
                    nw = dt.beforey(y, -1, x);
            }
        }

        //cerr << nw.fi << " " << nw.se << " " << a << " " << b << endl;
        if(nw.se == -1) {
            cerr << "exit early! st.size() = " << st.size() << endl;
            break;
        }
        move(nw.fi, nw.se);
        st.erase(nw);
        dt.rem(nw.fi, nw.se);
    }

    P.clear();
    for(auto [x, y]: st) P.emplace_back(x, y);
    vec<pii> ans;

    if(st.size() <= 10)
    do {
        int st = v.size();
        for(auto [x, y]: P) {
            move(x, y);
        }

        ans = calc();
        if(ans.size() <= N+4) break;
        while(v.size() > st) v.pop_back();
    } while(next_permutation(all(P)));

    ans = calc();

    cout << ans.size() -1 << lf;
    bool first = 1;

    for(auto [x, y]: ans) {
        if(first) {
            first = 0;
            continue;
        }
        cout << cx[x] << " " << cy[y] << lf;
    }
    cerr << "solved with an extra equal to: " << ans.size()-N-1 << lf;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for(int i=1; i<=10; i++) {
        string file = (i != 10 ? (string)"0" : (string)"")+to_string(i);
        string sorg = "";

        ifstream cin(sorg + "tests/" + file + ".in");
        ofstream cout(sorg + "out/"+ file + ".out.txt");

        if (!cin.is_open()) {
            cerr << "File does not exist (or could not be opened):" << lf;
            return -1;
        }

	    cerr << "----------------"+file+":" << endl;
        solve(cin, cout);
    }
}
