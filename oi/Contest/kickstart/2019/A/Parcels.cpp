#pragma GCC optimize(3)
#pragma GCC optimize("-Ofast")

#include <cstdio>
#include <cstring>
#include <climits>

#include <map>
#include <algorithm>

using namespace std;

#define NMAX 250

struct Point {
    int x, y, d;

    bool operator<(const Point &b) const {
        return d > b.d;
    }
};

static int n, m, K;
static char M[NMAX + 10][NMAX + 10];
static int D[NMAX + 10][NMAX + 10];
static int up[NMAX + 10], dw[NMAX + 10];
static Point P[NMAX * NMAX + 10];

inline void chkmin(int &a, int b) {
    if (b < a) a = b;
}

inline void chkmax(int &a, int b) {
    if (b > a) a = b;
}

inline int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%s", M[i] + 1);
        memset(up, 0, sizeof(up));
        memset(dw, 0, sizeof(dw));
        for (int j = 1; j <= m; j++)
            for (dw[j] = 1; dw[j] <= n && M[dw[j]][j] == '0'; dw[j]++) ;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                D[i][j] = INT_MAX;
                for (int k = 1; k <= m; k++) {
                    if (up[k]) chkmin(D[i][j], dist(up[k], k, i, j));
                    if (dw[k] <= n) chkmin(D[i][j], dist(dw[k], k, i, j));
                }
            }
            for (int j = 1; j <= m; j++) if (!dw[j] || dw[j] == i) {
                up[j] = dw[j];
                for (dw[j]++; dw[j] <= n && M[dw[j]][j] == '0'; dw[j]++) ;
            }
        }

        //for (int i = 1; i <= n; i++) {
        //    for (int j = 1; j <= m; j++)
        //        printf("%d", D[i][j]);
        //    puts("");
        //}

        K = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
            P[K++] = {i, j, D[i][j]};
        sort(P, P + K);
        int ans = INT_MAX;
        for (int i = 0; i < K; i++) {
            int maxd = 0, x = P[i].x, y = P[i].y;
            for (int j = 0; j < K; j++) {
                auto &p = P[j];
                if (maxd >= p.d) break;
                int nd = dist(p.x, p.y, x, y);
                if (nd < p.d) chkmax(maxd, nd);
                else {
                    chkmax(maxd, p.d);
                    break;
                }
            }
            chkmin(ans, maxd);
        }

        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
