#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define MOD 998244353

typedef long long i64;

constexpr i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

int n;
i64 P, Q;
int a[NMAX + 10];

int main() {
    scanf("%d%lld%lld", &n, &P, &Q);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(a + 1, a + n + 1);
    a[0] = a[n + 1] = -1000;

    i64 ans = 0;
    i64 p = P * inv(1000000) % MOD;
    i64 q = Q * inv(1000000) % MOD;
    for (int i = 1; i <= n; i++) {
        i64 v = p + q;
        if (a[i - 1] + 1 == a[i])
            v = v * (1 - q) % MOD;
        if (a[i + 1] - 1 == a[i])
            v = v * (1 - p) % MOD;
        ans = (ans + 1 - v) % MOD;
    }
    if (ans < 0) ans += MOD;

    printf("%lld\n", ans);
    return 0;
}