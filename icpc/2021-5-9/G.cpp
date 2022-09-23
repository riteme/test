#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr i64 NMAX = 823543;
constexpr i64 MOD = 998244353;
constexpr i64 G = 3;

void add(i64 &a, i64 b) {
    a = (a + b) % MOD;
}

void conv(int n, i64 w[7][7], i64 *a, i64 *b) {
    if (n == 1)
        b[0] = a[0];
    else {
        int m = n / 7;

        i64 c[n];
        for (int i = 0; i < 7; i++) {
            conv(n / 7, w, a + i * m, c + i * m);
        }

        memset(b, 0, sizeof(i64) * n);
        for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++) {
            for (int l = 0; l < m; l++) {
                add(b[i * m + l], w[i][j] * c[j * m + l]);
            }
        }
    }
}

i64 qpow(i64 a, i64 k) {
    i64 r = 1;
    for ( ; k; k >>= 1) {
        if (k & 1)
            r = r * a % MOD;
        a = a * a % MOD;
    }
    return r;
}

i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

void imul(i64 *a, i64 *b) {
    for (int i = 0; i < NMAX; i++) {
        a[i] = a[i] * b[i] % MOD;
    }
}

i64 a[NMAX], b[NMAX], c[NMAX];
i64 w[7][7];

int main() {
    int cnt;
    i64 K;
    scanf("%d%lld", &cnt, &K);
    for (int i = 0; i < cnt; i++) {
        i64 u, v = 0, pw = 1;
        scanf("%lld", &u);
        for (int j = 0; j < 7; j++) {
            if (u & 1)
                v += pw;
            u >>= 1;
            pw *= 7;
        }

        a[v]++;
    }

    i64 r = qpow(G, (MOD - 1) / 7);

    for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++) {
        w[i][j] = qpow(r, i * j);
    };

    conv(NMAX, w, a, b);

    for (int i = 0; i < NMAX; i++) {
        c[i] = 1;
    }
    for ( ; K; K >>= 1) {
        if (K & 1)
            imul(c, b);
        imul(b, b);
    }

    i64 i7 = inv(7);
    for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++) {
        w[i][j] = qpow(r, MOD - 1 - i * j) * i7 % MOD;
    };

    conv(NMAX, w, c, b);

    printf("%lld\n", b[0]);

    return 0;
}