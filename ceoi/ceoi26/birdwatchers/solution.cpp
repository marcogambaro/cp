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

struct node {
    int l = 0, r = 0;
    int x = 0, sx = 0;
    int d = 1e9, lazyd = 0, mind = 1e9;
    int p = 0;
    int s = 1;
    int prio = timmy_loves_gambling();
};
vec<node> t;
#define L(v) t[t[v].l]
#define R(v) t[t[v].r]
int SUMM = 0;

void push(int v) {
    if(t[v].l) {
        L(v).d += t[v].lazyd;
        L(v).lazyd += t[v].lazyd;
        L(v).mind += t[v].lazyd;
    }
    if(t[v].r) {
        R(v).d += t[v].lazyd;
        R(v).lazyd += t[v].lazyd;
        R(v).mind += t[v].lazyd;
    }
    t[v].lazyd = 0;
}
void pull(int v) {
    if(!v) return;
    t[v].sx = t[v].x + L(v).sx + R(v).sx;
    t[v].s = L(v).s + R(v).s + 1;
    t[v].mind = min({t[v].d, L(v).mind, R(v).mind});
    t[v].p = 0;
    L(v).p = v;
    R(v).p = v;
}

pii split(int v, int k) {
    if(!v) return {0, 0};
    push(v);
    if(L(v).s < k) {
        auto [l, r] = split(t[v].r, k-L(v).s-1);
        t[v].r = l;
        pull(v);
        pull(r);
        return {v, r};
    }
    else {
        auto [l, r] = split(t[v].l, k);
        t[v].l = r;
        pull(v);
        pull(l);
        return {l, v};
    }
}

int merge(int l, int r) {
    if(!l || !r) return l^r;
    if(t[l].prio > t[r].prio) {
        push(l);
        t[l].r = merge(t[l].r, r);
        pull(l);
        return l;
    }
    else {
        push(r);
        t[r].l = merge(l, t[r].l);
        pull(r);
        return r;
    }
}

int findpos(int v) {
    if(t[v].p == 0)
        return L(v).s;
    else if(t[t[v].p].l == v)
        return findpos(t[v].p) - R(v).s -1;
    else
        return findpos(t[v].p) + L(v).s +1;
}

int lowerd(int v, int q, int d) {
    if(!v) return 1e9;
    if(t[v].s <= q)   return 1e9;
    if(t[v].mind > d) return 1e9;
    push(v);
    int c = lowerd(t[v].l, q, d);
    if(c < 1e8) return c;
    if(L(v).s >= q && t[v].d <= d) return v;
    return lowerd(t[v].r, q-L(v).s-1, d);
}

void access(int v, int k) {
    if(!v) return;
    push(v);
    if(L(v).s > k)      access(t[v].l, k);
    else if(L(v).s < k) access(t[v].r, k-L(v).s-1);
}

void heapify(int v) {
    if(!v) return;
    if(L(v).prio > t[v].prio && L(v).prio >= R(v).prio) {
        swap(t[v].prio, L(v).prio);
        heapify(t[v].l);
    }
    else if(R(v).prio > t[v].prio) {
        swap(t[v].prio, R(v).prio);
        heapify(t[v].r);
    }
}

int build(int l, int r, vec<int> &V) {
    if(l == r) return 0;
    int m = (l+r)/2;
    t[V[m]].l = build(l, m, V);
    t[V[m]].r = build(m+1, r, V);
    heapify(V[m]);
    pull(V[m]);
    return V[m];
}

int sumsubx(int &v, int l, int r) {
    l = findpos(l), r = findpos(r);
    if(l > r) swap(l, r);
    auto [mmt, rt] = split(v, r);
    auto [lt, mt] = split(mmt, l);
    int rtn = t[mt].sx;
    v = merge(lt, merge(mt, rt));
    return rtn;
}

void cut_link(int &treap, int a, int b, int N) {
    auto [t1, t2] = split(treap, findpos(a+1+N)+1);
    auto [t3, t4] = split(t1, findpos(a+1));
    treap = merge(t3, t2);

    access(treap, findpos(b+1));
    access(t4, findpos(a+1));

    int dd = t[b+1].d+1 - t[a+1].d;
    t[t4].d += dd;
    t[t4].mind += dd;
    t[t4].lazyd += dd;

    auto [t5, t6] = split(treap, findpos(b+1+N));
    treap = merge(t5, merge(t4, t6));
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N, Q;
    cin >> N >> Q;
    t.resize(N*2+1);
    t[0].s = 0;

    int root;
    vec<vec<int>> G(N);
    vec<int> par(N);

    for(int i = 0; i < N; i++) {
        int s, m; cin >> s >> m;
        s--;
        if(s == -1) root = i;
        else {
            G[s].push_back(i);
            par[i] = s;
        }
        t[i+1].x = t[i+1].sx = m;
        SUMM += m;
    }

    pii ans = {2e9, 2e9};
    int treap = 0;
    vec<int> tour;
    tour.reserve(N*2);

    auto dfs = [&](int v, int d, auto &&dfs) -> int {
        t[v+1].d = t[v+1+N].d = d;
        t[v+1].mind = t[v+1+N].mind = d;
        int x = t[v+1].x;
        tour.push_back(v+1);
        for(int u: G[v])
            x += dfs(u, d+1, dfs);
        tour.push_back(v+1+N);
        if(x*2 >= SUMM) ans = min(ans, {x, v});
        return x;
    };
    dfs(root, 0, dfs);

    treap = build(0, tour.size(), tour);

    cout << ans.se+1 << lf;

    auto tri = [&](int n) {
        int q = findpos(n+N+1);
        int l = -1, r = N;
        int its = 0;

        while(its++ < 21) {
            int m = (l+r)/2;
            int c = lowerd(treap, q, m);
            assert(c < 1e8);
            c = (c-1)%N;
            int x = sumsubx(treap, c+1, c+1+N);
            infof("c = {}, x = {}", c, x);

            if(x*2 >= SUMM) {
                ans = min(ans, {x, c});
                l = m;
            } else {
                r = m;
            }
        }
    };

    while(Q--) {
        int a, b; cin >> a >> b;
        a = (ans.se+1 + a)%N;
        b = (ans.se+1 + b)%N;
        int c = par[a];
        int old_ans = ans.se;

        cut_link(treap, a, b, N);
        par[a] = b;

        ans.fi = 2e9;

        tri(a);
        infof("--");
        tri(c);
        infof("--");
        int x = sumsubx(treap, old_ans+1, old_ans+1+N);
        if(x*2 >= SUMM)
            ans = min(ans, {x, old_ans});

        cout << ans.se+1 << lf;
    }
}