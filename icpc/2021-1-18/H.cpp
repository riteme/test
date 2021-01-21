#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

constexpr int NMAX = 20;
constexpr int SMAX = 1 << NMAX;

int n, G, sum;
int p[NMAX + 10];
int w[SMAX], pc[SMAX];

int main() {
	scanf("%d%d", &n, &G);
	for (int i = 0; i < n; i++) {
		scanf("%d", p + i);
		sum += p[i];
	}

	int cnt = 0, ming = INT_MAX;
	for (int S = 0; S < (1 << n); S++) {
		int got = 0;
		for (int i = 0; i < n; i++) {
			if ((S >> i) & 1) {
				pc[S]++;
				got += p[i];
			}
		}

		w[S] = 100 * got / sum;
		if (w[S] >= G && pc[S] <= ming) {
			if (ming > pc[S]) {
				ming = pc[S];
				cnt = 0;
			}
			cnt++;
		}
	}

	printf("%d %d\n", ming, cnt);
	for (int S = 0; S < (1 << n); S++)
	if (pc[S] == ming && w[S] >= G) {
		printf("%d ", w[S]);

		int j = 0;
		for (int i = 0; i < n; i++) {
			if ((S >> i) & 1) {
				j++;
				printf(j < ming ? "%d " : "%d\n", i + 1);
			}
		}
	}

	return 0;
}
