#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100
#define MOD 1811939329

typedef long long i64;

i64 qpow(i64 a, int b) {
    i64 r = 1;
    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

static int n;
static i64 A[NMAX + 10];
static i64 C[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n + 1; i++) {
        scanf("%lld", A + i);
    }
}

int main() {
    freopen("le.in", "r", stdin);
    freopen("le.out", "w", stdout);
    initialize();

    for (int i = 1; i <= n + 1; i++) {
        C[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            C[i][j] = C[i - 1][j] * A[j] % MOD;
        }
    }

    for (int i = 1; i < n; i++) {
        if (C[i][i] == 0) {
            int p;
            for (int j = i + 1; j <= n; j++) {
                if (C[j][i]) {
                    p = j;
                    break;
                }
            }

            for (int j = i; j <= n + 1; j++) {
                swap(C[i][j], C[p][j]);
            }
        }

        for (int j = i + 1; j <= n; j++) {
            i64 r = C[j][i] * inv(C[i][i]) % MOD;

            for (int k = i; k <= n + 1; k++) {
                C[j][k] = (C[j][k] - C[i][k] * r) % MOD;
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        C[i][n + 1] = C[i][n + 1] * inv(C[i][i]) % MOD;
        for (int j = i - 1; j >= 1; j--) {
            C[j][n + 1] = (C[j][n + 1] - C[j][i] * C[i][n + 1]) % MOD;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (C[i][n + 1] < 0)
            C[i][n + 1] += MOD;
        printf("%lld ", C[i][n + 1]);
    }
    putchar('\n');

    return 0;
}
