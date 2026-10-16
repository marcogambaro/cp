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

#include "permutation.h"

vec<pii> rg;

struct Susser {
    priority_queue<array<int, 3>> p0, p1;
    vec<vec<pii>> vl, vm, vr;
    vec<int> tm;
    int N;

    Susser() {
        N = rg.size();
        tm.resize(N);
    }

    void init() {
        vl = vm = vr = vec<vec<pii>>(N+1);
        while(!p0.empty()) p0.pop();
        while(!p1.empty()) p1.pop();
        for(int i=0; i<N; i++) update(i);
    }

    void update(int i) {
        auto [l, r] = rg[i];
        int m = (l+r)/2;

        tm[i] += 7;
        if(rg[i].se == rg[i].fi+1) return;
        vl[l].emplace_back(i, tm[i]);
        vm[m].emplace_back(i, tm[i]+1);
        vr[r].emplace_back(i, tm[i]+2);
    }

    void mov(int l) {
        for(auto [i, t]: vl[l]) {
            if(t == tm[i]) p0.push({-rg[i].fi+1, i, t});
        }

        for(auto [i, t]: vm[l]) {
            if(t == tm[i]+1) {
                tm[i]++;
                p1.push({rg[i].se-1, i, t});
            }
        }

        for(auto [i, t]: vr[l]) {
            if(t == tm[i]+1) {
                tm[i]++;
            }
        }
    }

    int calc(int i) {
        mov(i);
        //infof("tm = {}\np0 = {}\np1 = {}\n", tm, p0, p1);

        while(!p0.empty() && p0.top()[2] != tm[p0.top()[1]])
            p0.pop();
        while(!p1.empty() && p1.top()[2] != tm[p1.top()[1]])
            p1.pop();

        if(p0.empty() && p1.empty()) return 0;
        if(p0.empty()) return p1.top()[1];
        if(p1.empty()) return p0.top()[1];

        return i+p0.top()[0] < p1.top()[0]-i ? p1.top()[1] : p0.top()[1];
    }
};


std::vector<int> solve(int N) {
    rg.resize(N, {0, N});

    int k = 0;
    int a = 1;
    vec<int> ans(N, -1);
    vec<int> ok(N, 0);
    int solved = 0;

    Susser sus;

    while(solved < N) {
        if(k == 0) sus.init();

        int i = sus.calc(k);
        int s = press_button(i);

        if(s == a) rg[i].se = min(rg[i].se, k+1);
        else       rg[i].fi = max(rg[i].fi, k+1);
        sus.update(i);

        k++;
        if(k == N) {
            k = 0;
            a ^= 1;
        }
        //infof("range of screen {} = {}", i, rg[i]);

        if(rg[i].se == rg[i].fi+1 && !ok[i]) {
            ok[i] = 1;
            ans[rg[i].fi] = i;
            solved++;
        }
    }

    return ans;
}

#ifdef LOCAL
int N;
vec<int> S, P;
int kk = 0;

int press_button(int i) {
    S[P[kk % N]] ^= 1;
    kk++;
    return S[i];
}

int main() {
    cin >> N;
    P.resize(N);
    S.resize(N);

    iota(all(P), 0);
    timmy_loves_gambling.seed(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(all(P), timmy_loves_gambling);

    for(int &i: P) cout << i << " ";
    cout << lf;

    vec<int> ans = solve(N);

    for(auto &i: ans) cout << i << " ";
    cout << lf;
    assert(ans == P);
    cout << kk << " guesses" << lf;
}
#endif
