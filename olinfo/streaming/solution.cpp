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


long long bfs(int N, long long K, std::vector<int> P, std::vector<int> F) {
    vec<int> id(N);
    iota(all(id), 0);

    sort(all(id), [&](int i, int j){return P[i] > P[j];});

    ll ans = 0;
    priority_queue<int> pq;
    ll fee = 0;

    for(int i : id) {
        pq.push(F[i]);
        fee += F[i];

        while(pq.size() && (pq.top() > P[i] || fee > K)) {
            fee -= pq.top();
            pq.pop();
        }

        ans = max(ans, (ll)P[i]*(ll)pq.size() - fee);
    }

    return ans;
}

#ifdef LOCAL
int main() {
	int N;
	long long K;
	std::cin >> N >> K;

	std::vector<int> P(N), F(N);
	for (int& i : P)
		std::cin >> i;
	for (int& i : F)
		std::cin >> i;

	std::cout << bfs(N,K,P,F) << "\n";
	return 0;
}
#endif

