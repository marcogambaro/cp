#include <algorithm>
#include <vector>
#include <cassert>
#include <array>
#include <iterator>

using namespace std;

#define forall(i, s, e) for(int i=(s); i<(e); i++)

#define ssize(x) (int)(x).size()

using vi = vector<int>;
using vb = vector<bool>;

void intrappola(int X);
bool ispeziona(vector<int> V);

int N;
vector<vi> G;
vi S(N); // size del subtree
vb C(N); // colore

void dfs(int v, int p, bool col) {
    S[v] = 1;
    C[v] = col;
    for(int c:G[v]) {
        if(c == p) continue;
        dfs(c, v, !col);
        S[v] += S[c];
    }
}

int _centroid(int v, int p) {
    for(int c:G[v]) {
        if(c == p) continue;
        if(S[c] > N/2)
            return _centroid(c, v);
    }
    return v;
}

int centroid(int v, bool col) { // preferisce il centroide del colore giusto
    int c0 = _centroid(v, -1);
    if(N%2 || C[c0]==col) return c0;

    for(int c:G[c0]) {
        if(S[c] == N/2)
            return c;
    }

    return c0;
}

void get_st(int v, int p, vi &qry) {
    qry.push_back(v);
    for(int c:G[v])
        if(c != p) get_st(c, v, qry);
}

int solve_start(int st, bool col) {
    sort(begin(G[st]), end(G[st]), [&](int a, int b){ return S[a]<S[b]; });

    vi qry;
    bool ret;

    int l = 0, r = ssize(G[st]);
    while(l<r && S[G[st][l]] == 1) l++;

    bool lf = (l > 0);

    if(C[st] == col)
        intrappola(st), lf = 0;

    forall(_, 0, 2) {
        if(r-l <= 1) break;
        
        get_st(G[st][r-1], st, qry);
        ret = ispeziona(qry);
        intrappola(st);
        lf = 0;

        if(ret) return G[st][r-1];
        
        r--;
    }

    while(r-l > 1) {
        int m = (l+r)/2;

        qry.clear();
        forall(i, l, m)
            get_st(G[st][i], st, qry);

        ret = ispeziona(qry);
        intrappola(st);
        lf = 0;

        if(ret) r = m;
        else l = m;
    }

    if(lf) {
        intrappola(st);
        intrappola(st); 
    }

    return l==r? -1 : G[st][l];
}

void solve(int v, int p) { // z è nel subtree di v e nel colore C[v]
    
    intrappola(v);

    vi nls;

    for(int c:G[v]) {
        if(c == p) continue;
        if(S[c] > 1) nls.push_back(c);
    }

    if(nls.empty()) return;

    vi qry;

    forall(i, 1, ssize(nls)) {
        qry.clear();
        get_st(nls[i], v, qry);

        bool ret = ispeziona(qry);
        intrappola(v);

        if(ret) {
            solve(nls[i], v);
            return;
        }
    }

    solve(nls[0], v);
}

void acchiappa(int n, vector<int> U, vector<int> V) { // NOLINT
    N = n;
    G.resize(N);
    S.resize(N);
    C.resize(N);

    forall(i, 0, N-1) {
        G[U[i]].push_back(V[i]);
        G[V[i]].push_back(U[i]);
    }

    dfs(0, -1, 0);

    vi qry;

    forall(i, 0, N)
        if(C[i]) qry.push_back(i);

    bool col = ispeziona(qry);
    
    col = !col; // z si muove

    int st = centroid(0, !col);

    dfs(st, -1, C[st]);

    int v = solve_start(st, col);
    if(v == -1) return;

    solve(v, st);
}
