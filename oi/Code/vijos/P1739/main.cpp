#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MOD 10007
#define KMAX 1000

typedef long long int64;

inline int64 quick_pow(int64 a, int64 b) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }  // while

    return r;
}

inline int64 fac(int64 n) {
    if (n < 2)
        return 1;

    int64 r = 1;
    for (int64 i = 2; i <= n; i++) {
        r = r * i % MOD;
    }  // for

    return r;
}

inline int64 c(int64 n, int64 m) {
    return fac(n) *
           (quick_pow(fac(m), MOD - 2) * quick_pow(fac(n - m), MOD - 2) % MOD) %
           MOD;
}

static int64 a, b, k, n, m;

int main() {
    scanf("%lld%lld%lld%lld%lld", &a, &b, &k, &n, &m);

    printf("%lld\n", (quick_pow(a, n) * quick_pow(b, m) % MOD) * c(k, n) % MOD);

    return 0;
}  // function main
