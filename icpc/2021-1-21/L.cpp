#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;
constexpr int MOD = 1000000007;

int n;
vector<int> f[NMAX + 10];

void add(int &a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--;
		y--;
		if (f[x].size() < y + 1)
			f[x].resize(y + 1);
	}

	for (int &v : f[0]) {
		v = 1;
	}

	int ans = f[1].size() < f[0].size() ? 1 : 0;
	for (int i = 1; i <= NMAX; i++) {
		for (int j = 0; j < f[i].size(); j++) {
			add(f[i][j], f[i - 1][j]);
			if (j)
				add(f[i][j], f[i][j - 1]);
		}

		if (f[i].size() && f[i + 1].size() < f[i].size())
			add(ans, f[i].back());
	}

	printf("%d\n", ans);
	return 0;
}
