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

#include "vision.h"

int N, M, K;

int get(int x, int y) {
	return M*x + y;
}

int zero, one;
void get_zero_one() {
	int a = add_not(0);
	zero = add_and({0, a});
	one = add_not(zero);
}

constexpr int Q = 9;

struct numb {
	vec<int> p;
	int S = -1;

	numb() {}

	void init() {
		if(S == -1) S = zero;
	}

	void set(int k) {
		p.resize(Q);
		for(int i=0; i<Q; i++) {
			if(k & (1 << i))
				p[i] = add_and({one});
			else
				p[i] = add_and({zero});
		}
	}

	void add_one(int pw = 1e9) {
		// add one if S is set
		init();
		int carry = S;

		for(int i=0; i<Q; i++) {
			if(pw < (i << 1))  return;

			int nw_carry = add_and({p[i], carry});
			p[i] = add_xor({p[i], carry});
			carry = nw_carry;
		}
	}

	void upd(int f) {
		// if S = 1  ---> add_one()
		// if f = 1  ---> flip S
		add_one();
		S = add_xor({S, f});
	}

	void print() {
		for(int i=0; i<Q; i++)
			add_and({p[i]});
	}
};

void construct_network(int H, int W, int K) {
	N = H;
	M = W;

	get_zero_one();

	numb x, y;
	x.set(0);
	y.set(0);

	for(int i = 0; i < N; i++) {
		vec<int> v;

		for(int j=0; j<M; j++)
			v.push_back(get(i, j));

		x.upd(add_xor(v));
	}

	for(int j = 0; j < M; j++) {
		vec<int> v;

		for(int i=0; i<N; i++)
			v.push_back(get(i, j));

		y.upd(add_xor(v));
	}

	numb nk;
	nk.set(K);

	vec<int> sum(Q);
	int carry = zero;

	for(int i=0; i<Q; i++) {
		sum[i] = add_xor({x.p[i], y.p[i], carry});
		int a = add_and({x.p[i], y.p[i]});
		int b = add_and({x.p[i], carry});
		int c = add_and({y.p[i], carry});
		carry = add_or({a, b, c});
	}

	int rn = zero;
	for(int i=0; i<Q; i++) {
		rn = add_or({rn, add_xor({sum[i], nk.p[i]})});
	}

	cerr << "used " << add_not(rn)-N*M+1 << " instructions!";
}

#ifndef EVAL
static const int MAX_INSTRUCTIONS = 10000;
static const int MAX_INPUTS = 1000000;

static const int _AND = 0;
static const int _OR = 1;
static const int _XOR = 2;
static const int _NOT = 3;

static inline bool increasing(int a, int b, int c) {
	return a <= b && b <= c;
}

[[noreturn]] static inline void error(string message) {
	printf("%s\n", message.c_str());
	exit(0);
}

class InstructionNetwork {

	struct Instruction {
		int type;
		vector<int> input_indexes;

		inline Instruction(int _type, const vector<int>& _input_indexes):
				type(_type), input_indexes(_input_indexes) {
		}

		inline int apply(int a, int b) const {
			switch (type) {
				case _AND:
					return a & b;
				case _OR:
					return a | b;
				case _XOR:
					return a ^ b;
				default:
					return 0;
			}
		}

		inline int compute(const vector<int>& memory_cells) const {
			int r = memory_cells[input_indexes[0]];
			if (type == _NOT)
				return 1 - r;
			for (int j = 1; j < (int)input_indexes.size(); j++)
				r = apply(r, memory_cells[input_indexes[j]]);
			return r;
		}
	};

	int input_size;
	int total_inputs;
	vector<Instruction> instructions;

public:

	inline void init(int _input_size) {
		this->input_size = _input_size;
		this->total_inputs = 0;
		this->instructions.clear();
	}

	inline int add_instruction(int type, const vector<int>& input_indexes) {
		if (input_indexes.size() == 0)
			error("Instruction with no inputs");

		if (instructions.size() + 1 > MAX_INSTRUCTIONS)
			error("Too many instructions");

		if (total_inputs + input_indexes.size() > MAX_INPUTS)
			error("Too many inputs");

		instructions.emplace_back(type, input_indexes);
		total_inputs += input_indexes.size();
		int new_index = input_size + (int)instructions.size() - 1;

		for (int input_index : input_indexes)
			if (!increasing(0, input_index, new_index-1))
				error("Invalid index");

		return new_index;
	}

	inline int compute(vector<int> &memory_cells) const {
		for (auto &instruction : instructions)
			memory_cells.push_back(instruction.compute(memory_cells));
		return memory_cells.back();
	}
};


static InstructionNetwork instructionNetwork;

int main() {
	int H, W, K;
	assert(3 == scanf("%d%d%d", &H, &W, &K));

	FILE *log_file = fopen("log.txt","w");

	instructionNetwork.init(H * W);
	construct_network(H, W, K);

	while (true) {
		int rowA, colA, rowB, colB;
		assert(1 == scanf("%d", &rowA));
		if (rowA == -1)
			break;
		assert(3 == scanf("%d%d%d", &colA, &rowB, &colB));

		if ((!increasing(0, rowA, H-1)) ||
			(!increasing(0, colA, W-1)) ||
			(!increasing(0, rowB, H-1)) ||
			(!increasing(0, colB, W-1)) ||
			(rowA == rowB && colA == colB)) {
			printf("-1\n");
			fprintf(log_file, "-1\n");
			fflush(stdout);
			fflush(log_file);
			continue;
		}

		vector<int> memory_cells;
		for (int row = 0; row < H; row++)
			for (int col = 0; col < W; col++) {
				bool active = (row == rowA && col == colA) || (row == rowB && col == colB);
				memory_cells.push_back(active ? 1 : 0);
			}
		int computation_result = instructionNetwork.compute(memory_cells);

		printf("%d\n", computation_result);
		fflush(stdout);

		for(int i = 0; i < (int)memory_cells.size(); i++)
			fprintf(log_file, (i ? " %d" : "%d"), memory_cells[i]);
		fprintf(log_file, "\n");
		fflush(log_file);
	}
	fclose(stdin);
}

int add_and(vector<int> Ns) {
	return instructionNetwork.add_instruction(_AND, Ns);
}

int add_or(vector<int> Ns) {
	return instructionNetwork.add_instruction(_OR, Ns);
}

int add_xor(vector<int> Ns) {
	return instructionNetwork.add_instruction(_XOR, Ns);
}

int add_not(int N) {
	vector<int> Ns = {N};
	return instructionNetwork.add_instruction(_NOT, Ns);
}
#endif
