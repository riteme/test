#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 2000
#define _SMAX 512
#define MOD 1000000007

int n, w, K, SMAX;
bool ok[NMAX + 10][NMAX + 10];
i64 f[NMAX + 10][_SMAX];

int extend(int i, int s) {
    return (s >> 1) | (i + w + 1 <= n ? 0 : (SMAX >> 1));
}

void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int main() {
    scanf("%d%d%d", &n, &w, &K);
    memset(ok, 1, sizeof(ok));
    for (int i = 0; i < K; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        ok[u][v] = 0;
    }

    SMAX = 1 << (2 * w + 1);
    int s = 0;
    for (int i = 1; i <= n && i <= w + 1; i++)
        s |= 1 << (i + w - 1);
    f[1][(~s) & (SMAX - 1)] = 1;

    for (int i = 1; i <= n; i++)
    for (int s = 0; s < SMAX; s++) if (f[i][s]) {
        if (!(s & 1)) {
            if (i - w >= 1 && ok[i][i - w])
                add(f[i + 1][extend(i, s)], f[i][s]);
        } else {
            for (int j = 0; j <= 2 * w; j++) if (!((s >> j) & 1)) {
                int v = i + j - w;
                if (1 <= v && v <= n && ok[i][v])
                    add(f[i + 1][extend(i, s | (1 << j))], f[i][s]);
            }
        }
    }

    printf("%lld\n", f[n + 1][SMAX - 1]);
    return 0;
}