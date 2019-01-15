#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 5000
#define DMAX 200
#define MMAX 2000000

struct Edge {
	int u, v, d;
};

static int fa[DMAX + 10][NMAX + 10];
static Edge e[MMAX + 10];
static vector<int> G[DMAX + 10][NMAX + 10];
static bool no[NMAX + 10][NMAX + 10];

struct Node {
	Node() : fa(0), head(0), prev(0), next(0) {}
	int fa, head, prev, next;
};

static bool mark[NMAX + 10];
static bool used[MMAX + 10];
static Node T[DMAX + 10][NMAX + 10];

inline int find(int d, int x) {
	return fa[d][x] ? fa[d][x] = find(d, fa[d][x]) : x;
}

void dfs(int d, int x, int f) {
	mark[x] = true;
	for (int v : G[d][x]) {
		if (v == f) continue;
		T[d][v].next = T[d][x].head;
		if (T[d][x].head) T[d][T[d][x].head].prev = v;
		T[d][x].head = v;
		T[d][v].fa = x;
		dfs(d, v, x);
	}
}

static int d, n, m;
static int pre[MMAX + 10];
static int A[NMAX + 10], B[NMAX + 10], acnt, bcnt;

void scan(int d, int x, int *arr, int &pos) {
	arr[pos++] = x;
	for (int y = T[d][x].head; y; y = T[d][y].next)
		scan(d, y, arr, pos);
}

int main() {
	scanf("%d%d%d", &d, &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k);
		e[i] = {u, v, k};
		int idu = find(k, u), idv = find(k, v);
		if (idu != idv) {
			used[i] = true;
			fa[k][idu] = idv;
			G[k][u].push_back(v);
			G[k][v].push_back(u);
		}
	}

	int om = m;
	for (int i = 1; i <= d; i++) {
		acnt = 0;
		for (int j = 1; j <= n; j++) {
			A[j] = find(i, j);
		}
		sort(A + 1, A + n + 1);
		acnt = unique(A + 1, A + n + 1) - A - 1;
		for (int j = 1; j < acnt; j++) {
			int u = A[j], v = A[j + 1];
			e[++m] = {u, v, i};
			G[i][u].push_back(v);
			G[i][v].push_back(u);
			used[m] = true;
		}

		memset(mark, 0, sizeof(mark));
		for (int j = 1; j <= n; j++) {
			if (!mark[j])
				dfs(i, j, 0);
		}
	}

	for (int i = m; i >= 1; i--) {
		if (!used[i]) continue;
		int d = e[i].d, u = e[i].u, v = e[i].v;
		if (T[d][u].fa == v) swap(u, v);
		if (T[d][v].prev) T[d][T[d][v].prev].next = T[d][v].next;
		if (T[d][v].next) T[d][T[d][v].next].prev = T[d][v].prev;
		if (T[d][u].head == v) T[d][u].head = T[d][v].next;
		acnt = bcnt = T[d][v].fa = /*T[d][v].prev = T[d][v].next =*/ 0;
        while (T[d][u].fa) u = T[d][u].fa;
		scan(d, u, A, acnt);
		scan(d, v, B, bcnt);
		for (int j = 0; j < acnt; j++) for (int k = 0; k < bcnt; k++) {
			if (no[A[j]][B[k]]) continue;
			pre[i]++;
			no[A[j]][B[k]] = no[B[k]][A[j]] = true;
		}
	}

	for (int i = 1; i <= om; i++) {
		pre[i] += pre[i - 1];
		printf("%d\n", pre[i] * 2 + n);
	}

	return 0;
}
