#include <cstdio>

using namespace std;

using i64 = long long;

constexpr i64 MOD = 1000000007;
constexpr i64 INV2 = (MOD + 1) / 2;

int main() {
	int T;
	scanf("%d", &T);

	while (T--) {
		i64 N, K;
		scanf("%lld%lld", &N, &K);
		i64 ans = (K + 1) * (N + 1) % MOD * (N + 2) % MOD * INV2 % MOD;
		printf("%lld\n", ans);
	}

	return 0;
}
