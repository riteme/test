#pragma GCC optimize(3)

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 30
#define MOD 1000000009

static int n, m;
static char mat[NMAX + 10][NMAX + 10];
static bool vis[NMAX + 10][NMAX + 10][NMAX + 10][NMAX + 10];
static int f[NMAX + 10][NMAX + 10][NMAX + 10][NMAX + 10];

const int dx[] = {1, 1, 0, -1, -1, -1,  0,  1, 1};
const int dy[] = {0, 1, 1,  1,  0, -1, -1, -1, 0};
const int l[]  = {0, 0, 2, 2, 4, 4, 6, 6};
const int r[]  = {0, 2, 2, 4, 4, 6, 6, 8};

#define add(dest, src) dest += src; \
    if (dest >= MOD) dest -= MOD; \
    else if (dest < 0) dest += MOD;

// inline void add(int &dest, int src) {
//     dest += src;
//     if (dest >= MOD)
//         dest -= MOD;
//     else if (dest < 0)
//         dest += MOD;
// }

static int d1, d2;

int dp(int x1, int y1, int x2, int y2) {
    if (vis[x1][y1][x2][y2])
        return f[x1][y1][x2][y2];

    vis[x1][y1][x2][y2] = true;
    int &ret = f[x1][y1][x2][y2];
    ret = 0;

    for (int i = l[d1]; i <= r[d1]; i++) {
        for (int j = l[d2]; j <= r[d2]; j++) {
            int tx1 = x1 + dx[i];
            int ty1 = y1 + dy[i];
            int tx2 = x2 + dx[j];
            int ty2 = y2 + dy[j];

            if (tx1 < 1 || tx1 > n ||
                ty1 < 1 || ty1 > m ||
                tx2 < 1 || tx2 > n ||
                ty2 < 1 || ty2 > m ||
                mat[tx1][ty1] != mat[tx2][ty2])
                continue;

            add(ret, 1 + dp(tx1, ty1, tx2, ty2));
        }
    }

    return ret;
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%s", &mat[i][1]);
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("makina.in", "r", stdin);
    freopen("makina.out", "w", stdout);
#endif
    initialize();

    int answer = 0;
    for (d1 = 0; d1 < 8; d1++) {
    for (d2 = 0; d2 < 8; d2++) {
        memset(vis, 0, sizeof(vis));
        int f = ((d1 & 1) ^ (d2 & 1)) ? -1 : 1;

        for (int x1 = 1; x1 <= n; x1++) {
        for (int y1 = 1; y1 <= m; y1++) {
        for (int x2 = 1; x2 <= n; x2++) {
        for (int y2 = 1; y2 <= m; y2++) {
            if (mat[x1][y1] != mat[x2][y2])
                continue;

            // if (dp(x1, y1, x2, y2) > 0)
            //     printf("d1 = %d, d2 = %d, (%d, %d), (%d, %d) = %d\n",
            //             d1, d2, x1, y1, x2, y2, f * dp(x1, y1, x2, y2));

            add(answer, f * dp(x1, y1, x2, y2));
        }}}}
    }}

    printf("%d\n", answer);

    return 0;
}
