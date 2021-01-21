#include <cstdio>

using i64 = long long;

constexpr i64 MOD = 1000000007;

i64 qpow(i64 a, i64 k) {
	i64 r = 1;
	for ( ; k; k >>= 1) {
		if (k & 1)
			r = r * a % MOD;
		a = a * a % MOD;
	}
	return r;
}

i64 inv(i64 x) {
	return qpow(x, MOD - 2);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		i64 i1, i2, j1, j2;
		scanf("%lld%lld%lld%lld", &i1, &i2, &j1, &j2);

		i64 p2 = qpow(2, i1) * (qpow(2, i2 - i1 + 1) - 1) % MOD;
		i64 p3 = qpow(3, j1) * (qpow(3, j2 - j1 + 1) - 1) % MOD *
			inv(2) % MOD;
		i64 ans = p2 * p3 % MOD;
		if (ans < 0)
			ans += MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
