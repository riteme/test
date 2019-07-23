#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100

typedef int DP[NMAX + 10][NMAX + 10];

static int n;
static DP f, fp, g, sum;

inline void chkmin(int &a, int &p, int b, int bp) {
    if (a >= b) {
        a = b;
        p = bp;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &sum[i][i]);
        fp[i][i] = i;
    }
    int a1 = INT_MAX, a2 = 0;
    for (int j = 1; j <= n; j++) {
        memset(f, 0x3f, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int i = 1; i <= n; i++) f[i][i] = 0;
        for (int i = 2; i <= n; i++) for (int l = 1; l + i <= n + 1; l++) {
            int r = l + i - 1;
            sum[l][r] = sum[l][r - 1] + sum[r][r];
            for (int p = max(fp[l][r - 1], l + 1); p <= fp[l + 1][r]; p++)
                chkmin(f[l][r], fp[l][r], f[l][p - 1] + f[p][r], p);
            g[l][r] = max(g[l + 1][r], g[l][r - 1]) + sum[l][r];
            f[l][r] += sum[l][r];
        }
        a1 = min(a1, f[1][n]);
        a2 = max(a2, g[1][n]);
        int head = sum[1][1];
        for (int i = 1; i < n; i++) sum[i][i] = sum[i + 1][i + 1];
        sum[n][n] = head;
    }
    printf("%d\n%d\n", a1, a2);

    return 0;
}
