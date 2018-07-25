#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define MMAX 50
#define MOD 1000000007

typedef long long i64;

static int n, m, cntc;
static bool appear[MMAX + 10];
static int pre[MMAX + 10][NMAX + 10];
static int suf[MMAX + 10][NMAX + 10];
static i64 tpow[NMAX + 10], w[NMAX + 10];
static int c[NMAX + 10];

inline int cnt(int col, int l, int r) {
    return (l >= 0 ? pre[col][l] : 0) + suf[col][r];
}

int main() {
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    scanf("%d%d", &n, &m);

    tpow[0] = 1;
    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i);
        tpow[i] = tpow[i - 1] * 2 % MOD;
        w[i] = ((2LL * i + 3) * i % MOD + 3) * i % MOD + 3;
        if (!appear[c[i]])
            cntc++;
        appear[c[i]] = true;
        pre[c[i]][i] = suf[c[i]][i] = 1;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n + 5; j++) {
            pre[i][j] += pre[i][j - 1];
        }

        for (int j = n; j >= 0; j--) {
            suf[i][j] += suf[i][j + 1];
        }
    }

    if (m > cntc) {
        puts("0");
        return 0;
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(appear, 0, sizeof(appear));
        for (int j = i; j <= n; j++) {
            appear[c[j]] = true;

            i64 f = 1;
            for (int col = 1; col <= m; col++) {
                if (appear[col])
                    f = f * tpow[cnt(col, i - 2, j + 2)] % MOD;
                else
                    f = f * (tpow[cnt(col, i - 2, j + 2)] - 1) % MOD;
            }

            ans = (ans + w[j - i + 1] * f) % MOD;
        }
    }

    printf("%lld\n", ans);

    return 0;
}
