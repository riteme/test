#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000
#define MOD 1000000007

i64 qpow(i64 a, i64 b) {
    i64 r = 1;
    for ( ; b; b >>= 1, a = a * a % MOD)
        if (b & 1) r = r * a % MOD;
    return r;
}

static i64 inv[NMAX + 10];

int main() {
    inv[1] = 1;
    for (int i = 2; i <= NMAX; i++)
        inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;

    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++) {
        i64 n, K;
        scanf("%lld%lld", &n, &K);

        i64 ans = qpow(2, n);
        i64 c = 1;
        for (int m = 0; m < K; m++) {
            ans = (ans - c) % MOD;
            c = c * (n - m) % MOD * inv[m + 1] % MOD;
        }
        if (ans < 0) ans += MOD;
        printf("Case #%d: %lld\n", _t, ans);
    }
    return 0;
}
