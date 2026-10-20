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

#include "squirrel.h"

void solve(int N, vector<vector<int>> A, long long& answer, vector<int>& solution) {
    vec<pii> V(N*(N+1)/2+1);
    for(int i=0; i<N; i++) for(int j=0; j<=i; j++) V[A[i][j]] = {i, j};

    answer = 0;
    solution.resize(N);

    vec<int> ar(N+1);
    iota(all(ar), 1);

    set<int> can;
    for(int i=0; i<N; i++) can.insert(i);

    vec<int> st;

    auto move = [&](int v, int x, auto &&move) -> int {
        if(x == 0) {
            st.push_back(v);
            return 1;
        }

        while(ar[v] <= V[x].fi) {
            if(move(ar[v], solution[ar[v]], move)) {
                st.push_back(v);
                return 1;
            }
            ar[v]++;
        }

        can.erase(v);
        return 0;
    };

    for(int x=N*(N+1)/2; x>0; x--) {
        auto [i, j] = V[x];

        while(1) {
            auto it = can.lower_bound(j);
            if(it == can.end() || *it > i) break;

            st.clear();

            if(move(*it, solution[*it], move)) {
                int ogx = x;
                answer += x;

                reverse(all(st));
                for(int k = 0; k < (int)st.size()-1; k++) {
                    if(V[x].fi < V[solution[st[k]]].fi) {
                        swap(x, solution[st[k]]);
                    }
                }

                assert(solution[st.back()] == 0);
                solution[st.back()] = x;

                x = ogx;
                break;
            }
        }
    }
}

#ifdef LOCAL
vector<vector<int>> read_input() {
  int N;
  cin >> N;
  vector<vector<int>> mat(N);
  for (int i = 0; i < N; i++) {
    mat[i].resize(i + 1);
    for (auto& x : mat[i]) {
      cin >> x;
    }
  }
  return mat;
}

void print_output(long long answer, vector<int> solution) {
  cout << answer << "\n";
  for (auto i = 0; i < solution.size(); i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << solution[i];
  }
  cout << "\n";
}

int main() {
  auto mat = read_input();
  long long result;
  vector<int> solution;
  solution.reserve(mat.size());

  int n = mat.size();
  solve(n,
        move(mat),
        result,
        solution);

  print_output(result, move(solution));
  return 0;
}
#endif
