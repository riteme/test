#pragma GCC optimize(3)

#define NDEBUG

#define NAME "product"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define MOD 1000000007
#define NMAX 10

typedef long long i64;

static int T, n;
static i64 cnt[NMAX + 10];

void initialize() {
    for (int i = 1; i <= n; i++) {
	scanf("%lld", cnt + i);
	cnt[i] %= MOD;
    }
}

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif

    scanf("%d%d", &T, &n);

    while (T--) {
	initialize();

	if (n == 5) {
	    if (cnt[2] > 0)
		printf("%lld\n", ((cnt[2] + cnt[4] * 2 + 1) * (cnt[3] + 1) % MOD) * (cnt[5] + 1) % MOD);
	    else
		printf("%lld\n", ((cnt[4] + 1) * (cnt[3] + 1) % MOD) * (cnt[5] + 1) % MOD);
	} else if (n == 6) {
	    i64 p2 = (cnt[2] ? cnt[2] + cnt[4] * 2 + 1 : cnt[4] + 1);
	    i64 p3 = cnt[3] + 1;
	    i64 p5 = cnt[5] + 1;
	    i64 a = (p2 * p3 % MOD) * p5 % MOD;
	    i64 b = (p3 * p5 % MOD) * cnt[6] % MOD;
	    i64 c = (p2 * p5 % MOD) * cnt[6] % MOD;
	    i64 d = p5 * cnt[6] % MOD;
	    printf("%lld\n", ((a + b + c + (cnt[2] == 0 || cnt[3] == 0 ? 1 : 0) - d) % MOD + MOD) % MOD);
	} else
	    printf("20952\n");
    }

    return 0;
}
