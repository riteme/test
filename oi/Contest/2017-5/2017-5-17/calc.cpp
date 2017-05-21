// #define NDEBUG

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define MOD 1000000007

typedef long long i64;

inline i64 inv(i64 n) {
    return n == 1 ? 1 : (MOD - MOD / n) * inv(MOD % n) % MOD;
}

inline i64 qpow(i64 a, i64 b) {
    i64 r = 1;

    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

inline void add(i64 &a, i64 b) {
    a += b % MOD;

    if (a >= MOD)
        a -= MOD;
    if (a < 0)
        a += MOD;
}

static int k, w;
static i64 p[NMAX + 10], a[NMAX + 10];
static i64 y[NMAX + 10][NMAX + 10];
static i64 b[NMAX + 10], c[NMAX + 10];

void initialize() {
    scanf("%d%d", &k, &w);

    for (int i = 1; i <= w; i++) {
        scanf("%lld%lld", p + i, a + i);
    }

    for (int i = 1; i <= k + 2; i++) {
        add(y[i][i], qpow(i, k) + y[i - 1][i - 1]);
    }

    for (int l = 1; l < k + 2; l++) {
        for (int i = 1; i <= k + 2 - l; i++) {
            int j = i + l;
            y[i][j] = (y[i + 1][j] - y[i][j - 1]) * inv(j - i) % MOD;
        }
    }

    b[0] = 1;
    for (int i = 1; i <= k + 2; i++) {
        for (int j = 0; j < i; j++) {
            add(c[j], b[j] * y[1][i]);
        }

        memmove(b + 1, b, sizeof(i64) * i);
        b[0] = 0;
        for (int j = 0; j < i; j++) {
            add(b[j], -b[j + 1] * i);
        }
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);
#endif
    initialize();

    i64 ans = 0;
    for (int i = 0; i <= k + 1; i++) {
        if (c[i] == 0)
            continue;
        
        i64 prod = 1;
        for (int j = 1; j <= w; j++) {
            i64 h = qpow(p[j], a[j] * i) - qpow(p[j], k + a[j] * i - i);
            prod = prod * h % MOD;
        }

        add(ans, c[i] * prod);
    }

    printf("%lld\n", ans);

    return 0;
}
