#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 3000
#define INF 0x3f3f3f3f

typedef int DP[NMAX + 1][NMAX + 1];

static int n, m;
static int pos[NMAX + 10];

inline void chkmin(int &a, int b) {
    if (a > b) a = b;
}

inline void chkmin(int &a, short &p, int b, int bp) {
    if (a > b) {
        a = b;
        p = bp;
    }
}

static short mp[3001][3001];
inline void dp(DP a, DP b, DP o) {
    if (b[1][1] == INF) {
        memcpy(o, a, sizeof(DP));
        return;
    }
    //memset(o, 0x3f, sizeof(DP));
    for (int i = 1; i <= n; i++) o[i][i] = 0;
    for (short i = 2; i <= n; i++) for (short l = 1; l + i <= n + 1; l++) {
        short r = l + i - 1;
        register int ret = INF;
        for (short p = max(mp[l][r - 1], static_cast<short>(l + 1)); p <= mp[l + 1][r]; p++)
            chkmin(ret, mp[l][r], a[l][p - 1] + b[p][r], p);
        o[l][r] = ret;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", pos + i);
    for (int i = 1; i <= n; i++) mp[i][i] = i;
    sort(pos + 1, pos + n + 1);

    static DP cur, tmp, res;
    memset(cur, 0x3f, sizeof(cur));
    res[1][1] = INF;
    for (int i = 1; i <= n; i++) {
        cur[i][i] = 0;
        int l, r, s;
#define EVAL(L, R) \
        l = L, r = R, s = 0; \
        for (; l >= 1 && r <= n; l--, r++) { \
            s += pos[r] - pos[l]; \
            chkmin(cur[l][r], s); \
        }
        EVAL(i - 1, i + 1);
        EVAL(i - 1, i);
        EVAL(i, i + 1);
    }
    for (; m; m >>= 1) {
        if (m & 1) {
            dp(cur, res, tmp);
            memcpy(res, tmp, sizeof(res));
        }
        dp(cur, cur, tmp);
        memcpy(cur, tmp, sizeof(cur));
    }
    printf("%d\n", res[1][n]);

    return 0;
}
