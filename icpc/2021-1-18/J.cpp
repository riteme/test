#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 1000;
constexpr int TMAX = 10000;
constexpr int INF = 0x3f3f3f3f;

int n, m, T0, T, L;
vector<int> G[NMAX + 10];
int tm[NMAX + 10][NMAX + 10];
int s[NMAX + 10], d[NMAX + 10], w[NMAX + 10];

void bfs(int *dist, int s) {
	memset(dist + 1, 0x3f, sizeof(int) * n);
	dist[s] = 0;
	queue<int> q;
	q.push(s);
	do {
		int u = q.front();
		q.pop();
		for (int v : G[u]) {
			if (dist[v] > dist[u] + 1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	} while (q.size());
}

void initialize() {
	scanf("%d%d%d", &n, &m, &T0);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	scanf("%d%d", &L, &T);
	T /= T0;
	for (int i = 1; i <= L; i++) {
		scanf("%d", s + i);
	}
	s[L + 1] = 1;
	for (int i = 1; i <= L; i++) {
		scanf("%d%d", d + i, w + i);
	}
}

int f[TMAX + 10];

void chkmax(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	initialize();

	for (int i = 1; i <= n; i++) {
		bfs(tm[i], i);
	}

	for (int i = 0; i <= T; i++) {
		f[i] = -INF;
	}
	f[tm[1][s[1]]] = 0;

	for (int i = 1; i <= L; i++) {
		int t0 = tm[s[i]][s[i + 1]];
		int t1 = tm[s[i]][d[i]] + tm[d[i]][s[i + 1]];

		for (int t = T; t >= 0; t--) {
			int f0 = f[t];
			f[t] = -INF;

			if (t0 >= 0 && t + t0 <= T)
				chkmax(f[t + t0], f0);
			if (t1 >= 0 && t + t1 <= T)
				chkmax(f[t + t1], f0 + w[i]);
		}

		/*
		for (int j = 0; j <= T; j++) {
			printf("%d ", f[j]);
		}
		puts("");
		*/
	}

	int ans = -INF;
	for (int i = 0; i <= T; i++) {
		ans = max(ans, f[i]);
	}

	if (ans < 0)
		puts("Impossible");
	else
		printf("%d\n", ans);

	return 0;
}

