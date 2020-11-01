#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;
using vi = vector<i64>;

auto solve(int m, const vi &x0, const vi &y0) -> vi {
	if (m == 1)
		return {x0[0] * y0[0]};

	int n = m / 3;
	vi x, y;
	x.resize(n);
	y.resize(n);

	for (int i = 0; i < n; i++) {
		x[i] = x0[2 * n + i];
		y[i] = y0[2 * n + i];
	}
	vi z3 = solve(n, x, y);

	for (int i = 0; i < n; i++) {
		x[i] += x0[n + i];
		y[i] += y0[n + i];
	}
	vi z0 = solve(n, x, y);

	for (int i = 0; i < n; i++) {
		x[i] += x0[i];
		y[i] += y0[i];
	}
	vi z012 = solve(n, x, y);

	for (int i = 0; i < n; i++) {
		x[i] -= x0[n + i];
		y[i] -= y0[n + i];
	}
	vi z13 = solve(n, x, y);

	vi &z1 = z13;
	for (int i = 0; i < n; i++) {
		z1[i] -= z3[i];
	}

	vi &z2 = z012;
	for (int i = 0; i < n; i++) {
		z2[i] -= z0[i] + z1[i];
	}

	vi z;
	z.insert(z.end(), z0.begin(), z0.end());
	z.insert(z.end(), z1.begin(), z1.end());
	z.insert(z.end(), z2.begin(), z2.end());
	return z;
}

int main() {
	int K;
	scanf("%d", &K);
	int n = 1;
	for (int _ = 0; _ < K; _++) {
		n *= 3;
	}

	vi x, y;
	x.reserve(n);
	y.reserve(n);
	for (int i = 0; i < n; i++) {
		i64 v;
		scanf("%lld", &v);
		x.push_back(v);
	}
	for (int i = 0; i < n; i++) {
		i64 v;
		scanf("%lld", &v);
		y.push_back(v);
	}

	vi z = solve(n, x, y);
	for (int i = 0; i < n; i++) {
		printf("%lld ", z[i]);
	}
	puts("");

	return 0;
}
