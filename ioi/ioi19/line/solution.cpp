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

pii rev(pii p) {
    return {p.se, p.fi};
}

struct Dt {
    set<pii> stx, sty;

    void insert(pii p) {
        stx.insert(p);
        sty.insert(rev(p));
    }
    void erase(pii p) {
        stx.erase(p);
        sty.erase(rev(p));
    }

    // 0=right, 1=up, 2=left, 3=down
    pii dir(int d) {
        pii p;
        if(d == 0) p = *prev(stx.end());
        if(d == 1) p = *prev(sty.end());
        if(d == 2) p = *stx.begin();
        if(d == 3) p = *sty.begin();
        if(d&1) p = rev(p);
        return p;
    }

    int size() {
        return stx.size();
    }
};

void solve(ifstream &cin, ofstream &cout) {
    int N; cin >> N;
    Dt pts;

    for(int i=0; i<N; i++) {
        int x, y; cin >> x >> y;
        pts.insert({x, y});
    }

    vec<array<pii, 4>> squares;
    vec<vec<pii>> V(4);

    while(pts.size()) {
        pii low = pts.dir(3);
        pii high = pts.dir(1);
        pii l = pts.dir(2);
        pii r = pts.dir(0);

        if(low == l) {
            V[0].push_back(low);
            pts.erase(low);
        }
        else if(low == r) {
            V[1].push_back(low);
            pts.erase(low);
        }
        else if(high == r) {
            V[2].push_back(high);
            pts.erase(high);
        }
        else if(high == l) {
            V[3].push_back(high);
            pts.erase(high);
        }
        else {
            squares.push_back({r, high, l, low});
            pts.erase(low);
            pts.erase(high);
            pts.erase(l);
            pts.erase(r);
        }
    }

    reverse(all(V[2]));
    for(pii p: V[2]) V[0].push_back(p);
    reverse(all(V[3]));
    for(pii p: V[3]) V[1].push_back(p);

    sort(all(squares));
    // infof("squares: {}", squares);
    // infof("V[0]: {}", V[0]);
    // infof("V[1]: {}", V[1]);

    vec<pii> ans = {{0, 0}};

    auto move = [&](vec<pii> V) {
        for(auto &[x, y]: V) {
            if(ans.size() == 1) ans.emplace_back(x, 0);
            int s = ans.size();

            if(ans[s-2].se == ans[s-1].se) {
                if((ans[s-2].fi < ans[s-1].fi) == (ans[s-1].fi < x)) {
                    ans.pop_back();
                }
                if(x != ans.back().fi) ans.emplace_back(x, ans.back().se);
            }
            else {
                if((ans[s-2].se < ans[s-1].se) == (ans[s-1].se < y)) {
                    ans.pop_back();
                }
                if(y != ans.back().se) ans.emplace_back(ans.back().fi, y);
            }

            ans.emplace_back(x, y);
        }
    };

    for(auto &[r, h, l, d]: squares) {
        if(ans.back().se < r.se) {
            // counterclockwise
            move({r, h, l, d});
        }
        else {
            // clockwise
            move({r, d, l, h});
        }
    }

    if(V[1].size()) {
        if(ans.size() > 2) ans.pop_back();
        ans.emplace_back(2e9, ans.back().se);
        ans.emplace_back(2e9, V[1][0].se);
        move(V[1]);
    }
    if(V[0].size()) {
        if(ans.size() > 2 && ans[ans.size()-1].fi == ans[ans.size()-2].fi) {
            reverse(all(V[0]));
            ans.pop_back();
            ans.emplace_back(ans.back().fi, 2e9);
            ans.emplace_back(V[0][0].fi, 2e9);
        }
        else if(ans.size() > 2 && ans[ans.size()-1].se == ans[ans.size()-2].se) {
            ans.pop_back();
            ans.emplace_back(0, ans.back().se);
            ans.emplace_back(0, V[0][0].se);
        }
        move(V[0]);
    }

    cout << ans.size()-1 << lf;
    for(int i=1; i<ans.size(); i++)
        cout << ans[i].fi _ ans[i].se << lf;

    cerr << "Solved with extra = " << ans.size()-1-N << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int L, R; cin >> L >> R;

    for(int i=L; i<=R; i++) {
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
