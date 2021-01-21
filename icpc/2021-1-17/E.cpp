#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int n;
int atk[6], hp[6];
double ans[6];
bool vis[6];

void dfs(int i, int d, double p);

void recur(int d, double p) {
	if (d >= n) {
		for (int j = 0; j < n; j++) {
			ans[j] += hp[j] > 0 ? p : 0;
		}
	} else {
		for (int j = 0; j < n; j++) if (!vis[j]) {
			dfs(j, d + 1, p / (n - d));
		}
	}
}

void dfs(int i, int d, double p) {
	vis[i] = 1;

	if (hp[i] <= 0) {
		recur(d, p);
	} else {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            cnt += j != i && hp[j] > 0;
        }

		for (int j = 0; j < n; j++) if (j != i && hp[j] > 0) {
			hp[i] -= atk[j];
			hp[j] -= atk[i];

			recur(d, p / cnt);

			hp[i] += atk[j];
			hp[j] += atk[i];
		}

		if (!cnt) {
			recur(d, p);
		}
	}

	vis[i] = 0;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", atk + i, hp + i);
	}

	for (int i = 0; i < n; i++) {
		dfs(i, 1, 1.0 / n);
	}

	for (int i = 0; i < n; i++) {
		printf("%.12lf\n", ans[i]);
	}

	return 0;
}
