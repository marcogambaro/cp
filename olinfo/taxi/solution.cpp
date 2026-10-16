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

struct Taxi {
    int t0, x0, y0, x1, y1;
    Taxi() {}
};

struct SplayTree {
    struct node {
        int ch[2]; // children
        int p = 0;  // parent
    };
    vec<node> t;

    SplayTree(int N) {
        t.resize(N+1);
    }

    int par(int v) {
        if(v == 0)  return 0;
        return t[v].p;
    }
    int dir(int v) {
        int p = t[v].p;
        if(p == 0) return -1;

        for(int i=0; i<2; i++)
            if(t[p].ch[i] == v) return i;
        return -1;
    }

    void zig(int v) {
        int p = par(v);
        int g = par(p);

        bool b = t[p].ch[1] == v;
        int u = t[v].ch[!b];

        t[v].p = g;
        for(int i=0; i<2; i++)
            if(t[g].ch[i] == p) t[g].ch[i] = v;

        t[v].ch[!b] = p;
        t[p].p = v;

        t[p].ch[b] = u;
        t[u].p = p;
    }

    void splay(int v) {
        while(dir(v) != -1) {
            if(dir(v) == dir(par(v))) {
                zig(par(v));
                zig(v);
            }
            else if(dir(par(v)) != -1) {
                zig(v);
                zig(v);
            }
            else zig(v);
        }
    }
};

struct LinkCutTree : SplayTree {
    LinkCutTree(int N) : SplayTree(N) {}

    void detach(int v) {
        splay(v);
        t[v].ch[1] = 0;
    }

    void access(int v) {
        detach(v);

        while(par(v) != 0) {
            int u = par(v);
            detach(u);
            t[u].ch[1] = v;
            t[v].p = u;
            splay(v);
        }
    }

    void link(int v, int u) {
        access(v);
        access(u);
        t[u].ch[1] = v;
        t[v].p = u;
    }

    void cut(int v) {
        access(v);
        t[t[v].ch[0]].p = 0;
        t[v].ch[0] = 0;
    }

    int query(int v, vec<Taxi> &V, int x) {
        int u = 0;
        int pv = -1;

        while(v != 0) {
            access(v);
            if(V[v-1].x0 <= x) {
                u = v;
                v = t[v].ch[0];
            } else {
                v = t[v].ch[1];
            }
            pv = v;
        }

        return u;
    }
};


vector<int> incrocia(int N, int M, vector<Taxi> V, vector<Taxi> H) {
    const int T = N*7;
    vec<vec<int>> Y0(N), Y1(N), YQ(N);
    vec<vec<int>> vm(T); // [diag] = { taxi, ... }
    vec<int> pos(M);

    auto getd = [&](int i, bool o) -> int {
        if(!o) // horizontal
            return H[i].x0 + H[i].y0 - H[i].t0 + 2*N;
        else
            return V[i].x0 + V[i].y0 - V[i].t0 + 2*N;
    };

    LinkCutTree BOSS(M);

    for(int i=0; i<M; i++) {
        Y0[V[i].y0].push_back(i);
        Y1[V[i].y1].push_back(i);
        int d = getd(i, 1);
        vm[d].emplace_back(i);
    }

    for(int i=0; i<T; i++) {
        sort(all(vm[i]), [&](int &i, int &j){
            return V[i].x0 < V[j].x0;
        });

        for(int j=1; j<vm[i].size(); j++) {
            BOSS.link(vm[i][j-1] + 1, vm[i][j] + 1);
        }
        for(int j=0; j<vm[i].size(); j++)
            pos[vm[i][j]] = j;
    }

    for(int i=0; i<M; i++) {
        YQ[H[i].y0].push_back(i);
    }

    /////////////////////////////////////////////////////////////

    vec<int> ans(M);

    for(int y=0; y<N; y++) {
        // solve queries
        for(int q: YQ[y]) {
            int d = getd(q, 0);

            int l = -1, r = vm[d].size();
            while(r-l > 1) {
                int m = (l+r)/2;
                if(V[vm[d][m]].x0 <= H[q].x0) l = m;
                else r = m;
            }
            int i = r;

            if(i == vm[d].size()) {
                ans[q] = H[q].x1 - H[q].x0;
            }
            else {
                int u = BOSS.query(vm[d][i] + 1, V, H[q].x1) -1;
                int du = getd(u, 1);

                if(u < 0) ans[q] = H[q].x1 - H[q].x0;
                else ans[q] = H[q].x1 - H[q].x0 + d - du +
                        (int)(V[u].y0 < y && y <= V[u].y1);
            }

            infof("ans[{}] = {}", q, ans[q]);
        }

        // add new taxis
        for(int q: Y0[y]) {
            BOSS.cut(q+1);

            int d = getd(q, 1);

            int l = -1, r = vm[d-1].size();
            while(r-l > 1) {
                int m = (l+r)/2;
                if(V[vm[d-1][m]].x0 <= V[q].x0) l = m;
                else r = m;
            }
            int i = r;

            if(i == vm[d-1].size()) continue;

            BOSS.link(q+1, vm[d-1][i] + 1);
        }

        // kill old taxis
        for(int q: Y1[y]) {
            BOSS.cut(q+1);

            int d = getd(q, 1);
            int i = pos[q]+1;

            if(i == vm[d].size()) continue;

            BOSS.link(q+1, vm[d][i] +1);
        }
    }

    return ans;
}

#ifndef EVAL

int main() {
    int N;
    int M;
    cin >> N;
    cin >> M;

    std::vector<Taxi> V(M), H(M);

    for (Taxi &taxi: V) {
        cin >> taxi.t0;
        cin >> taxi.x0;
        cin >> taxi.y0;
        cin >> taxi.x1;
        cin >> taxi.y1;
    }

    for (Taxi &taxi: H) {
        cin >> taxi.t0;
        cin >> taxi.x0;
        cin >> taxi.y0;
        cin >> taxi.x1;
        cin >> taxi.y1;
    }

    vector<int> ans = incrocia(N, M, V, H);

    for (int x: ans) {
        cout << x << '\n';
    }
}
#endif
