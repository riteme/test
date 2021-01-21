#include <cstdio>
#include <cstring>

constexpr int PMAX = 1000000;

int P;
int f[PMAX + 10];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &P);
		if (P == 2) {
			puts("1");
			continue;
		}

		f[1] = 1;

		int Q = P / 2;
		double s = 1;
		for (int i = 2; i <= Q; i++) {
			f[i] = f[P % i] + 1;
			s += f[i];
		}
		double ans = (s * 2 + Q) / (P - 1);
		printf("%.12lf\n", ans);
	}

	return 0;
}
