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

int N;
vec<int> P;
vec<pii> cyc;
vec<int> szc;
vec<int> pvi, sci;
// pvi: element before i that, in the cycle, has position pos[i]--
// sci: element before i that, in the cycle, has position pos[i]++

void find_cyc() {
    cyc.resize(N);
    int c = 0;
    vec<int> vis(N);

    for(int i=0; i<N; i++) {
        if(vis[i]) continue;
        int j = i;
        int k = 0;
        do {
            vis[j] = 1;
            cyc[j] = {c, k++};
            j = P[j];
        } while(i != j);
        szc.push_back(k);
        c++;
    }

    pvi.resize(N, -1);
    sci.resize(N, -1);

    for(int i=0; i<N; i++) {
        for(int j=0; j<i; j++) {
            if(cyc[j].fi != cyc[i].fi) continue;

            if(cyc[j].se < cyc[i].se) {
                if(pvi[i] == -1 || cyc[pvi[i]].se < cyc[j].se)
                    pvi[i] = j;
            } else {
                if(sci[i] == -1 || cyc[sci[i]].se > cyc[j].se)
                    sci[i] = j;
            }
        }
    }
}

void do1() { // for each cycle, do xor with previous
    int B[N];

    for(int i = 0; i < N; i++) {
        cin >> B[i];

        cout << (pvi[i] == -1 ? B[i] : B[i] ^ B[pvi[i]]) << endl;
    }
}

void do2() { // for each cycle, do suffix xor
    int B[N];

    for(int i = N-1; i >= 0; i--) {
        cin >> B[i];

        // first, restore the REAL value of B[i]
        if(pvi[i] != -1) {
            for(int j=N-1; j>i; j--) {
                if(cyc[j].fi != cyc[i].fi) continue;
                if(cyc[pvi[i]].se < cyc[j].se && cyc[j].se < cyc[i].se)
                    B[i] ^= B[j];
            }
        }

        // now do suffix xor
        int x = B[i];
        for(int j=N-1; j>i; j--) {
            if(cyc[j].fi == cyc[i].fi && cyc[j].se > cyc[i].se)
                if(sci[i] == -1 || cyc[j].se < cyc[sci[i]].se)
                    x ^= B[j];
        }

        cout << x << endl;
    }
}

void do3() {
    int B[N];

    for(int i = 0; i < N; i++) {
        cin >> B[i];

        // first, restore tjhe REAL suffix xor of i
        if(sci[i] != -1) B[i] ^= B[sci[i]];

        // now do xor with the first of the cycle
        int x = B[i];
        for(int j=0; j<i; j++) if(cyc[j] == make_pair(cyc[i].fi, 0)) x ^= B[j];

        cout << x << endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int W; cin >> W;
    if(W == 0) {
        cout << 3 << lf;
        return 0;
    }

    cin >> N;
    P.resize(N);
    for(auto &i: P) cin >> i;

    // ops! invert the permutation!
    vec<int> ivP(N);
    for(int i=0; i<N; i++)
        ivP[P[i]] = i;
    P.swap(ivP);

    find_cyc();

    if(W == 1) do1();
    if(W == 2) do2();
    if(W == 3) do3();
}