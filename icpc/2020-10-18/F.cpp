#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;
constexpr int LOGN = 18;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
	int v, w;
};

struct Query {
	int u, v, w;
};

int n, m, mcnt;
bool mark[NMAX + 10];
int dep[NMAX + 10], wt[NMAX + 10], seq[NMAX + 10];
int pa[LOGN][NMAX + 10], mi[LOGN][NMAX + 10];
vector<Edge> T[NMAX + 10];
Query minor[NMAX + 10];

void dfs(int x, int p) {
	for (auto &e : T[x])
	if (e.v != p) {
		dep[e.v] = dep[x] + 1;
		pa[0][e.v] = x;
		mi[0][e.v] = e.w;
		dfs(e.v, x);
	}
}

int query(int u, int v) {
	if (dep[u] < dep[v])
		swap(u, v);

	int d = dep[u] - dep[v];
	int rax = INF;
	for (int j = 0; d; d >>= 1, j++)
	if (d & 1) {
		rax = min(rax, mi[j][u]);
		u = pa[j][u];
	}

	if (u == v)
		return rax;
	
	for (int j = LOGN - 1; j >= 0; j--)
	if (pa[j][u] != pa[j][v]) {
		rax = min(rax, min(mi[j][u], mi[j][v]));
		u = pa[j][u];
		v = pa[j][v];
	}

	return min(rax, min(mi[0][u], mi[0][v]));
}

void cover(int x, int c) {
	if (mark[x])
		return;
	mark[x] = true;

	for (auto &e : T[x]) {
		if (e.w > c)
			cover(e.v, c);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int _ = 0; _ < m; _++) {
		int t, u, v, w;
		scanf("%d%d%d%d", &t, &u, &v, &w);

		if (t == 1) {
			T[u].push_back({v, w});
			T[v].push_back({u, w});
		} else
			minor[mcnt++] = {u, v, w};
	}

	memset(mi, INF, sizeof(mi));
	dfs(1, 0);
	for (int j = 1; j < LOGN; j++)
	for (int i = 1; i <= n; i++) {
		pa[j][i] = pa[j - 1][pa[j - 1][i]];
		mi[j][i] = min(mi[j - 1][i], mi[j - 1][pa[j - 1][i]]);
	}

	memset(wt, INF, sizeof(wt));
	for (int i = 0; i < mcnt; i++) {
		auto &z = minor[i];
		if (z.u == z.v)
			continue;

		int e = query(z.u, z.v);
		if (e < z.w) {
			wt[z.u] = min(wt[z.u], e);
			wt[z.v] = min(wt[z.v], e);
		}
	}

	for (int i = 1; i <= n; i++) {
		seq[i] = i;
	}
	sort(seq + 1, seq + n + 1, [](int i, int j) {
		return wt[i] < wt[j];
	});

	for (int i = 1; i <= n; i++) {
		int u = seq[i];
		if (wt[u] < INF)
			cover(u, wt[u]);
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		cnt += !mark[i];
	}

	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++) {
		if (!mark[i])
			printf("%d ", i);
	}
	puts("");

	return 0;
}
