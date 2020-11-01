#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;
constexpr i64 MOD = 1000000007;

int a[NMAX + 10];

int solve(vector<int> s, int m) {
	int S = 1;
	for (int i = 0; i < m; i++) {
		S *= 2;
		if (S > NMAX)
			break;
	}
	if (s.empty())
		return 0;
	if (s.size() == S) {
		int val = 0;
		for (int i = 1; i <= s.size(); i++) {
			val += a[i] != s[i - 1];
		}
		return val;
	}

	vector<int> s0, s1;
	s0.reserve((s.size() + 1) / 2);
	s1.reserve((s.size() + 1) / 2);

	int b0 = 0, b1 = 0;
	for (int i = 0; i < s.size(); i += 2) {
		s0.push_back(s[i] - 1);
		b0 += s[i] != 1;
	}
	for (int i = 1; i < s.size(); i += 2) {
		s1.push_back(s[i] - 1);
		b1 += s[i] != 1;
	}

	int c0 = solve(s0, m - 1);
	int c1 = solve(s1, m - 1);
	return min(b0 + c1, b1 + c0);
}

int main() {
	for (int i = 1; i <= NMAX; i++) {
		a[i] = __builtin_clz(i) + 1;
	}

	int n, m;
	vector<int> s;
	while (scanf("%d%d", &n, &m) != EOF) {
		s.clear();
		s.reserve(n);
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			s.push_back(x);
		}

		int ans1 = solve(s, m);
		i64 ans2 = 0;

		printf("%d %d\n", ans1, ans2);
	}


	return 0;
}
