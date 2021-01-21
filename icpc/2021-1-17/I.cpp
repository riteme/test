#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 2000;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int n, K;
int a[NMAX + 10];
i64 w[NMAX + 10][NMAX + 10];
i64 mx[NMAX + 10];
i64 f[NMAX + 10], g[NMAX + 10];
vector<int> ps[NMAX + 10];

int main() {
	scanf("%d%d", &n, &K);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}

	for (int i = 1; i <= n; i++) {
		int os = 0, as = 0x7fffffff;
		int last = 0xffffffff;
		for (int j = i; j >= 1; j--) {
			os |= a[j];
			as &= a[j];
			int v = os ^ as;
			if (v != last)
				ps[i].push_back(j);
			last = v;
			w[j][i] = v;
		}
	}

	g[0] = -INF;
	for (int i = 1; i <= n; i++) {
		g[i] = w[1][i];
	}

	for (int k = 1; k < K; k++) {
		for (int i = 0; i <= n; i++) {
			f[i] = -INF;
		}

		for (int i = 1; i <= n; i++)
		for (int j : ps[i]) {
			f[i] = max(f[i], g[j - 1] + w[j][i]);
		}

		memcpy(g, f, sizeof(g));
	}

	i64 ans = g[n];
	printf("%lld\n", ans);
	return 0;
}
