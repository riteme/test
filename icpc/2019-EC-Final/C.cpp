#pragma GCC optimize("O3")
#pragma GCC option("unroll-loops")

#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr size_t BUFFERSIZE = 65536;
char _buf[BUFFERSIZE];
size_t _pos = BUFFERSIZE;

char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do c = _getchar(); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        c = _getchar();
    } while (isdigit(c));
}

using i64 = long long;

constexpr int NMAX = 100000;
constexpr i64 MOD = 998244353;
constexpr int LMAX = 29;

int n, K;
i64 g[NMAX + 10];
i64 f[NMAX + 10][LMAX + 1];
i64 h[NMAX + 10][LMAX + 1];

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

int main() {
    // scanf("%d%d", &n, &K);
    read(n); read(K);
    for (int i = 1; i <= n; i++) {
        // scanf("%lld", g + i);
        read(g[i]);
    }

    assert(g[1] == 1);
    for (int j = 0; j <= LMAX; j++) {
        f[1][j] = h[1][j] = 1;
    }

    i64 ik = inv(K);
    for (int i = 2; i <= n; i++) {
        i64 v = 0;
        for (int j = 1; j <= LMAX; j++) {
            v = (f[i][j] + 2 * v) % MOD;
            // printf("f'[%d][%d]=%lld\n", j, i, v);

            if ((K >> j) & 1)
                h[i][j] = (h[i][j] + h[i][j - 1] + v) % MOD;
            else
                h[i][j] = (h[i][j] + h[i][j - 1]) % MOD;
        }

        // for (int j = 0; j < 6; j++) {
        //     printf("f[%d][%d]=%lld, h[%d][%d]=%lld\n", j, i, f[i][j], j, i, h[i][j]);
        // }

        f[i][0] = (g[i] - h[i][LMAX]) * ik % MOD;

        for (int j = 0; j < LMAX; j++) {
            f[i][j + 1] = (f[i][j + 1] + 2 * f[i][j]) % MOD;
        }

        int k = 2, p = 2 * i;
        for ( ; k < i && p <= n; k++, p += i)
        for (int j = 0; j < LMAX; j++) {
            f[p][j + 1] = (f[p][j + 1] + 2 * f[k][j] * f[i][j]) % MOD;
        };

        if (k == i && p <= n) {
            for (int j = 0; j < LMAX; j++) {
                f[p][j + 1] = (f[p][j + 1] + f[i][j] * f[i][j]) % MOD;
            }
        }

        for (int j = 0; j <= LMAX; j++) {
            int mask = (1 << (j + 1)) - 1;
            int cnt = K & mask;
            h[i][j] = (h[i][j] + cnt * f[i][0]) % MOD;
        }

        k = 2, p = 2 * i;
        for ( ; k < i && p <= n; k++, p += i)
        for (int j = 1; j <= LMAX; j++)
        if ((K >> j) & 1) {
            h[p][j] = (h[p][j] + h[k][j - 1] * f[i][j] + h[i][j - 1] * f[k][j]) % MOD;
        };

        if (k == i && p <= n) {
            for (int j = 1; j <= LMAX; j++)
            if ((K >> j) & 1) {
                h[p][j] = (h[p][j] + h[i][j - 1] * f[i][j]) % MOD;
            }
        }
    }

    // for (int i = 1; i <= n; i++) {
    //     i64 v = h[i][LMAX];
    //     if (v < 0)
    //         v += MOD;
    //     assert(v == g[i]);
    //     printf("%lld ", v);
    // }
    // puts("");

    for (int i = 1; i <= n; i++) {
        i64 v = f[i][0];
        if (v < 0)
            v += MOD;
        printf("%lld ", v);
    }
    puts("");

    return 0;
}