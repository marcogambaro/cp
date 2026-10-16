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

#include "longesttrip.h"

bool ask(int a, int b) {
    return are_connected({a}, {b});
}

std::vector<int> longest_trip(int N, int D) {
    vec<int> v1 = {0}, v2 = {1};

    for(int i=2; i<N-1; i+=2) {
        bool s1 = ask(i, v1.back());
        bool s2 = ask(i, v2.back());
        bool s = ask(i, i+1);

        if(s1 & s) {
            v1.push_back(i);
            v1.push_back(i+1);
        }
        else if(s2 & s) {
            v2.push_back(i);
            v2.push_back(i+1);
        }
        else if(s) {
            reverse(all(v2));
            for(int j: v2) v1.push_back(j);
            v2 = {i, i+1};
        }
        else if(s1 & s2) {
            v1.push_back(i);
            reverse(all(v2));
            for(int j: v2) v1.push_back(j);
            v2 = {i+1};
        }
        else if(s1) {
            v1.push_back(i);
            v2.push_back(i+1);
        }
        else if(s2) {
            v2.push_back(i);
            v1.push_back(i+1);
        }
        else {
            v1.push_back(i+1);
            reverse(all(v2));
            for(int j: v2) v1.push_back(j);
            v2 = {i};
        }
    }

    if(N%2 == 1) {
        int i = N-1;
        if(ask(i, v1.back())) v1.push_back(i);
        else if(ask(i, v2.back())) v2.push_back(i);
        else {
            reverse(all(v2));
            for(int j: v2) v1.push_back(j);
            v2 = {i};
        }
    }

    if(v2.size() > v1.size()) v1.swap(v2);
    if(v2.empty()) return v1;

    auto search = [&](vec<int> v, vec<int> u) -> int {
        reverse(v.begin()+1, v.end());
        int l = -1, r = v.size();
        while(r-l > 1) {
            int m = (l+r)/2;

            vec<int> v3;
            for(int j=0; j<=m; j++)
                v3.push_back(v[j]);

            if(!are_connected(v3, u)) l = m;
            else r = m;
        }

        if(r == v.size()) return -1;
        return v[r];
    };

    vec<int> ans;

    int n1 = search(v1, v2);

    if(n1 == -1) return v1;
    if(n1 != v1[0]) {
        int n2 = search(v2, {n1});

        if(n1 != v1.back()) {
            bool ins = 0;
            for(int i=0; i<v1.size(); i++) {
                if(ins) ans.push_back(v1[i]);
                if(v1[i] == n1) ins = 1;
            }
            for(int i=0; ;i++) {
                ans.push_back(v1[i]);
                if(v1[i] == n1) break;
            }
        } else {
            ans = v1;
        }

        ans.push_back(n2);
        for(int j: v2) if(j != n2) ans.push_back(j);
    }
    else {
        if(v2.size() == 1 || ask(v2[0], v2.back())) {
            int n2 = search(v2, {n1});
            reverse(all(v1));
            ans = v1;
            bool ins = 0;
            for(int i=0; i<v2.size(); i++) {
                if(v2[i] == n2) ins = 1;
                if(ins) ans.push_back(v2[i]);
            }
            for(int i=0; ;i++) {
                if(v2[i] == n2) break;
                ans.push_back(v2[i]);
            }
        }
        else {
            reverse(all(v1));
            if(ask(n1, v2.back())) reverse(all(v2));

            for(int i: v1) ans.push_back(i);
            for(int j: v2) ans.push_back(j);
        }
    }

    return ans;
}

#ifdef LOCAL
static inline constexpr int maxNumberOfCalls = 32640;
static inline constexpr int maxTotalNumberOfCalls = 150000;
static inline constexpr int maxTotalNumberOfLandmarksInCalls = 1500000;
static int call_counter = 0;
static int total_call_counter = 0;
static int landmark_counter = 0;

static int C, N, D;
static std::vector<std::vector<int>> U;
static std::vector<bool> present;

static inline void protocol_violation(std::string message)
{
    printf("Protocol Violation: %s\n", message.c_str());
    exit(0);
}

bool are_connected(std::vector<int> A, std::vector<int> B)
{
    ++call_counter;
    ++total_call_counter;
    if (call_counter > maxNumberOfCalls || total_call_counter > maxTotalNumberOfCalls)
    {
        protocol_violation("too many calls");
    }

    int nA = A.size(), nB = B.size();
    landmark_counter += nA + nB;
    if (landmark_counter > maxTotalNumberOfLandmarksInCalls)
    {
        protocol_violation("too many elements");
    }

    if (nA == 0 || nB == 0)
    {
        protocol_violation("invalid array");
    }
    for (int i = 0; i < nA; ++i)
    {
        if (A[i] < 0 || N <= A[i])
        {
            protocol_violation("invalid array");
        }
        if (present[A[i]])
        {
            protocol_violation("invalid array");
        }
        present[A[i]] = true;
    }
    for (int i = 0; i < nA; ++i)
    {
        present[A[i]] = false;
    }
    for (int i = 0; i < nB; ++i)
    {
        if (B[i] < 0 || N <= B[i])
        {
            protocol_violation("invalid array");
        }
        if (present[B[i]])
        {
            protocol_violation("invalid array");
        }
        present[B[i]] = true;
    }
    for (int i = 0; i < nB; ++i)
    {
        present[B[i]] = false;
    }

    for (int i = 0; i < nA; ++i)
    {
        for (int j = 0; j < nB; ++j)
        {
            if (A[i] == B[j])
            {
                protocol_violation("non-disjoint arrays");
            }
        }
    }

    for (int i = 0; i < nA; ++i)
    {
        for (int j = 0; j < nB; ++j)
        {
            if (U[std::max(A[i], B[j])][std::min(A[i], B[j])] == 1)
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    assert(1 == scanf("%d", &C));
    int maximumCalls = 0;
    for (int c = 0; c < C; ++c)
    {
        call_counter = 0;
        assert(2 == scanf("%d %d", &N, &D));

        present.assign(N, false);
        U.resize(N);
        for (int i = 1; i < N; ++i)
        {
            U[i].resize(i);
            for (int j = 0; j < i; ++j)
            {
                assert(1 == scanf("%d", &U[i][j]));
            }
        }

        for (int i = 2; i < N; ++i)
        {
            for (int j = 1; j < i; ++j)
            {
                for (int k = 0; k < j; ++k)
                {
                    if (U[i][j] + U[i][k] + U[j][k] < D)
                    {
                        printf("Insufficient Density\n");
                        exit(0);
                    }
                }
            }
        }

        std::vector<int> t = longest_trip(N, D);
        int l = t.size();
        printf("%d\n", l);
        for (int i = 0; i < l; ++i)
        {
            printf(i == 0 ? "%d" : " %d", t[i]);
        }
        printf("\n");
        printf("%d\n", call_counter);

        maximumCalls = std::max(maximumCalls, call_counter);
        call_counter = 0;
    }
    printf("%d\n", maximumCalls);

    return 0;
}

#endif
