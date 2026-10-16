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

#include "incursion.h"

vec<vec<int>> G, G2;

std::vector<int> mark(std::vector<std::pair<int, int>> F, int safe) {
	int N = F.size()+1;
	G.resize(N+1);

	for(auto [a, b]: F) {
		G[a].push_back(b);
		G[b].push_back(a);
	}

	vec<int> ans(N);

    vec<bool> cnt(N+1);
    auto dfs = [&](int v, int f, auto &&self) -> int {
        int sf = 0;
        bool ok = 1;

        for(auto &u: G[v]) {
            if(u == f) continue;
            int k = self(u, v, self);
            if(k*2 > N) ok = 0;
            sf += k;
        }

        if(ok && (N-1-sf)*2 <= N) cnt[v] = 1;
        return sf+1;
    };
    dfs(1, 0, dfs);

    auto color = [&](int v, int f, auto &&self) -> int {
        if(cnt[v])  return ans[v-1] = 1;
        int ok = 0;

        for(auto &u: G[v]) {
            if(u == f) continue;
            ok |= self(u, v, self);
        }

        return ans[v-1] = ok;
    };
    color(safe, 0, color);

    return ans;
}

void locate(std::vector<std::pair<int, int>> F, int curr, int t) {
	int N = F.size()+1;
    G = vec<vec<int>>();
	G.resize(N+1);

	for(auto [a, b]: F) {
		G[a].push_back(b);
		G[b].push_back(a);
	}

	vec<int> par(N+1);
    vec<int> sz(N+1, 1);
    int ctr = -1, ctr2 = -1;

    auto dfs = [&](int v, int f, auto &&self) -> int {
        int sf = 0;
        bool ok = 1;

        for(auto &u: G[v]) {
            if(u == f) continue;
            int k = self(u, v, self);
            if(k*2 > N) ok = 0;
            sf += k;
        }

        if(ok && (N-1-sf)*2 <= N) {
            if(ctr == -1) ctr = ctr2 = v;
            else ctr2 = v;
        }
        return sf+1;
    };
    dfs(1, 0, dfs);

	auto dfs2 = [&](int v, int f, auto &&self) -> void {
        par[v] = f;
		for(auto &u: G[v]) {
			if(u == f) continue;
			self(u, v, self);
            sz[v] += sz[u];
		}
	};
	dfs2(ctr, -1, dfs2);

    par[ctr] = ctr2;
    par[ctr2] = ctr;

    while(t == 0) {
        curr = par[curr];
        t = visit(curr);
    }
	
    int f = par[curr];
    while(1) {
        vec<int> v;

        for(auto &u: G[curr]) {
            if(u == f) continue;
            v.push_back(u);
        }
        sort(all(v), [&](int i, int j){return sz[i] > sz[j];});

        bool ok = 0;
        for(auto &u: v) {
            t = visit(u);
            if(t == 0) {
                t = visit(curr);
            }
            else {
                ok = 1;
                f = curr;
                curr = u;
                break;
            }
        }

        if(!ok) return;
    }
}

#ifdef LOCAL
namespace sample_grader {

using std::cout;
using std::cin;
using std::endl;
using std::function;
using std::make_pair;
using std::max;
using std::min;
using std::pair;
using std::swap;
using std::vector;

constexpr int tieLimit = 1000000000;
int N;
int dest;
int curr;
vector<int> T;
vector<pair<int, int>> F;
enum { MARK, LOCATE } phase;

[[noreturn]] void die(const char *const s) {
    cout << s << endl;
    exit(0);
}

void print_vector(vector<int> v)
{
    cout << "{";
    for (size_t i = 0; i < v.size(); ++i) {
        cout <<  v[i];
        if (i + 1 != v.size()) cout << ", ";
    }
    cout << "}";
}

void print_vector(vector<pair<int, int>> v)
{
    cout << "{";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << "{" << v[i].first << ", " << v[i].second << "}";
        if (i + 1 != v.size()) cout << ", ";
    }
    cout << "}";
}

} // namespace sample_grader

int visit(int v) {
    using namespace sample_grader;
    function<void()> die_invalid_call_to_visit = [&]() {
        cout << "visit(" << v << ")" << endl;
        die("Invalid call to visit");
    };
    if (phase == MARK || v < 1 || v > N) die_invalid_call_to_visit();

    bool adjacent = false;
    for (auto e : F) {
        if (e == make_pair(v, curr) or e == make_pair(curr, v)) {
            adjacent = true;
        }
    }
    if (not adjacent) die_invalid_call_to_visit();

    curr = v;
    cout << "visit(" << v << ") returned " << T[v - 1] << endl;
    return T[v - 1];
}

int main() {
    using namespace sample_grader;
    if (!(cin >> N >> dest) or N < 2 or dest < 1 or dest > N) die("Invalid input");

    vector<int> deg(N + 1);

    for(int i = 1; i < N; ++i) {
        int u, v;
        if (!(cin >> u >> v) or min(u, v) < 1 or max(u, v) > N or u == v) {
            die("Invalid input");
        }
        F.emplace_back(u, v);
        ++deg[u]; ++deg[v];
        if(deg[u] > 3 or deg[v] > 3) die("Invalid input");
    }

    vector<bool> visited(N + 1, false);
    function<void(int)> visit = [&](int x) {
        visited[x] = true;
        for (auto [a, b] : F) {
            if (b == x) swap(a, b);
            if (a != x or visited[b]) continue;
            visit(b);
        }
    };
    visit(1);
    if (not all_of(visited.begin() + 1, visited.end(), [](bool b) { return b; })) {
        die("Invalid input");
    }

    phase = MARK;
    T = mark(F, dest);
    cout << "mark(";
    print_vector(F);
    cout << ", " << dest << ") returned ";
    print_vector(T);
    cout << endl;
    if (T.size() != static_cast<size_t>(N)) die("Invalid return value of mark");
    for (int x : T) {
        if (x < 0 or x > tieLimit) die("Invalid return value of mark");
    }

    phase = LOCATE;

    cout << "Enter curr: ";
    if (!(cin >> curr) or curr < 1 or curr > N) die("Invalid input");
    cout << "locate(";
    print_vector(F);
    cout << ", " << curr << ", " << T[curr - 1] << ")" << endl;
    locate(F, curr, T[curr - 1]);

    if (curr == dest) {
        cout << "Correct: at most " << *max_element(T.begin(), T.end()) << " tie(s) per room" << endl;
    } else {
        cout << "Not correct: current position is " << curr << endl;
    }
    return 0;
}
#endif
