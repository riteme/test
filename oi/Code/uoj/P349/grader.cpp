// RTS grader

#include "rts.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static const int MAXN = 300005;

static void wrong(const char *msg) {
	printf("%s\n", msg);
	exit(0);
}

static void wrong(const char *msg, int x) {
	printf(msg, x);
	printf("\n");
	exit(0);
}

static int n, T, dataType;

struct Edge {
	Edge *next;
	int to;
};

static Edge *firstEdge[MAXN], edges[MAXN * 2], *lastEdge = edges;

static void addEdge(int u, int v) {
	*(++lastEdge) = (Edge){firstEdge[u], v};
	firstEdge[u] = lastEdge;
}

static int fa[MAXN];
static int dTime[MAXN], fTime[MAXN];
static int dfsSeq[MAXN];

static int *childArrStart[MAXN];
static int childArr[MAXN];

static void dfs() {
	static int stack[MAXN];
	int top = 1;
	int nowTime = 0;
	stack[1] = 1;
	while (top) {
		int u = stack[top];
		if (dTime[u]) {
			fTime[u] = nowTime;
			--top;
			continue;
		}
		dTime[u] = ++nowTime;
		dfsSeq[nowTime] = u;
		int lastTop = top;
		for (Edge *e = firstEdge[u]; e; e = e->next) {
			int v = e->to;
			if (v == fa[u]) continue;
			fa[v] = u;
			stack[++top] = v;
		}
		for (int i = lastTop + 1, j = top; i < j; i++, j--) {
			int tmp = stack[i];
			stack[i] = stack[j];
			stack[j] = tmp;
		}
	}
}

static bool discovered[MAXN];

static void init() {
	scanf("%d%d%d", &n, &T, &dataType);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	fa[1] = 0;
	dfs();
	int *childArrPointer = childArr;
	for (int i = 1; i <= n; i++) {
		childArrStart[i] = childArrPointer;
		for (Edge *e = firstEdge[i]; e; e = e->next) {
			int j = e->to;
			if (j == fa[i]) continue;
			*(childArrPointer++) = dTime[j];
		}
	}
	childArrStart[n + 1] = childArrPointer;
	memset(discovered, 0, sizeof(discovered));
	discovered[1] = true;
}

static int cntExploreCalls = 0;

int explore(int x, int y) {
	if (++cntExploreCalls > T) {
		wrong("explore: too many calls");
	}
	if (x < 1 || x > n) {
		wrong("explore: argument x (%d) not in [1, n]", x);
	}
	if (y < 1 || y > n) {
		wrong("explore: argument y (%d) not in [1, n]", y);
	}
	if (x == y) {
		wrong("explore: argument x = y = %d", x);
	}
	if (!discovered[x]) {
		wrong("explore: node x (%d) not discovered", x);
	}
	int z = fa[x];
	if (dTime[x] < dTime[y] && fTime[x] >= fTime[y]) {
		int *A = childArrStart[x];
		int N = childArrStart[x + 1] - A;
		int val = dTime[y];
		while (N > 1) {
			int mid = N >> 1;
			if (val < A[mid]) {
				N = mid;
			} else {
				A += mid;
				N -= mid;
			}
		}
		z = dfsSeq[A[0]];
	}
	discovered[z] = true;
	return z;
}

static void check() {
	for (int i = 1; i <= n; i++) {
		if (!discovered[i]) {
			wrong("node %d not discovered after the game", i);
		}
	}
	printf("Correct\n");
	#ifdef DEBUG
	printf("# of explore calls = %d\n", cntExploreCalls);
	#endif
}

int main() {
	init();
	play(n, T, dataType);
	check();
}
