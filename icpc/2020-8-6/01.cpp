#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define MOD 1000000007
#define INV2 500000004

typedef long long i64;

int n;
i64 pre[NMAX + 10], suf[NMAX + 10];
i64 a[NMAX + 10];

i64 inv(i64 x) {
    return x > 1 ? MOD - MOD / x * inv(MOD % x) % MOD : 1;
}

void _main() {
    scanf("%d", &n);
    pre[0] = suf[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] * i % MOD;
    }
    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] * i % MOD;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
        a[i] += a[i - 1];
    }

    i64 ans = 0, sum = 0;
    for (int l = 1; l <= (n + 1) / 2; l++) {
        int L = n - l + 1;
        sum = (sum + a[n - l + 1] - a[l - 1]) % MOD;
        ans = (ans + sum * pre[l - 1] % MOD * suf[l + 1]) % MOD;
        if (l != L)
            ans = (ans + sum * pre[L - 1] % MOD * suf[L + 1]) % MOD;
    }

    i64 dem = pre[n] * n % MOD * (n + 1) % MOD * INV2 % MOD;
    ans = ans * inv(dem) % MOD;
    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }

    return 0;
}