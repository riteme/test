#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define MOD 998244353

typedef long long i64;

i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

int n;
i64 INV2, INV3, INV4;
i64 a[NMAX + 10];
i64 pre[NMAX + 10], suf[NMAX + 10];

inline i64 c2(i64 n) {
    return n * (n - 1) % MOD * INV2 % MOD;
}

inline i64 c4(i64 n) {
    return n * (n - 1) % MOD * (n - 2) % MOD * (n - 3) % MOD * INV2 % MOD * INV3 % MOD * INV4 % MOD;
}

int main() {
    INV2 = inv(2);
    INV3 = inv(3);
    INV4 = inv(4);

    scanf("%d", &n);
    n *= 2;
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        pre[i] = (pre[i - 1] + a[i]) % MOD;
    for (int i = n; i >= 1; i--)
        suf[i] = (suf[i + 1] + a[i]) % MOD;

    i64 mi = inv(n - 1);
    i64 mii = inv(n - 3);

    i64 s2 = a[1] * a[1] % MOD, sum1 = 0;
    for (int i = 2; i <= n; i++) {
        sum1 = (sum1 + (i - 1) * a[i] % MOD * a[i] + s2 - 2 * a[i] * pre[i - 1]) % MOD;
        s2 = (s2 + a[i] * a[i]) % MOD;
    }

    i64 sum2 = 0, sf = 0;
    for (int i = 2; i <= n; i++) {
        i64 f = ((i - 1) * a[i] - pre[i - 1]) % MOD;
        sum2 = (sum2 + f * sf) % MOD;
        sf = (sf + f) % MOD;
    }

    i64 sp = a[n - 1] * a[n] % MOD;
    for (int i = n - 2; i >= 1; i--) {
        i64 val = (sp - a[i] * (n - i - 1) % MOD * suf[i + 1] + c2(n - i) * a[i] % MOD * a[i]) % MOD;
        sum2 = (sum2 - val) % MOD;
        sp = (sp + a[i] * suf[i + 1]) % MOD;
    }

    for (int i = 2; i < n; i++) {
        i64 val = (
            ((n - i) * pre[i - 1] + (i - 1) * suf[i + 1]) % MOD * a[i]
            - a[i] * a[i] % MOD * (i - 1) % MOD * (n - i)
            - pre[i - 1] * suf[i + 1]
        ) % MOD;
        // printf("val[%d] = %lld\n", i, val);
        sum2 = (sum2 - val) % MOD;
    }

    // printf("sum1 = %lld, sum2 = %lld\n", sum1, sum2);

    i64 ni = inv(n / 2);
    i64 ans = (
        ni * sum1 % MOD -
        (ni * ni) % MOD * (2 * sum2 * mii % MOD + sum1) % MOD
    ) * mi % MOD;
    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);
    return 0;
}