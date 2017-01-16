#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>

#define MAX 5100000

struct Vector {
	int value;
	Vector* next;
	Vector* last;
	Vector() {
		value = 0;
		next = nullptr;
		last = this;
	}
	void push_back(int value) {
		last->next = new Vector();
		last->next->value = value;
		last = last->next;
	}
};

std::vector<int> m[MAX];
std::vector<int> son[MAX];

bool v[MAX];
int dep[MAX];
int p[MAX];
int top[MAX];
int siz[MAX];

int N, M;

void dfs(int x) {
	v[x] = true;
	for (size_t it = 0; it < m[x].size(); it++) {
		if (v[m[x][it]]) continue;
		p[m[x][it]] = x;
		dep[m[x][it]] = dep[x] + 1;
		son[x].push_back(m[x][it]);
		siz[x]++;
		dfs(m[x][it]);
	}
}

void Bulid(int x, int topx) {
	top[x] = topx;

	int MAXSON = 0;
	int MAXSIZE = 0;

	if (siz[x] == 0) return;

	for (size_t it = 0; it < son[x].size(); it++) {
		if (MAXSIZE < siz[son[x][it]]) {
			MAXSON = son[x][it];
			MAXSIZE = siz[son[x][it]];
		}
	}

	Bulid(MAXSON, topx);

	for (size_t it = 0; it<son[x].size(); it++) {
		if (son[x][it] == MAXSON)continue;
		Bulid(son[x][it], son[x][it]);
	}

}

int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			std::swap(u, v);
		u = p[top[u]];
	}

	if (dep[u] > dep[v]) return v;
	return u;
}

int read() {
	int x = 0;
	int f = 1;
	char ch = getchar();
	while (ch<'0' || ch>'9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0'&&ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x*f;
}


void Initalize() {
	N = read();
	M = read();

	for (int i = 1; i < N; i++) {
		int u = read();
		int v = read();
		m[u].push_back(v);
		m[v].push_back(u);
	}

	dfs(1);
	Bulid(1, 1);
}

int main() {
	Initalize();


	for (int i = 1; i <= M; i++) {
		int k = read();
		int u = read();
		for (int j = 1; j < k; j++) {
			int v = read();
			u = LCA(u, v);
		}
		printf("%d\n", u);
	}
}
