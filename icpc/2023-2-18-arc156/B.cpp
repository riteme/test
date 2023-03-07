#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int AMAX = 400010;
constexpr i64 MOD = 998244353;

int n, K;
bool has[AMAX + 10];
i64 f[2 * AMAX], finv[2 * AMAX];

i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

i64 comb(i64 n, i64 m) {
    return f[n] * finv[m] % MOD * finv[n - m] % MOD;
}

int main() {
    f[0] = 1;
    for (i64 i = 1; i < 2 * AMAX; i++) {
        f[i] = f[i - 1] * i % MOD;
    }
    finv[2 * AMAX - 1] = inv(f[2 * AMAX - 1]);
    for (i64 i = 2 * AMAX - 2; i >= 0; i--) {
        finv[i] = finv[i + 1] * (i + 1) % MOD;
    }

    scanf("%d%d", &n, &K);
    int a;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        has[a] = true;
    }

    i64 ans = 0;
    int cnt = 0;
    for (a = 0; a <= AMAX; a++) {
        int c = cnt + 1;
        if (c <= K)
            ans = (ans + comb(K - c + a, a)) % MOD;
        cnt += !has[a];
    }

    printf("%lld\n", ans);
    return 0;
}
