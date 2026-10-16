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

#include "monuments.h"

struct mon {
    int x = 0;
    int t = 0;
};

struct fen {
    vec<ll> v;

    fen(int N) { v.resize(N+40); }

    void add(int i, ll k) {
        infof("adding i={}, k={}", i, k);
        i += 3;
        while(i < v.size()) {
            v[i] += k;
            i += i&-i;
        }
    }
    ll pfx(int i) {
        ll res = 0;
        i += 3;
        while(i) {
            res += v[i];
            i -= i&-i;
        }
        return res;
    }
    ll sum(int l, int r) {
        return pfx(r-1) - pfx(l-1);
    }
};

int lw(vec<int> &v, int k) {
    int l=-1, r=v.size();
    while(r-l > 1) {
        int m = (l+r)/2;
        if(v[m] >= k) l = m;
        else r = m;
    }
    return r;
}

int lweq(vec<int> &v, int k) {
    int l=-1, r=v.size();
    while(r-l > 1) {
        int m = (l+r)/2;
        if(v[m] > k) l = m;
        else r = m;
    }
    return r;
}

vec<ll> absosolver(vec<mon> &A, vec<mon> &B, vec<array<int, 3>> &Q) {
    int N = Q.size();
    vec<ll> ans(N);

    vec<int> a0, a1, b0, b1;
    vec<int> cna0, cna1, cnb0, cnb1;
    for(int i=0; i<A.size(); i++) {
        if(!A[i].t) a0.push_back(A[i].x), cna0.push_back(i);
        else        a1.push_back(A[i].x), cna1.push_back(i);
    }
    for(int i=0; i<B.size(); i++) {
        if(!B[i].t) b0.push_back(B[i].x), cnb0.push_back(i);
        else        b1.push_back(B[i].x), cnb1.push_back(i);
    }

    vec<vec<int>> qs((A.size()+B.size()+1)*2);
    vec<vec<pii>> qfw((A.size()+B.size()+1)*2);
    int OFF = A.size()+B.size()+1;

    fen fw(A.size());

    for(int i=0; i<Q.size(); i++) {
        qs[Q[i][2]+OFF].push_back(i);
    }

    for(int i=0; i<a1.size(); i++) {
        int j = lw(b0, a1[i])-1;
        qfw[i-j+OFF].emplace_back(cna1[i], a1[i]);
    }
    for(int i=0; i<b0.size(); i++) {
        int j = lweq(a1, b0[i]);
        fw.add(cnb0[i], b0[i]);
        qfw[j-i+OFF].emplace_back(cnb0[i], -b0[i]);
    }
    for(int i=0; i<b1.size(); i++) {
        int j = lw(a0, b1[i])-1;
        qfw[i-j+OFF].emplace_back(cnb1[i], b1[i]);
    }
    for(int i=0; i<a0.size(); i++) {
        int j = lweq(b1, a0[i]);
        fw.add(cna0[i], a0[i]);
        qfw[j-i+OFF].emplace_back(cna0[i], -a0[i]);
    }

    for(int i=0; i<qs.size(); i++) {
        for(auto [j, k]: qfw[i]) {
            fw.add(j, k);
        }

        for(int q: qs[i]) {
            auto [l, r, tt] = Q[q];
            ans[q] = fw.sum(l, r);
        }
    }

    return ans;
}

vec<ll> sufsolver(vec<int> &v1, vec<int> &v0, vec<array<int, 4>> &Q) {
    vec<ll> ans(Q.size());

    vec<vec<int>> qs((v1.size()+v0.size()+1)*2);
    vec<vec<pii>> qfw1((v1.size()+v0.size()+1)*2);
    vec<vec<pii>> qfw0((v1.size()+v0.size()+1)*2);
    int OFF = v1.size()+v0.size()+1;

    fen fw1(v1.size()), fw0(v0.size());

    for(int i=0; i<Q.size(); i++) {
        qs[Q[i][3]+OFF].push_back(i);
    }

    for(int i=0; i<v1.size(); i++) {
        int j = lw(v0, v1[i])-1;
        qfw1[i-j+OFF].emplace_back(i, v1[i]);
    }
    for(int i=0; i<v0.size(); i++) {
        int j = lweq(v1, v0[i]);
        fw0.add(i, v0[i]);
        qfw0[j-i+OFF].emplace_back(i, -v0[i]);
    }

    for(int i=0; i<qs.size(); i++) {
        for(auto [j, k]: qfw1[i]) {
            fw1.add(j, k);
        }
        for(auto [j, k]: qfw0[i]) {
            fw0.add(j, k);
        }

        for(int q: qs[i]) {
            auto [l1, l0, s, tt] = Q[q];
            ans[q] = fw1.sum(l1, l1+s) + fw0.sum(l0, l0+s);
        }
    }

    return ans;
}

