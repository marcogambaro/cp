#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> P;
    vector<int> H;

    DSU(int N) {
        P.assign(N, -1);
        H.resize(N);
        iota(H.begin(), H.end(), 0);
    }

    int find(int i) {
        return P[i]<0? i : P[i] = find(P[i]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);

        if(a == b) return;

        int h = H[b];

        if(P[a] > P[b]) swap(a, b);

        H[a] = h;
        P[a] += P[b];
        P[b] = a;
    }
};

long long acquista(int N, int M, int L, vector<int> X, vector<int> T) {
    sort(X.begin(), X.end());
    sort(T.begin(), T.end());

    vector<int> I(N);

    int j = 0;
    for(int i=0; i<N; i++) {
        for(; j<M && T[j]<X[i]; j++);
        I[i] = j;
    }

    DSU dsu(M+1);

    long long ans = 0;

    for(int i=N-1; i>=0; i--) {
        j = dsu.H[dsu.find(I[i])];
        if(j == M) continue;

        ans += L - min(L, T[j]-X[i]);
        dsu.merge(j, j+1);
    }

    return ans;
}
