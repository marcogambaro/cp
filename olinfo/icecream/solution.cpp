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

#include <bits/stdc++.h>
using namespace std;
mt19937 timmy_loves_gambling(73);
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define readv(v) do { for(auto &i: v) cin >> i; } while(0)
#define _ << " " <<
#define lf "\n"
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define fi first
#define se second
template<typename... Args>
using vec = vector<Args...>;
#ifndef LOCAL
bool dbg = 0;
#define infor(str, ...)
#define infof(str, ...)
#else
bool dbg = 1;
#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str "\n", ##__VA_ARGS__); } while(0)
#endif

struct node {
	array<int, 26> adj;
	int x = 0;

};

vector<node> t(2);
int ans = 0;

void add(int v, string &s, int i) {
	t[v].x++;
	if(i == s.size()) return;

	if(t[v].adj[s[i]-'a'] == 0) {
		t[v].adj[s[i]-'a'] = t.size();
		t.emplace_back();
	}

	add(t[v].adj[s[i]-'a'], s, i+1);
}

void query(int v, string &s, int i) {
	t[v].x--;
	if(s.size() == i) {
		ans++;
		for(int j=0; j<26; j++) {
			if(t[v].adj[j] == 0) continue;
			ans--;
		}
		return;
	}

	query(t[v].adj[s[i]-'a'], s, i+1);

	if(t[v].x == 0) {
		ans++;
		for(int j=0; j<26; j++) {
			if(t[v].adj[j] == 0) continue;
			ans--;
		}
	}
}

signed main(){	
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N; cin >> N;
	vec<string> V(N);

	for(auto &s: V) {
		cin >> s;
		add(1, s, 0);
	}
	t[1].x++;

	for(auto &s: V) {
		query(1, s, 0);
		cout << ans << lf;
	}
}

