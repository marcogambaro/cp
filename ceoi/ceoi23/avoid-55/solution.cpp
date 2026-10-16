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

#include "avoid.h"

std::pair<int, int> solve1() {
	for(int i = 0; i < 10; i++) {
		vec<int> r;
		for(int j = 0; j < 1000; j++)
			if(j & (1 << i) )r.push_back(j+1);
		send(r);
	}
	vec<int> k = wait();
	int ans = 0;
	for(int i = 0; i < 10; i++) {
		if(k[i]) ans += (1 << i);
	}
	return {ans+1,ans+1};
}

std::pair<int, int> solve2() {
	int a = 0, b = 0;

	for(int i = 0; i < 10; i++) {
		vec<int> r;
		for(int j = 0; j < 1000; j++)
			if(j & (1 << i) && (j&a) == a) r.push_back(j+1);
		send(r);
		vec<int> k = wait();
		if(k[0] == 1)
			a += (1 << i);
	}

	a++;

	bool allz = 1;

	for(int i = 0; i < 10; i++) {
		vec<int> r;
		for(int j = 1; j <= 1000; j++)
			if((j & (1 << i)) && j != a && (j & b) == b) r.push_back(j);
		send(r);
		vec<int> k = wait();
		if(k[0] == 1)
			b += (1 << i), allz = 0;
	}

	if(allz == 1) b = a;

	infof("a = %d, b = %d", a, b);
	return {a, b};
}

std::pair<int, int> solve3() {
	int a = 0, b = 0;
	
	for(int i = 0; i < 10; i++) {
		vec<int> v, u;
		for(int j = 1; j < 1001; j++) {
			if(j & (1 << i)) u.push_back(j);
			else v.push_back(j);
		}
		send(v);
		send(u);
	}

	vec<int> k = wait();

	int c = 0, x = 0;
	int db = -1;

	for(int i = 0; i < 10; i++) {
		if(k[i*2] == 1 && k[i*2+1] == 0) {
			// both 0
		}
		else if(k[i*2] == 0 && k[i*2+1] == 1) {
			// both 1
			c += (1 << i);
		}
		else {
			// diverse
			db = i;
			x += (1 << i);
		}
	}

	if(db == -1) return {c, c};

	for(int i = 0; i < 10; i++) {
		vec<int> r;
		for(int j = 1; j < 1001; j++) {
			if(j & (1 << i))
				if(j & (1 << db))
					r.push_back(j);
		}
		send(r);
	}

	k = wait();
	for(int i = 0; i < 10; i++) {
		if(k[i]) a += (1 << i);
	}

	return {a, a^x};
}

std::pair<int, int> scout(int R, int H) {
    if(R == 10 && H == 1)  return solve1();
    if(R == 20 && H == 20) return solve2();
    if(R == 30 && H == 2)  return solve3();
    vec<int> va(5), vb(5);

    for(int i = 0; i < 5; i++) {
        vec<vec<int>> v(4);
        for(int j = 1; j <= 1000; j++) {
            v[(j >> (i*2)) %4].push_back(j);
        }

        for(int j=0; j<4; j++) send(v[j]);
    }

    map<array<int, 3>, int> mp;
    int Q = 20;

    for(int i = 0; i < 5; i++) {
        for(int j = i+1; j < 5; j++) {
            vec<int> vs, vd;

            for(int k = 1; k <= 1000; k++) {
                if( (k >> i*2 &3) == (k >> j*2 &3) ) {
                    vs.push_back(k);
                }
                else if( (k >> i*2 &3) == ((k >> j*2)+1 &3) ) {
                    vd.push_back(k);
                }
            }

            send(vs);
            send(vd);
            mp[{i, j, 0}] = Q++;
            mp[{i, j, 1}] = Q++;
        }
    }

    vec<int> res = wait();
    int a=0, b=0;

    for(int i = 0; i < 5; i++) {
        int e = -1, f = -1;

        for(int j=0; j<4; j++) {
            if(res[i*4+j]) {
                if(e == -1) e = j;
                else f = j;
            }
        }

        if(f == -1) {
            a += e << i*2;
            b += e << i*2;
        }
        else {
            if(a == b) {
                a += e << i*2;
                b += f << i*2;
            }
            else {
                for(int j=0; ;j++) {
                    int ca = a>>j*2 &3;
                    int cb = b>>j*2 &3;

                    if(ca == cb) continue;

                    set<int> st = {ca, cb, e, f};
                    int k = 0;
                    if(st.size() == 4) {
                        ca = ca+3&3;
                        cb = cb+3&3;
                        k = 1;
                    }

                    if(res[mp[{j, i, k}]]) {
                        if(ca == e || cb == f) {
                            a += e << i*2;
                            b += f << i*2;
                        }
                        else {
                            a += f << i*2;
                            b += e << i*2;
                        }
                    }
                    else {
                        if(ca == e || cb == f) {
                            b += e << i*2;
                            a += f << i*2;
                        }
                        else {
                            b += f << i*2;
                            a += e << i*2;
                        }
                    }

                    break;
                }
            }
        }
    }

    return {a,b};
}

#ifdef LOCAL
namespace sample_grader {

using std::cout;
using std::cin;
using std::endl;
using std::set;
using std::swap;
using std::vector;

constexpr int N = 1000;

int R, H;
int r, h;
int a, b;
vector<int> answers;

[[noreturn]] void invalid_input()
{
    cout << "Invalid input" << endl;
    exit(0);
}

[[noreturn]] void wrong_answer(const char *msg)
{
    cout << msg << endl;
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

} // namespace sample_grader


void send(std::vector<int> positions)
{
    using namespace sample_grader;
    cout << "send(";
    print_vector(positions);
    cout << ")" << endl;

    ++r;
    if (r > R) wrong_answer("Out of robots");

    set<int> position_set;
    int curr_answer = 0;
    for (int x : positions) {
        if (x < 1 or x > N or position_set.find(x) != position_set.end()) {
            wrong_answer("Invalid send");
        }
        position_set.insert(x);

        if (x == a or x == b) curr_answer = 1;
    }

    answers.push_back(curr_answer);
}

std::vector<int> wait()
{
    using namespace sample_grader;
    h++;
    cout << "wait()";
    if (h <= H) {
        cout << " returns ";
        print_vector(answers);
    }
    cout << endl;

    if (h > H) wrong_answer("Out of time");

    vector<int> result = answers;
    answers.clear();
    return result;
}


int main()
{
    using namespace sample_grader;
    // for(int i = 1; i <= 1000; i++) {
    //     for(int j = 1 ; j <= 100; j++) {
    //         R = H = 100;
    //         r = 0, h  = 0;
    //         a=i, b=j;
    //         auto [q, w] = scout(R, H);

    //         if( (q != a || w != b) && (q != b || w != a) ) {
    //             cout << "wprong: " << a << " " << b << lf;
    //             return 0;
    //         }
    //     }
    // }

    if (!(cin >> R >> H >> a >> b) || R <= 0 || H <= 0) invalid_input();
    if (a > b) swap(a, b);
    if (a < 1 or b > N) invalid_input();

    auto p = scout(R, H);
    cout << "scout(" << R << ", " << H << ") returned {" << p.first << ", " << p.second << "}" << endl;

    if (p.first > p.second) swap(p.first, p.second);

    if (p.first == a and p.second == b) {
        cout << "Correct: " << r << " robot(s) used, " << h << " hour(s) passed" << endl;
    } else {
        wrong_answer("Wrong answer");
    }
    return 0;
}
#endif
