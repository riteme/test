#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500
#define MOD 1000000007

typedef long long i64;

inline i64 quick_pow(i64 a, i64 b) {
    i64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

static int n, cnt;
static i64 l[NMAX + 10], r[NMAX + 10];
static i64 pos[NMAX * 2 + 10];
static i64 f[NMAX + 10][NMAX * 2 + 10];
static i64 g[NMAX + 10][NMAX * 2 + 10];
static i64 inv[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", l + i, r + i);
        pos[2 * i] = l[i];
        pos[2 * i - 1] = r[i] + 1;
    }

    sort(pos + 1, pos + n * 2 + 1);
    cnt = unique(pos + 1, pos + n * 2 + 1) - pos - 1;

    for (i64 i = 1; i <= n; i++) {
        inv[i] = quick_pow(i, MOD - 2);
    }
}

int main() {
    initialize();

    f[0][0] = 1;
    l[0] = 0;
    r[0] = 1000000000;
    for (int i = 0; i < cnt; i++) {
        g[0][i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < cnt; j++) {
            if (r[i] < pos[j] || pos[j + 1] <= l[i]) {
                f[i][j] = 0;
                g[i][j] = g[i][j - 1];
                continue;
            }

            int m = 1;
            i64 L = pos[j + 1] - pos[j];
            i64 c = L;
            for (int k = i - 1; k >= 0; k--) {
                f[i][j] += g[k][j - 1] * c % MOD;
                f[i][j] %= MOD;
                g[i][j] = (g[i][j - 1] + f[i][j]) % MOD;

                if (l[k] <= pos[j] && pos[j + 1] <= r[k] + 1) {
                    m++;
                    c = (c * inv[m] % MOD) * (L + m - 1) % MOD;
                }
            }
        }
    }

    i64 answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = (answer + g[i][cnt - 1]) % MOD;
    }
    printf("%lld\n", answer);

    return 0;
}
