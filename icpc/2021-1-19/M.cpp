#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 1000;
constexpr int CMAX = NMAX * NMAX;
constexpr int INF = 20000000;

int n, m, cnt, D;
int sx[CMAX + 10], sy[CMAX + 10];
int sz[CMAX + 10];
int seq[CMAX + 10];
char s[NMAX + 10];
int a[NMAX + 10][NMAX + 10];

int dfs(int x, int y, int k) {
	if (a[x][y])
		return 0;
	if (x == 1 || x == n || y == 1 || y == m)
		return -INF;
	
	a[x][y] = k;
	int rax = 1 +
		dfs(x - 1, y, k) +
		dfs(x + 1, y, k) +
		dfs(x, y - 1, k) +
		dfs(x, y + 1, k);
	
	if (rax < -INF)
		rax = -INF;
	
	return rax;
}

void fill(int x, int y, int u, int v) {
	if (a[x][y] != u)
		return;
	a[x][y] = v;
	fill(x - 1, y, u, v);
	fill(x + 1, y, u, v);
	fill(x, y - 1, u, v);
	fill(x, y + 1, u, v);
}

int main() {
	scanf("%d%d%d", &n, &m, &D);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= m; j++) {
			a[i][j] = s[j] == '#' ? -1 : 0;
		}
	}

	for (int x = 2; x < n; x++)
	for (int y = 2; y < m; y++)
	if (!a[x][y]) {
		int s = dfs(x, y, cnt + 1);
		if (s > 0) {
			cnt++;
			sx[cnt] = x;
			sy[cnt] = y;
			sz[cnt] = s;
			//printf("x=%d, y=%d, s=%d\n", x, y, s);
		}
	}

	for (int i = 1; i <= cnt; i++) {
		seq[i] = i;
	}

	sort(seq + 1, seq + cnt + 1, [](int i, int j) {
		return sz[i] < sz[j] ||
			(sz[i] == sz[j] && sx[i] < sx[j]) ||
			(sz[i] == sz[j] && sx[i] == sx[j] && sy[i] < sy[j]);
	});

	int i;
	for (i = 1; i <= cnt; i++) {
		int p = seq[i];
		if (sz[p] >= D)
			break;

		//D -= sz[p];
		fill(sx[p], sy[p], p, -1);
	}
	for ( ; i <= cnt; i++) {
		int p = seq[i];
		fill(sx[p], sy[p], p, 0);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			putchar(a[i][j] == -1 ? '#' : '.');
		}
		puts("");
	}

	return 0;
}
