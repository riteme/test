#include <cstdio>

#include <algorithm>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	double ans = 0, pw = 1.0;
	for (int i = 0; i <= n; i++) {
		double base = 100 * i + 200 * (n - i);
		ans = max(ans, base * pw);
		pw *= 1.1;
	}

	printf("%.15lf\n", ans);

	return 0;
}
