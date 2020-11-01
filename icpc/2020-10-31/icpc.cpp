#include <cstdio>
#include <cstring>
#include <cassert>

#include <unordered_set>
#include <algorithm>

using namespace std;

constexpr int NMAX = 2000000;

using i64 = long long;

i64 idx(int x, int y) {
	return (x << 16) | y;
}

i64 idxe(int x1, int y1, int x2, int y2) {
	i64 v1 = idx(x1, y1);
	i64 v2 = idx(x2, y2);
	if (v1 > v2)
		swap(v1, v2);
	return (v1 << 32) | v2;
}

int n, m, K, cnt;
char s[NMAX + 10];
int vis[2000][2000];

int dist(int x, int y) {
	return abs(n - x) + abs(m - y);
}

bool solve(int x, int y, int d) {
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++) {
		vis[i][j] = 0;
	}
	for (int i = 0; i <= n + 1; i++) {
		vis[i][0] = vis[i][m + 1] = -1;
	}
	for (int i = 0; i <= m + 1; i++) {
		vis[0][i] = vis[n + 1][i] = -1;
	}
	vis[1][1] = -1;
	if (y > 1) {
		if (n % 2 == 0)
			vis[n][1] = -1;
		if (m % 2 == 1)
			vis[1][m] = -1;
	} else {
		if (n % 2 == 1)
			vis[n][1] = -1;
		if (m % 2 == 0)
			vis[1][m] = -1;
	}

	int l = 1;
	const char *dc = "NESW";
	int dx[] = {-1, 0, 1, 0};
	int dy[] = {0, 1, 0, -1};

	while (l <= K && (x != n || y != m)) {
		assert(cnt <= NMAX + 3);
		//printf("(%d, %d), d=%d\n", x, y, d);
		if (x == 1 || x == n || y == 1 || y == m)
			vis[x][y] = -1;
		else
			vis[x][y] = 1;

		if (l + dist(x, y) == K) {
			if (!vis[x + 1][y]) {
				x++;
				s[cnt++] = 'S';
			} else {
				y++;
				s[cnt++] = 'E';
			}
			l++;
		} else {
			int tx = x + dx[d], ty = y + dy[d];
			if (vis[tx][ty] == -1) {
				if (dx[d] != 0)
					d = d == 2 ? 0 : 2;
				else
					d = d == 1 ? 3 : 1;
			}

			x += dx[d];
			y += dy[d];
			s[cnt++] = dc[d];
			switch (d) {
				case 0: d = 1; break;
				case 1: d = 0; break;
				case 2: d = 3; break;
				case 3: d = 2; break;
			}

			l++;
		}
	}

	s[cnt] = 0;
	return l == K;
}

bool simulate(int l) {
	unordered_set<i64> mp;

	int x = 1, y = 1;
	for (int i = 0; i < l; i++) {
		int x0 = x, y0 = y;
		switch (s[i]) {
			case 'N': x--; break;
			case 'E': y++; break;
			case 'S': x++; break;
			case 'W': y--; break;
		}

		i64 key = idxe(x0, y0, x, y);
		assert(!mp.count(key));
		mp.insert(key);
		assert(1 <= x && x <= n);
		assert(1 <= y && y <= m);
	}
	assert(s[l] == 0);
	assert(x == n && y == m);
	return true;
}

bool _main(int _n, int _m, int _K) {
	n = _n;
	m = _m;
	K = _K;

	int x = 1, y = 2;
	cnt = 0;
	s[cnt++] = 'E';
	if (solve(1, 2, 2)) {
		//puts("YES");
		//puts(s);
		return true;
	} else {
		cnt = 0;
		s[cnt++] = 'S';
		if (solve(2, 1, 1)) {
			//puts("YES");
			//puts(s);
			return true;
		} else {
			//puts("NO");
			return false;
		}
	}
}

int main() {
	for (int i = 1000; i <= 1000; i++)
	for (int j = 1000; j <= 1000; j++) {
		int L = i * j * 2 + i + j - (i / 2) * 2 - (j / 2) * 2;
		if (i % 2 == 1 && j % 2 == 1)
			L -= 2;
		//for (int l = i + j; ; l += 2) {
		for (int l = L; l >= i + j; l -= 2) {
			printf("i=%d, j=%d, l=%d\n", i, j, l);
			if (!_main(i + 1, j + 1, l)) {
				printf("# i=%d, j=%d, end at l=%d (L=%d)\n", i, j, l, L);
				assert(l == L + 2);
				break;
			} else {
				assert(simulate(l));
			}
		}
	}

	/*
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &K);
		n++; m++;
		_main(n, m, K);
	}
	*/
	return 0;
}
