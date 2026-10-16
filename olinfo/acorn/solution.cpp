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

void ask(int x, int y){
    cout << x << " " << y << "\n";
}

int main() {
    // uncomment the two following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int X, Y;
    cin >> X >> Y;

    //Perdi se hai davanti a una configurazione 2-3; 4-5; 6-7... oppure 0-x; 1-x con x>1;
    if( abs(X-Y)==1 && max(X,Y)%2 )
    {
        cout << 'N' << "\n";
        goto move_second;
    }
    cout << 'C' << "\n";


    while(X>1 && Y>1)
    {
        if(X>Y)
        {
            if(Y%2)
                X=Y-1;
            else
                X=Y+1;

        }
        else
        {
            if(X%2)
                Y=X-1;
            else
                Y=X+1;
        }


        ask(X, Y);

        move_second:
        cin >> X >> Y;
    }

    //Vittoria!
    if(X==1 || Y==0)    ask(1, 0);
    else                ask(0, 1);
}

