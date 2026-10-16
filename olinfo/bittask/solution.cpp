#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

vector<int> assegna(int N, int M, vector<vector<int>> S) {
    vector<int> seen(M, -1);
    vector<vector<int>> vs(N);
    vector<vector<int>> fix(M);
    vector<int> cond(M);

    for(int i = N-1; i >= 0; i--) {
        for(int s: S[i]) {
            if(seen[s] != i+1 && seen[s] != -1) {
                vs[seen[s]-1].push_back(s);
                cond[s]++;
            }

            if(seen[s] != i+1)
                fix[s].push_back(i);

            seen[s] = i;
        }
    }

    for(int s = 0; s < M; s++) {
        if(seen[s] != 0 && seen[s] != -1) {
            vs[seen[s]-1].push_back(s);
            cond[s]++;
        }
    }

    stack<int> st;

    for(int i = 0; i < M; i++) {
        if(cond[i] == 0) st.push(i);
    }

    vector<int> ans(M);
    int K = M-1;

    while(!st.empty()) {
        int s = st.top();
        st.pop();
        ans[s] = K--;

        for(int i: fix[s]) {
            for(int v: vs[i]) {
                if(--cond[v] == 0) st.push(v);
            }

            vs[i].clear();
        }
    }

    return K == -1 ? ans : vector<int>();
}
