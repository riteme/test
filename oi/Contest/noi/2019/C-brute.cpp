#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200

typedef long long i64;

static int n, K, L;
static int A[NMAX + 10], B[NMAX + 10];
static i64 f[NMAX + 1][NMAX + 1][NMAX + 1];

inline void chkmax(i64 &a, i64 b) {
    if (a < b) a = b;
}

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d%d", &n, &K, &L);
        for (int i = 1; i <= n; i++) scanf("%d", A + i);
        for (int i = 1; i <= n; i++) scanf("%d", B + i);
        memset(f, 0xff, sizeof(f));
        f[0][0][0] = 0;
        for (int l = 0; l < n; l++) for (int i = min(l, K); i >= 0; i--)
        for (int j = min(l, K); j >= 0; j--) for (int k = min(i, j); k >= 0; k--) {
            if (f[i][j][k] < 0) continue;
            if (i < K) chkmax(f[i + 1][j][k], f[i][j][k] + A[l + 1]);
            if (j < K) chkmax(f[i][j + 1][k], f[i][j][k] + B[l + 1]);
            if (i < K && j < K)
                chkmax(f[i + 1][j + 1][k + 1], f[i][j][k] + A[l + 1] + B[l + 1]);
        }
        i64 ans = 0;
        for (int i = L; i <= K; i++) chkmax(ans, f[K][K][i]);
        printf("%lld\n", ans);
    }

    return 0;
}
