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


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vec<int> vl(N, -1), vr(N, -1);
    vec<pii> vp(M+1);
    vp[0] = {0, N-1};

    for(int i=0; i<M; i++) {
        int a, b; cin >> a >> b;
        if(b < a) swap(a, b);
        vl[a] = i+1;
        vr[b] = i+1;
        vp[i+1] = {a, b};
    }

    stack<int> st;
    st.push(0);
    vec<vec<int>> G(M+1);

    for(int i=0; i<N; i++) {
        if(vl[i] != -1) {
            G[st.top()].push_back(vl[i]);
            st.push(vl[i]);
        }
        if(vr[i] != -1) {
            assert(st.top() == vr[i]);
            st.pop();
        }
    }

    vector dp(2, vec<int>(M+1));
    vec<int> spu(M+1, -1);

    auto dfs = [&](int v, auto &&dfs) -> void {
        int p = vp[v].fi;
        int k = 0;
        int x = 0;

        for(int u: G[v]) {
            dfs(u, dfs);
            k ^= (vp[u].fi - p)%2;
            p = vp[u].se;

            if(dp[0][u] < dp[1][u]) x += dp[0][u];
            else                    x += dp[1][u], k ^= 1;

            if(dp[0][u] == dp[1][u]) spu[v] = u;
        }

        k ^= (vp[v].se - p)%2;

        dp[k][v] = x;
        dp[!k][v] = x + (spu[v]==-1);
        dp[0][v]++;
    };
    dfs(0, dfs);

    cout << min(dp[0][0], dp[1][0]) << lf;

    vec<int> ans(N);
    vec<int> choose(M+1);

    auto color = [&](int v, int m, int c, auto &&color) -> void {
        int p = vp[v].fi;
        int k = 0;

        for(int u: G[v]) {
            k ^= (vp[u].fi - p)%2;
            p = vp[u].se;

            if(dp[0][u] < dp[1][u]) choose[u] = 0;
            else                    choose[u] = 1, k ^= 1;
        }

        k ^= (vp[v].se - p)%2;
        p = vp[v].fi;

        int sp = 0;
        if(k != m && spu[v] != -1)
            choose[spu[v]] ^= 1;
        else if(k != m)  sp = 1;

        for(int u: G[v]) {
            while(p < vp[u].fi) {
                ans[p++] = c;
                if(!sp) c ^= 1;
                else    sp = 0;
            }
            color(u, choose[u], c, color);
            p = vp[u].se;
            c = ans[p];
        }

        while(p <= vp[v].se) {
            ans[p++] = c;
            if(!sp) c ^= 1;
            else    sp = 0;
        }
    };
    color(0, dp[1][0] < dp[0][0], 0, color);

    for(int i: ans) cout << i << " ";
    cout << lf;
}

