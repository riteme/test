#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 5000;
constexpr int MMAX = 100;

int n, m;
int a[2][MMAX + 10];
bool f[NMAX + 10][2];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", a[0] + i);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", a[1] + i);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i >= a[0][j])
				f[i][0] |= !f[i - a[0][j]][1];
			if (i >= a[1][j])
				f[i][1] |= !f[i - a[1][j]][0];
		}
	}

	if (f[n][0])
		puts("Long Long nb!");
	else
		puts("Mao Mao nb!");
	return 0;
}