long long get_cost(std::vector<int> X, std::vector<int> P) {
    int N = X.size();
    vec<int> stat(N, 1);
    for(int i: P) stat[i] = 0;

    int a=0, b=N-1;
    while(a <= b) {
        int x = max(abs(X[a]), abs(X[b]));
        vec<int> na, nb;
        if(x != 0) {
            while(a < N && X[a] == -x) {
                if(stat[a] == 0) na.push_back(a);
                a++;
            }
            while(b >= 0 && X[b] == x) {
                if(stat[b] == 0) nb.push_back(b);
                b--;
            }
            for(int j=0; j<min(na.size(), nb.size()); j++)
                stat[na[j]] = stat[nb[j]] = -1;
        }
        else {
            while(a <= b) {
                if(stat[a] == 0) stat[a] = -1;
                a++;
            }
        }
    }

    vec<mon> A, B;
    ll tot = 0;
    for(int i=0; i<N; i++) {
        if(stat[i] == -1) continue;
        if(X[i] <= 0) A.push_back({-X[i], stat[i]});
        else          B.push_back({X[i], stat[i]});
        tot += abs(X[i]);
    }

    reverse(all(B));
    if(B.size() > A.size()) A.swap(B);
    int S = B.size();

    infor("A: ");
    for(auto [x, t]: A) infor("{}/{} ", x, t);
    infof("");
    infor("B: ");
    for(auto [x, t]: B) infor("{}/{} ", x, t);
    infof("");

    vec<int> tra(S, -1), rm(S); // dp transiction in N
    vec<int> last(S*4 + 7, -1);
    int pf = S*2;
    last[pf] = 0;

    for(int i=0; i<S; i++) {
        bool no = 0;
        if(A[i].t && B[i].t) pf++;
        else if(!A[i].t && !B[i].t) pf--;
        else no = 1;

        tra[i] = last[pf];
        rm[i] = pf - S*2;
        last[pf] = i+1;
    }

    vec<array<int, 3>> Q(S);
    for(int i=0; i<S; i++) Q[i] = {tra[i], i+1, rm[i]};

    vec<ll> cost = absosolver(A, B, Q);

    vec<int> A0, A1, B0, B1;
    for(int i=0; i<A.size(); i++) {
        if(A[i].t) A1.push_back(A[i].x);
        else       A0.push_back(A[i].x);
    }
    for(int i=0; i<B.size(); i++) {
        if(B[i].t) B1.push_back(B[i].x);
        else       B0.push_back(B[i].x);
    }

    int a0=0, a1=0, b0=0, b1=0;
    vec<ll> dp(S+1, -1e18);
    dp[0] = 0;

    for(int i=0; i<A.size(); i++) {
        if(A[i].t) a1++;
        else a0++;
    }
    for(int i=0; i<B.size(); i++) {
        if(B[i].t) b1++;
        else b0++;
    }

    int ca0=0, ca1=0, cb0=0, cb1=0;
    vec<array<int, 4>> Qa(A.size()+1), Qb(A.size()+1);
    for(int i=0; i<A.size(); i++) {
        Qa[i] = {ca1, cb0, min(a1-ca1, b0-cb0), ca1-cb0};
        Qb[i] = {cb1, ca0, min(b1-cb1, a0-ca0), cb1-ca0};
        if(A[i].t) ca1++;
        else       ca0++;
        if(i < S) {
            if(B[i].t) cb1++;
            else       cb0++;
        }
    }

    vec<ll> sa = sufsolver(A1, B0, Qa);
    vec<ll> sb = sufsolver(B1, A0, Qb);

    infof("tra: {}", tra);
    infof("rm: {}", rm);
    infof("cost: {}", cost);
    infof("sa: {}", sa);
    infof("sb: {}", sb);

    ll ans = -1e18;
    for(int i=-1; i<S;i++) {
        if(i != -1) {
            if(A[i].t || B[i].t) dp[i+1] = dp[i] + min(A[i].x, B[i].x);
            if(tra[i] > -1) dp[i+1] = max(dp[i+1], dp[tra[i]] + cost[i]);

            if(A[i].t) a1--;
            else       a0--;
            if(B[i].t) b1--;
            else       b0--;
        }

        if(b0 + a0 <= a1 + b1) {
            ans = max(dp[i+1]+sa[i+1]+sb[i+1], ans);
        }
    }

    infof("dp: {}", dp);
    infof("tot = {}, ans = {}", tot, ans);
    if(ans < 0) return -1;
    return tot - 2*ans;
}

#ifdef LOCAL
int main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));

  std::vector<int> X(N);
  for (int i = 0; i < N; i++) {
    assert(1 == scanf("%d", &X[i]));
  }

  std::vector<int> P(M);
  for (int i = 0; i < M; i++) {
    assert(1 == scanf("%d", &P[i]));
  }
  fclose(stdin);

  long long res = get_cost(X, P);

  printf("%lld\n", res);
  fclose(stdout);
  return 0;
}
#endif
