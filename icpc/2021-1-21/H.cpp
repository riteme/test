#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 500000;
constexpr int OFF = NMAX + 5;

using iter = set<int>::iterator;

int n, q;
int a[NMAX + 10], b[NMAX + 10];
int idx[NMAX + 10], rev[NMAX + 10];
int L[NMAX + 10], R[NMAX + 10], tm;
int pa[NMAX + 10];
vector<int> G[NMAX + 10];
set<int> pos[2 * NMAX + 100];
iter null = pos[0].end();

int iget(int v, int x) {
	int l = L[x];
	int r = R[x];
	v += OFF;

	auto it = pos[v].lower_bound(l);
	if (it == pos[v].end() || *it > r)
		return 0;

	return rev[*it];
}

void idel(int v, int x) {
	x = idx[x];
	v += OFF;
	auto &s = pos[v];
	auto it = s.find(x);
	s.erase(it);
}

void iadd(int v, int x) {
	x = idx[x];
	v += OFF;
	auto &s = pos[v];
	s.insert(x);
}

void store(int x, int v) {
	if (a[x])
		idel(a[x], x);

	a[x] = v - b[x];

	if (a[x])
		iadd(a[x], x);
}

void scan(int x, int p) {
	if (!a[x])
		return;
	
	int v = a[x];
	store(x, b[x]);

	iter it;
	while (1) {
		int u = iget(v, x);
		if (!u)
			break;
		if (u == p)
			continue;

		scan(u, x);
	}

	int u = pa[x];
	if (u && u != p && a[u] == v)
		scan(u, x);
}

void bfs(int s) {
	queue<int> q;
	q.push(s);
	idx[s] = ++tm;
	do {
		int u = q.front();
		q.pop();
		for (int v : G[u]) if (!idx[v]) {
			idx[v] = ++tm;
			q.push(v);
		}
	} while (q.size());

	for (int i = 1; i <= n; i++) {
		rev[idx[i]] = i;
	}
}

void dfs(int x) {
	L[x] = INT_MAX;
	R[x] = 0;
	for (int v : G[x]) if (v != pa[x]) {
		pa[v] = x;
		L[x] = min(L[x], idx[v]);
		R[x] = max(R[x], idx[v]);
		dfs(v);
	}
}

void initialize() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", b + i);
	}

	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	bfs(1);
	dfs(1);

	for (int i = 1; i <= n; i++) {
		a[i] -= b[i];
		if (a[i])
			iadd(a[i], i);
	}
}

int main() {
	initialize();

	while (q--) {
		int t, x;
		scanf("%d%d", &t, &x);
		if (t == 1) {
			int v;
			scanf("%d", &v);
			store(x, v);
		} else if (t == 2) {
			int v = a[x] + b[x];
			printf("%d\n", v);
		} else {
			scan(x, 0);
		}
	}

	return 0;
}
