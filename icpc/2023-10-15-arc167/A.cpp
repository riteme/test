#include <cstdio>
#include <cstring>

#include <algorithm>
#include <functional>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

int n, m;
int a[NMAX + 10];
i64 b[NMAX + 10];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	sort(a + 1, a + n + 1, std::greater<int>());
	int i = 1;
	for (int j = 1; j <= m; j++) {
		if (i <= n) {
			b[j] += a[i];
			i++;
		}
	}
	for (int j = m; j >= 1; j--) {
		if (i <= n) {
			b[j] += a[i];
			i++;
		}
	}
	i64 ans = 0;
	for (int j = 1; j <= m; j++) {
		ans += b[j] * b[j];
	}
	printf("%lld\n", ans);
	return 0;
}
