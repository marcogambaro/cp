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

vector<vector<int>> G;
vector<int> dist0, distn;
queue<int> q;
int dist;

void calcola(int n)
{
    q.pop();

    if(n == -1)
    {
        if(q.front() == -1) return;

        q.push(-1);
        dist++;
        return;
    }

    if(dist0[n] != -1) return;
    dist0[n] = dist;

    for(int n2: G[n])
        q.push(n2);
}

void calcola2(int n)
{
    q.pop();

    if(n == -1)
    {
        if(q.front() == -1) return;

        q.push(-1);
        dist++;
        return;
    }

    if(distn[n] != -1) return;
    distn[n] = dist;

    for(int n2: G[n])
        q.push(n2);
}

/////////////////////////////////////////////////////
struct dt{
    int a, b, i;
};

bool cmp(dt q, dt w){
    return q.a < w.a;
}

bool cmp1(dt q, dt w){
    return q.b > w.b;
}


vector<dt> va, vb;
long long ans;
vector <ll> t;


void sum(int p)
{
    while(p)
    {
        ans += t[p];
        p -= p&-p;
    }
}

void add(int p)
{
    while(p<t.size())
    {
        t[p] ++;
        p += p&-p;
    }
}

void get_v(int n)
{
    va.resize(n);
    vb.resize(n);
    t.resize(n+4);

    for(int i=0; i<n; i++)
    {
        va[i] = {dist0[i], distn[i], i};
        vb[i] = {dist0[i], distn[i], i};
    }

    sort(va.begin(), va.end(), cmp);
    sort(vb.begin(), vb.end(), cmp1);
}

void process(int n, int m)
{
    int c = 1;
    int pb = 0;

    for(dt DT: va)
    {
        int a = DT.a;
        int b = DT.b;
        int i = DT.i;

        //calcolo quanti b1 ci sono per cui a+b >= dist-1

        while(a + vb[pb].b >= dist-1 && pb<=n-1)
        {
            add( t.size()-1-vb[pb].a );

            pb++;
        }

        sum( min(t.size()-1-dist+1+b, t.size()-1) );

    }
    //cout << "\n" << ans << "\n";

    cout << (ans-n)/2 - m;
}


int main()
{
    int n, m; cin >> n >> m;
    G.resize(n);
    dist0.resize(n, -1);
    distn.resize(n, -1);

    for(int i=0; i<m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    //calcolo delle distanze

    q.push(0);
    q.push(-1);
    while(!q.empty())
    {
        calcola(q.front());
    }

    dist = 0;
    q.push(n-1);
    q.push(-1);
    while(!q.empty())
    {
        calcola2(q.front());
    }

    dist = dist0[n-1]; // =distn[0]

    get_v(n);

    process(n, m);
}

