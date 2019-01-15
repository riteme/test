#pragma GCC optimize("O3")
//#define NDEBUG

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long u64;

#define NMAX 50
#define T 22
#define SMAX (1 << T)
#define F 1
#define E 2
#define UNK 0

static int N, M, n, m, fri;
static int G[NMAX][NMAX];
static int A[NMAX], B[NMAX];
static u64 R[NMAX];

void initialize() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		G[u][v] = G[v][u] = t + 1;
	}

	for (int v = 2; v <= N; v++) {
		if (G[1][v] == F) fri++;
	}

	static int dist[NMAX];
	queue<int> q;
	q.push(1);
	dist[1] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v = 1; v <= N; v++) {
			if (!G[u][v] || dist[v]) continue;
			dist[v] = dist[u] + 1;
			q.push(v);
		}
	}

	for (int i = 1; i <= N; i++) {
		if (dist[i] == 2) A[n++] = i;
		else if (dist[i] == 3) B[m++] = i;
	}

	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
		if (G[A[i]][B[j]]) R[i] |= 1LL << j;
}

#define has(S, i) ((S >> i) & 1)

inline int e(int i, int j) {
	return G[1][A[i]] == G[A[i]][B[j]] ? F : E;
}

static int f[SMAX];

void work1() {
	static struct {
		int s = 0, i = 0;
	} g[SMAX];
	for (int i = 1; i < (1 << m); i++) f[i] = -1;
	for (int s = 0; s < (1 << m); s++) {
		if (f[s] < 0) continue;
		for (int i = 0; i < n; i++) {
			u64 re = R[i] & (~u64(s));
			if (!re) continue;
			int cnt = 0;
			for (int j = 0; j < m; j++) {
				if (!has(re, j)) continue;
				cnt += e(i, j) == F;
			}
			int t = s | re;
			if (f[t] < f[s] + cnt) {
				f[t] = f[s] + cnt;
				g[t] = {s, i};
			}
		}
	}

	int x = 0;
	for (int i = 1; i < (1 << m); i++)
		if (f[i] > f[x]) x = i;
	static bool mark[NMAX];
	assert(f[x] >= 0);
	printf("%.15lf\n", 1.0 * (fri + f[x]) / (N - 1));
	stack<int> stk;
	while (x) {
		if (!mark[g[x].i]) stk.push(A[g[x].i]);
		mark[g[x].i] = true;
		x = g[x].s;
	}
	while (!stk.empty()) {
		printf("%d ", stk.top());
		stk.pop();
	}
	for (int i = 0; i < n; i++)
		if (!mark[i]) printf("%d ", A[i]);
}

void work2() {
	static int g[SMAX];
	for (int i = 1; i < (1 << n); i++) f[i] = -1;
	for (int s = 0; s < (1 << n); s++) {
		if (f[s] < 0) continue;
		u64 used = 0;
		for (int i = 0; i < n; i++) if (has(s, i)) used |= R[i];
		for (int i = 0; i < n; i++) {
			if (has(s, i)) continue;
			u64 re = R[i] & (~u64(used));
            if (!re) continue;
			int cnt = 0;
			for (int j = 0; j < m; j++) {
				if (!has(re, j)) continue;
				cnt += e(i, j) == F;
			}

			int t = s | (1 << i);
			if (f[t] < f[s] + cnt) {
				f[t] = f[s] + cnt;
				g[t] = i;
            }
		}
	}

	int x = 0;
	for (int i = 1; i < (1 << n); i++)
		if (f[i] > f[x]) x = i;
	printf("%.15lf\n", 1.0 * (fri + f[x]) / (N - 1));
	stack<int> stk;
	static bool mark[NMAX];
	while (x) {
		if (!mark[g[x]]) stk.push(A[g[x]]);
		mark[g[x]] = true;
		x ^= 1 << g[x];
	}
	while (!stk.empty()) {
		printf("%d ", stk.top());
		stk.pop();
	}
	for (int i = 0; i < n; i++)
		if (!mark[i]) printf("%d ", A[i]);
}

int main() {
	initialize();
	if (n <= T) work2();
	else work1();
	return 0;
}
