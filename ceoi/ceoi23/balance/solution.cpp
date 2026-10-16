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
int tn = 0;
vector<vector<int>> ans;

void solve(int S, vector<vector<int>> &tb) {
    vector<vector<int>> L(N), R(N);

    if(S == 1) {
        for(int i=0;i<N; i++)
            ans[i][tn] = tb[i][0];
        tn++;
        return;
    }

    map<int, queue<pair<int, int>>> G;
    int te = 0;
    vector<int> line;

    for(int i=0; i<N; i++) {
        sort(all(tb[i]));
        int x = tb[i][0];
        int f = 1;

        vector<int> ex;

        for(int j = 1; j < S; j++) {
            if(x != tb[i][j]) {
                for(; f > 1; f -= 2) {
                    L[i].push_back(x);
                    R[i].push_back(x);
                }
                if(f) {
                    ex.push_back(x);
                }

                x = tb[i][j];
                f = 1;
            }
            else f++;
        }

        for(; f > 1; f -= 2) {
            L[i].push_back(x);
            R[i].push_back(x);
        }
        if(f) {
            ex.push_back(x);
        }

        if(ex.size()%2) while(1);
        for(int k=0; k<ex.size(); k+=2) {
            line.emplace_back(i);
            G[ex[k]].emplace(ex[k+1], te);
            G[ex[k+1]].emplace(ex[k], te);
            te++;
        }
    }

    vector<bool> ed(te);

    auto push = [&](int v, bool w, auto &&self) -> bool {
        queue<pii> &q = G[v];

        while(!q.empty()) {
            if(ed[q.front().se]) {
                q.pop();
                continue;
            }
            auto [u, e] = q.front();
            q.pop();
            ed[e] = 1;

            if(!w) {
                L[line[e]].push_back(v);
                R[line[e]].push_back(u);
                infof("edge %d -> %d", v, u);
            }
            else {
                L[line[e]].push_back(u);
                R[line[e]].push_back(v);
                infof("edge %d -> %d", u, v);
            }

            self(u, w, self);
            return 1;
        }
        return 0;
    };

    for(auto &[k, v]: G) {
        bool w = 0;
        while(push(k, w, push)) w ^= 1;;
    }

    solve(S/2, L);
    solve(S/2, R);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int S, T; cin >> N >> S >> T;
    ans = vector(N, vector<int>(S));

    vector<vector<int>> tb(N, vector<int>(S));
    for(auto &a: tb) for(auto &b: a) cin >> b;

    solve(S, tb);

    for(auto &a: ans) {
        for(auto &b: a) {
            cout << b << " ";
        }
        cout << lf;
    }
}
