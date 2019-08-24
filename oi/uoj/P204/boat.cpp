/**
 * 从[0, L]的区间中选出m个数构成递增数列的方案数是
 * C(L, m)
 * 如果允许不选，那么就留出m个空位，因此方案数为
 * C(L + m, m)
 * 基于这个想法，我们将区间离散化，得到至多2 * n个区间
 * 然后枚举这个区间内有多少个学校，那么它们的方案数就是上面所说的
 * 实现的时候需要前缀和优化复杂度，滚动数组优化常数
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500
#define MOD 1000000007

typedef long long i64;

inline i64 quick_pow(i64 a, i64 b) {
    i64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

static int n, cnt;
static i64 l[NMAX + 10], r[NMAX + 10];
static i64 pos[NMAX * 2 + 10];
static i64 f[NMAX * 2 + 10];
static i64 g[NMAX * 2 + 10];
static i64 inv[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", l + i, r + i);
        pos[2 * i] = l[i];
        pos[2 * i - 1] = r[i] + 1;
    }

    sort(pos + 1, pos + n * 2 + 1);
    cnt = unique(pos + 1, pos + n * 2 + 1) - pos - 1;

    for (i64 i = 1; i <= n; i++) {
        inv[i] = quick_pow(i, MOD - 2);
    }
}

int main() {
    initialize();

    f[0] = 1;
    g[0] = 1;
    for (int j = 1; j < cnt; j++) {
        for (int i = n; i >= 1; i--) {
            if (r[i] < pos[j] || pos[j + 1] <= l[i])
                continue;

            int m = 1;
            i64 L = pos[j + 1] - pos[j];
            i64 c = L;
            for (int k = i - 1; k >= 0; k--) {
                g[i] = (g[i] + g[k] * c % MOD) % MOD;

                if (l[k] <= pos[j] && pos[j + 1] <= r[k] + 1) {
                    m++;
                    c = (c * inv[m] % MOD) * (L + m - 1) % MOD;
                }
            }
        }
    }

    i64 answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = (answer + g[i]) % MOD;
    }
    printf("%lld\n", answer);

    return 0;
}
