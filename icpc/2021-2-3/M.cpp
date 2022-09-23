#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i8 = __int128_t;
using i64 = long long;

constexpr int NMAX = 1000000;
constexpr i64 MOD = 1000000000000000031;

i64 qpow(i64 a, i64 k) {
    i8 r = 1;
    for ( ; k; k >>= 1) {
        if (k & 1)
            r = r * a % MOD;
        a = i8(a) * a % MOD;
    }
    return r;
}

i64 f[NMAX + 10];

int main() {
    int n;
    scanf("%d", &n);
    f[NMAX] = 300;
    for (int i = NMAX; i > n; i--) {
        f[i - 1] = qpow(42, f[i]);
    }
    printf("%lld\n", f[n]);
    return 0;
}