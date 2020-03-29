#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 12
#define RMOD 10000007
#define MOD1 941
#define MOD2 10627

typedef long long i64;

typedef i64 Matrix[NMAX][NMAX];

void mul(Matrix a, Matrix b, int n, i64 MOD) {
    Matrix c;
    memset(c, 0, sizeof(c));

    for (int i = 0; i < n; i++)
    for (int k = 0; k < n; k++)
    for (int j = 0; j < n; j++)
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;

    memcpy(a, c, sizeof(c));
}

void qpow(Matrix a, int k, int n, i64 MOD) {
    Matrix c;
    memset(c, 0, sizeof(c));
    for (int i = 0; i < n; i++)
        c[i][i] = 1;

    for ( ; k; k >>= 1) {
        if (k & 1)
            mul(c, a, n, MOD);
        mul(a, a, n, MOD);
    }

    memcpy(a, c, sizeof(c));
}

int n, m;
i64 a[NMAX];
Matrix T;

i64 solve(i64 MOD) {
    memset(T, 0, sizeof(T));

    for (int i = 0; i < n; i++)
    for (int j = i; j <= n; j++)
        T[i][j] = 1;
    T[n][n] = 10;
    T[n][n + 1] = 3;
    T[n + 1][n + 1] = 1;
    qpow(T, m, n + 2, MOD);

    i64 ret = 0;
    for (int i = 0; i <= n + 1; i++) {
        ret += T[0][i] * a[i];
        if (ret >= MOD)
            ret -= MOD;
    }

    return ret;
}

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) return x = 1, y = 0, a;
    i64 t = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return t;
}

i64 crt(i64 a, i64 am, i64 b, i64 bm) {
    i64 x, y, g = exgcd(am, bm, x, y);
    i64 m = am / g * bm;
    x = -x % m * (a - b) / g % m;
    return (x * am + a) % m;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = n - 1; i >= 0; i--)
            scanf("%lld", a + i);
        a[n] = 233;
        a[n + 1] = 1;

        i64 a1 = solve(MOD1);
        i64 a2 = solve(MOD2);
        i64 ans = crt(a1, MOD1, a2, MOD2);
        if (ans < 0) ans += RMOD;
        printf("%lld\n", ans);
    }
    return 0;
}