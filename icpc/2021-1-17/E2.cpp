#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int n;
int atk[6], hp[6];
int cnt[6], sum;
bool vis[6];

void dfs(int i, int d);

void recur(int d) {
	if (d >= n) {
		sum++;
		for (int j = 0; j < n; j++) {
			cnt[j] += hp[j] > 0;
		}
	} else {
		for (int j = 0; j < n; j++) if (!vis[j]) {
			dfs(j, d + 1);
		}
	}
}

void dfs(int i, int d) {
	vis[i] = 1;

	if (hp[i] <= 0) {
		recur(d);
	} else {
		bool found = false;
		for (int j = 0; j < n; j++) if (j != i && hp[j] > 0) {
			found = true;
			hp[i] -= atk[j];
			hp[j] -= atk[i];

			recur(d);

			hp[i] += atk[j];
			hp[j] += atk[i];
		}

		if (!found) {
			recur(d);
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
		dfs(i, 1);
	}

	for (int i = 0; i < n; i++) {
		printf("%.12lf\n", double(cnt[i]) / sum);
	}

	return 0;
}
