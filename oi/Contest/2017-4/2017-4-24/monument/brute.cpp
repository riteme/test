#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define N 2000
#define eps 1e-9
#define inf 1e11

using namespace std;

struct point {
	double p, v;
	bool operator < (const point &b) const {
		return p < b.p;
	}
}a[N + 5];

double count(int i, int j) {
	double t;
	if (abs(a[i].p - a[j].p) < eps)
		t = 0;
	else
		if (a[j].v == a[i].v || j == 0 || a[i].v - a[j].v >= -eps)
			t = inf;
		else
			t = (a[i].p - a[j].p) / (a[j].v - a[i].v);
	return t;
}

double dp[N + 5][N + 5], ans = 0;
int n, k;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i ++)
		scanf("%lf%lf", &a[i].p, &a[i].v);
	sort(a + 1, a + 1 + n);
	dp[0][0] = inf, dp[1][0] = inf;
	for (int i = 0; i <= k; i ++)
		for (int j = i; j <= k; j ++)
			dp[i][j] = inf;
	for (int i = 2; i <= n; i ++)
		dp[i][0] = min(dp[i - 1][0], count(i, i - 1));
	for (int i = 2; i <= n; i ++) {
		for (int j = max(0, i - k - 1); j < i; j ++) {
			double t = count(i, j);
			for (int l = 0; l <= k - (i - j - 1); l ++)
				dp[i][l + i - j - 1] = max(dp[i][l + i - j - 1], min(dp[j][l], t));
		}
	}
	for (int i = 0; i <= k; i ++)
		ans = max(dp[n - k + i][i], ans);
	if (abs(ans - inf) < eps)
		puts("Forever");
	else
		printf("%.8lf\n", ans);
	return 0;
}
