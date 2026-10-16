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

// Lamerated. I did not know it was lamerated when I wrote it.
constexpr ll  STOP = 1e16;

struct Event
{
	int l, r, s, e;
	bool operator<(Event o) {
		return s<o.s;
	}
};

bool cmpe(Event a, Event b) {
	return a.e < b.e;
}

int n, k, m;
int tempo;
vector<Event> events;
map<int, ll> mp; //qui simulo la strada. Le quantità maggiori di STOP indicano che lì sta piovendo

void die(){
	cout << -1;
	exit(0);
}

void first_rains(vector<Event>& s0)
{
	//le prime pioggie non possono essere schivate
	sort(s0.begin(), s0.end(), cmpe);
	for(Event event: s0)
	{
		int l = event.l;
		int r = event.r;
		int e = event.e;

		if(l<=k && k<=r) 	die();

		mp[l] = STOP+e;
		mp[r] = STOP+e;
	}
}

void get_events() {
	events.reserve(m);
	vector<Event> s0;
	for(int i=0; i<m; i++)
	{
		int a, b, c, d; cin >> a >> b >> c >> d;
		if(c == 0) s0.push_back({a, b, c, d});
		else       events.push_back({a, b, c, d});
	}
	sort(events.begin(), events.end());

	first_rains(s0);
}

map<int, ll>::iterator get_low(int x) //ritorna il valore della prima casella accettabile sotto x (incluso)
{
	map<int, ll>::iterator ans = mp.upper_bound(x), it;
	ans--;

	while(ans->second < STOP + tempo-1 && ans->second >= STOP) //devo rimuovere questi "Muri"
	{
		ans = mp.erase(ans);
		ans--;
	}

	it = ans;
	if(it->second < STOP)
		while(true)
		{
			it--;
			if(it->second >= STOP + tempo-1)	break;
			if(/*it->second < STOP + tempo-1 && */ it->second >= STOP)
			{
				it = mp.erase(it);
			}
			else if(it->second + (ans->first - it->first) <= ans->second)
			{
				//mp.erase(ans);
				ans = it;
			}
		}

	return ans;
}

map<int, ll>::iterator get_up(int x) //ritorna il valore della prima casella accettabile sopra x (incluso)
{
	map<int, ll>::iterator ans = mp.lower_bound(x), it;

	while(ans->second < STOP + tempo-1 && ans->second >= STOP) //devo rimuovere questi "Muri"
	{
		ans = mp.erase(ans);
	}

	it = ans;
	if(it->second < STOP)
		while(true)
		{
			it++;
			if(it->second >= STOP + tempo-1)	break;
			if(/*it->second < STOP + tempo-1 && */ it->second >= STOP)
			{
				it = mp.erase(it);
				it--;
			}
			else if(it->second + (it->first - ans-> first) <= ans->second)
			{
				//mp.erase(ans);
				ans = it;
			}
		}

	return ans;
}

void rain(int l, int r, int end) //spazzola via tutto ciò in [l, r]
{
	map<int, ll>::iterator it = mp.lower_bound(l);
	if(it -> first != l || it->second < STOP + end)
		mp[l] = STOP + end;


	map<int, ll>::iterator it2 = mp.upper_bound(r);
	//cancella ciò che sta in mezzo
	while(it != it2)
	{
		if(it->second < STOP + end ) //ocho
			it = mp.erase(it);
		else
			it++;
	}

	it2--;
	if(it2 -> first != r || it2->second < STOP + end)
		mp[r] = STOP + end;
}

int main()
{
	cin >> n >> k >> m;
	get_events();
	mp[-1] = STOP + 1e9 +5;
	mp[n] = STOP +1e9 + 5;
	mp[k] = 0;

	for(Event event: events)
	{
		int l = event.l - 1;
		int r = event.r + 1;
		tempo = event.s;

		//se necessario, mi sposto nell'estremo sinistro
		auto low = get_low(l), high = get_up(l);
		if(high->second + (high->first - l) < low->second + (l - low->first) && high->second < STOP)
			mp[l] = high->second + (high->first - l);

		//se necessario, mi sposto nell'estremo destro
		low = get_low(r), high = get_up(r);
		if(low->second + (r - low->first) < high->second + (high->first - r) && low->second < STOP)
			mp[r] = low->second + (r - low->first);

		rain(l+1, r-1, event.e);
	}

	ll ans = LLONG_MAX;
	for(auto pp: mp) ans = min(ans, pp.second);

	if(ans >= STOP) cout << -1;
	else			cout << ans;
}

