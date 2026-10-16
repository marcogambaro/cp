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

#include "light.h"

ll N;
vector<ll> V;

void prepare(){
	N = 1;
	V = {1};
}

ll t = 1;

std::pair<long long, std::vector<long long>> join(long long p){
	ll n = N+p;

	while(V.back() > n) V.pop_back();
	
	set<ll> st;
	for(ll &i: V) st.insert(i);

	ll r = n+1;

	while(r > 1) {
		ll x = r-1;

		auto it = st.upper_bound(x);
		it--;

		while(1) {
			if(*it + (n-x) >= x) {
				if(it == st.begin()) break;
				else it--;
			}
			else {
				it++;
				break;
			}
		}

		auto pt = st.upper_bound(x);

		if(it == pt) {
			// cannot reach x!
			it--;
			ll k = min(*it + p*t, n - 2*(n-x));
			st.insert(k);
			it++;
		}
		else {
			pt--;

			while(pt != it) {
				pt = st.erase(pt);
				pt--;
			}
		}
		
		r = *it;
	}

	N = n;
	V.clear();
	for(auto &i: st) V.push_back(i);
	return {p*t, V};
}

std::pair<long long, std::vector<long long>> leave(long long p){
	ll n = N-p;

	while(V.back() > n) V.pop_back();
	
	set<ll> st;
	for(ll &i: V) st.insert(i);

	ll r = n+1;

	while(r > 1) {
		ll x = r-1;

		auto it = st.upper_bound(x);
		it--;

		while(1) {
			if(*it + (n-x) >= x) {
				if(it == st.begin()) break;
				else it--;
			}
			else {
				it++;
				break;
			}
		}

		auto pt = st.upper_bound(x);

		if(it == pt) {
			// cannot reach x!
			it--;
			ll k = min(*it + p*t, n - 2*(n-x));
			st.insert(k);
			it++;
		}
		else {
			pt--;

			while(pt != it) {
				pt = st.erase(pt);
				pt--;
			}
		}
		
		r = *it;
	}

	N = n;
	V.clear();
	for(auto &i: st) V.push_back(i);
	return {p*t, V};
}

#ifdef LOCAL
namespace {

double maxQuotient = 0.0;
ll NN = 1;
size_t maxFires = 1;
vector<ll> fires = {1};
constexpr int MAX_NNUM_FIRES = 150;

[[noreturn]] void die(string msg)
{
    cout << msg << endl;
    exit(0);
}

void check(ll p, pair<ll, vector<ll>> res) {
    ll t = res.first;
    vector<ll> newFires = res.second;
    maxQuotient = max(maxQuotient, static_cast<double>(t)/abs(static_cast<double>(p)));
    maxFires = max(maxFires, newFires.size());

    cout << (p < 0? "leave" : "join") << "(" << llabs(p) << ") returned " << t << ", {";
    for(size_t i = 0; i < newFires.size(); i++) {
        cout << newFires[i];
        if(i + 1 < newFires.size()) cout << ", ";
    }
    cout << "}" << endl;

    if(t < 0 || t > 5 * static_cast<__int128_t>(llabs(p))) die("Invalid return value");
    for(size_t i = 0; i + 1 < newFires.size(); i++) {
        if(newFires[i] >= newFires[i + 1]) die("Invalid return value");
    }
    if(!newFires.empty() && (newFires[0] <= 0 || newFires.back() > NN)) die("Invalid return value");
    if(newFires.size() > MAX_NNUM_FIRES) die("Too many burning torches");
    if(newFires.empty() || newFires.back() < NN) die("Rightmost torch not on fire");


    size_t i = 0;
    for (ll x : newFires) {
        for (;; ++i) {
            if (i >= fires.size() || fires[i] > x) die("NNot all announced torches have been lit");
            if (fires[i] + t >= x) break;
        }
    }
    fires = newFires;
}

};

int main() {
    int Q;
    if (!(cin >> Q)) die("Invalid input");

    cout << "prepare()" << endl;
    prepare();

    for (int i = 0; i < Q; i++) {
        ll p;
        if (!(cin >> p) || p == 0) die("Invalid input");
        NN += p;
        if (NN <= 0) die("The stage is empty");
        if (p > 0)  check(p, join(p));
        if (p < 0)  check(p, leave(-p));
    }

    cout << "Correct: ratio at most " << maxQuotient << ", at most " << maxFires << " burning torches" << endl;
    return 0;
}
#endif
