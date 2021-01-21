#include <cstdio>
#include <algorithm>

using namespace std;

int c[100];

int main() {
	for (int i = 0; i < 14; i++) {
		int v;
		scanf("%d", &v);
		c[v]++;
	}

	int ans = 1000000;
	for (int i = 1; i <= 13; i++) {
		int cnt = 0;
		for (int j = 1; j <= 34; j++) {
			int t = 0;
			if (j <= 13)
				t = 1;
			if (j == i)
				t = 2;
			cnt += abs(c[j] - t);
		}
		ans = min(ans, cnt / 2);
	}

	printf("%d\n", ans);
	return 0;
}
