#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;

int n, ans = 0;
char s[NMAX + 10];
vector<int> G[NMAX + 10];

int dfs(int x) {
	int sum = 0, mx = 0;
	int c = 0;
	for (int v : G[x]) {
		int cnt = dfs(v);
		sum += cnt;
		mx = max(mx, cnt);
	}

	if (G[x].size() <= 1) {
		return sum + 1;
	}

	if (sum - mx >= mx) {
		ans += sum / 2;
		return sum % 1 + 1;
	} else {
		int val = sum - mx;
		ans += val;
		return sum - 2 * val + 1;
	}
}

int main() {
	while (scanf("%d%s", &n, s + 1) != EOF) {
		for (int i = 0; i <= n; i++) {
			G[i].clear();
		}

		vector<int> stk;
		stk.push_back(0);
		for (int i = 1; i <= n; i++) {
			if (s[i] == '2') {
				stk.push_back(i);
			} else if (s[i] == '0' && stk.back() != 0) {
				int v = stk.back();
				stk.pop_back();
				int u = stk.back();
				G[u].push_back(v);
			}
		}

		ans = 0;
		dfs(0);
		printf("%d\n", ans);
	}
	return 0;
}
