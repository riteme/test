#include <cstdio>

#define MOD 10007

inline int quick_pow(int a, int b) {
    int r = 1;
    a %= MOD;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

static int _f[2000][2000];

static int c(int n, int m) {
    if (n < m)
        return 0;
    if (n == 1 || m == 0)
        return 1;

    if (_f[n][m])
        return _f[n][m];

    _f[n][m] = (c(n - 1, m) + c(n - 1, m - 1)) % MOD;
    return _f[n][m];
}

int main() {
    int a, b, k, n, m;
    scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);

    printf("%d\n",
        (quick_pow(a, n) * quick_pow(b, m) % MOD)* c(k, n) % MOD
    );

    return 0;
}
