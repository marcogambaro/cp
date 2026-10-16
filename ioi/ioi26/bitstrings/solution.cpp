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

#include "bitstrings.h"

int count_duplicated(std::string S) {
    int N = S.size();
    set<string> st;

    for(int s=1; s<N; s++) {
        for(int i=0; i+s+s<=N; i++) {
            if(S.substr(i, s) == S.substr(i+s, s))
                st.insert(S.substr(i, s));
        }
    }

    return st.size();
}

std::string find_weakest() {
    string S;
    auto rec = [&](auto &&rec) {
        if(count_duplicated(S) > 3) return 0;
        if(S.size() == 100) return 1;

        S += '0';
        if(rec(rec)) return 1;
        S.pop_back();
        S += '1';
        if(rec(rec)) return 1;
        S.pop_back();

        return 0;
    };
    rec(rec);

    return S;
}

std::string find_strongest() {
    string S = "0010010001000010000010000001000001000000100000001000000100000001000000001000000010000000010000000011";
    return S;
    vec<set<string>> st(100);

    auto rec = [&](int pos, int fail, int g, auto &&rec) {
        if(fail > 16) return 0;
        if(g > 3)     return 0;
        if(pos == 100)
            return 1;

        for(int i=0; i<2; i++) {
            S += to_string(i);
            st[pos] = st[pos-1];

            for(int s=1; pos-s-s+1 >= 0;s++) {
                string T = S.substr(pos-s+1, s);
                if(T == S.substr(pos-s-s+1, s)) {
                    if(!st[pos-1].count(T)) {
                        st[pos].insert(T);
                    }
                }
            }

            if(st[pos].size() - st[pos-1].size() > 0) {
                if(rec(pos+1, fail, 0, rec)) return 1;
            }
            else {
                if(rec(pos+1, fail+1, g+1, rec)) return 1;
            }

            S.pop_back();
        }
        return 0;
    };
    rec(1, 1, 0, rec);

    cerr << count_duplicated(S) << lf;
    return S;
}

#ifdef LOCAL
namespace {

void run_part1() {
  char tmp[101];
  assert(1 == scanf("%100s", tmp));
  std::string S = tmp;
  fclose(stdin);

  int K = count_duplicated(S);

  printf("%d\n", K);
  fclose(stdout);
}

void run_part2() {
  char tmp[101];
  assert(1 == scanf("%100s", tmp));
  std::string T = tmp;
  fclose(stdin);

  std::string S;
  if (T == "weakest")
    S = find_weakest();
  else
    S = find_strongest();

  printf("%s\n", S.c_str());

  fclose(stdout);
}

} // namespace

int main() {
  int part;
  assert(1 == scanf("%d", &part));
  if (part == 1)
    run_part1();
  else if (part == 2)
    run_part2();

  return 0;
}
#endif
