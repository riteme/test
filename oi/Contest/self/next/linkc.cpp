#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#define MAX 1600000

int N, M;

class TreeArray {
private:
	int arr[MAX];
	int lowbit(int x) {
		return x&(-x);
	}
public:
	void Add(int x, int value) {
		if (x == 0) return;
		for (int i = x; i <= N; i += lowbit(i))
			arr[i] += value;
	}
	int  Query(int x) {
		if (x == 0) return 0;
		int ans = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			ans += arr[i];
		return ans;
	}
};

TreeArray tarr;

struct Operator {
	int kind;
	int x, q;
	int id;
	Operator(int _kind, int _x, int _q, int _id) {
		kind = _kind;
		x = _x;
		q = _q;
		id = _id;
	}
};

struct T {
	int to, id;
	T(int _to, int _id) {
		to = _to;
		id = _id;
	}
};

std::vector<T> m[MAX];
std::vector<Operator> version_op[MAX];
int ans[MAX];
bool Is[MAX];

int now_version = 1;

void dfs(int x) {
	int now_point = 0;
	for (size_t i = 0; i < version_op[x].size(); i++) {
		Operator op = version_op[x][i];
		while (now_point < m[x].size() && m[x][now_point].id <= op.id) {
			dfs(m[x][now_point].to);
			now_point++;
		}
		if (op.kind == 1) {
			tarr.Add(op.x, op.q);
		}
		else {
			ans[op.id] = tarr.Query(op.q) - tarr.Query(op.x - 1);
			Is[op.id] = true;
		}
	}
	for (size_t i = now_point; i < m[x].size(); i++)
		dfs(m[x][i].to);
	for (size_t i = 0; i < version_op[x].size(); i++) {
		Operator op = version_op[x][i];
		if (op.kind == 1) {
			tarr.Add(op.x, -op.q);
		}
	}
}

void Initalize() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++) {
		char kind[10];
		scanf("%s", kind);
		switch (kind[0])
		{
		case 'A': {
			int version, p, x;
			scanf("%d %d %d", &version, &p, &x);
			version_op[version].push_back(Operator(1, p, x, i));
			break;
		}
		case 'Q': {
			int version, l, r;
			scanf("%d %d %d", &version, &l, &r);
			version_op[version].push_back(Operator(2, l, r, i));
			break;
		}
		case 'C': {
			int version;
			scanf("%d", &version);
			now_version++;
			m[version].push_back(T(now_version, i));
			break;
		}
		default:
			break;
		}
	}
}

int main() {
	Initalize();
	dfs(1);
	for (int i = 1; i <= M; i++) {
		if (Is[i]) printf("%d\n", ans[i]);
	}
}
