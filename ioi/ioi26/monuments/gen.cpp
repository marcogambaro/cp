#include <bits/stdc++.h>
using namespace std;
mt19937 rng(7334);

int main() {
    int ciao = 1000000;
    while(ciao--) {
        int N = 10;
        ofstream cout(".in");

        vector<int> V(N), P;

        int t=0;
        for(int &i: V) {
            int x = abs((int)rng())%(int)20;
            i = -10 + x;
            if(1) P.push_back(t);
            t++;
        }
        sort(V.begin(), V.end());

        cout << N << " " << P.size() << endl;
        for(int i: V) cout << i << " ";
        cout << endl;
        for(int i: P) cout << i << " ";
        cout << endl;

        system("./quadratic <.in >out-quad");
        system("./solution <.in >out-sol");

        ifstream in1("out-quad");
        ifstream in2("out-sol");

        long long a=-2, b=-3;
        in1 >> a;
        in2 >> b;
        if(a != b) exit(1);
    }
    cout << "YAY";
}