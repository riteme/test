// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MOD 1000000007

typedef long long i64;

static i64 fac[NMAX + 10];
static i64 inv[NMAX + 10];

inline i64 get_inv(i64 x) {
    if (x == 1)
        return 1;
    return (MOD - MOD / x) * get_inv(MOD % x) % MOD;
}

inline i64 c(int n, int m) {
    if (n < m || n < 0)
        return 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

void initialize() {
    fac[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    inv[NMAX] = get_inv(fac[NMAX]);
    for (int i = NMAX - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("board.in", "r", stdin);
    freopen("board.out", "w", stdout);
#endif
    initialize();

    int t;
    scanf("%d", &t);

    while (t--) {
        int n, r, g, b;
        scanf("%d%d%d%d", &n, &r, &g, &b);

        int x = n - r, y = n - g;
        i64 ans = c(n, x) * c(n - x, y) % MOD;
        printf("%lld\n", ans * 2 % MOD);
    }

    return 0;
}
