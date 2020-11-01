#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 2000;
constexpr int INF = 0x3f3f3f3f;

int n, m;
char s[NMAX + 10], t[NMAX + 10];
int f[NMAX + 10][NMAX + 10][2];

void chkmax(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	while (scanf("%s%s", s + 1, t + 1) != EOF) {
		n = strlen(s + 1);
		m = strlen(t + 1);
		for (int i = 1; i <= n + 1; i++)
		for (int j = 1; j <= m + 1; j++) {
			f[i][j][0] = f[i][j][1] = -INF;
		}

		f[1][1][0] = 0;
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			chkmax(f[i + 1][j][0], f[i][j][0]);
			chkmax(f[i + 1][j][1], f[i][j][1]);
			chkmax(f[i][j + 1][0], f[i][j][0]);
			chkmax(f[i][j + 1][1], f[i][j][1]);

			if (s[i] <= t[j])
				chkmax(f[i + 1][j + 1][s[i] < t[j]], f[i][j][0] + 2);
			chkmax(f[i + 1][j + 1][1], f[i][j][1] + 2);
		}

		int ans = 0;
		for (int i = 1; i <= n + 1; i++)
		for (int j = 1; j <= m + 1; j++) {
			chkmax(ans, f[i][j][0] + m + 1 - j);
			chkmax(ans, f[i][j][1] + n + 1 - i + m + 1 - j);
		}
		printf("%d\n", ans);
	}

	return 0;
}
