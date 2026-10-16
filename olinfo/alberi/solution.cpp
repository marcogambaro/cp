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


void visita(int N, int *PRE, int *POST, int *SIMM) {
	int i=0, j=0, k=0;
	stack<int> st;
	vector<int> vb(N+1);
	
	for(int i=0; i<N; i++) {
		st.push(PRE[i]);
		while(!st.empty() && st.top() == POST[j]) {
			SIMM[k++] = st.top();
			vb[st.top()] = 1;
			st.pop();
			if(!st.empty() && vb[st.top()] == 0) SIMM[k++] = st.top(),  vb[st.top()] = 1, st.pop();
			while(j < N && vb[POST[j]] == 1) j++;
		}
	}
}

#ifndef EVAL
static int N,i ;
static int preordine [MAXN] ;
static int postordine[MAXN] ;
static int simmetrica[MAXN] ;
int main(){
  FILE *fin, *fout;
#ifdef EVAL
  assert(fin = fopen("input.txt", "r"));
  assert(fout = fopen("output.txt", "w"));
#else
  fin = stdin;
  fout = stdout;
#endif
  assert(1==fscanf(fin, "%d", &N));

  for( i = 0 ; i < N ; i++ ) assert( 1 == fscanf(fin,"%d",preordine+i) );
  for( i = 0 ; i < N ; i++ ) assert( 1 == fscanf(fin,"%d",postordine+i) );

  visita(N,preordine,postordine,simmetrica);

  for( i = 0 ; i < N ; i++ ) fprintf(fout,"%d ",simmetrica[i]);
  fprintf(fout,"\n");

  return 0;
}
#endif



