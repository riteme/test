// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

#define NMAX 1000

static int n, m, c;
static bool mat[NMAX + 10][NMAX + 10];
static bool marked[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &c);

    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < c; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        mat[x][y] = true;
    }  // for
}

int dfs(int x, int y) {
    marked[x][y] = true;

    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, 1, -1};

    int ret = 1;
    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];

        if (mat[tx][ty] || marked[tx][ty] || tx < 1 || tx > n || ty < 1 ||
            ty > m)
            continue;

        ret += dfs(tx, ty);
    }  // for

    return ret;
}

bool invalid() {
    if (c >= n * m - 1)
        return true;

    if (c + 2 == n * m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (mat[i][j])
                    continue;

                const int dx[] = {1, -1, 0, 0};
                const int dy[] = {0, 0, 1, -1};

                for (int p = 0; p < 4; p++) {
                    int tx = i + dx[p];
                    int ty = j + dy[p];

                    if (mat[tx][ty] || tx < 1 || tx > n || ty < 1 || ty > m)
                        continue;

                    return true;
                }  // for
            }      // for
        }          // for
    }

    return false;
}

bool ok() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!mat[i][j]) {
                memset(marked, 0, sizeof(marked));
                return dfs(i, j) + c <= n * m - 1;
            }
        }  // for
    }      // for

    return false;
}

bool ok1() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mat[i][j])
                continue;

            mat[i][j] = true;
            c++;

            if (ok())
                return true;

            mat[i][j] = false;
            c--;
        }  // for
    }      // for

    return false;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        if (invalid())
            puts("-1");
        else if (ok())
            puts("0");
        else if (ok1())
            puts("1");
        else
            puts("2");
    }  // while

    return 0;
}
