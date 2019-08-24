#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define NMAX 500

static int n, m;
static int h[NMAX + 10][NMAX + 10];
static bool marked[NMAX + 10][NMAX + 10];
static int left[NMAX + 10][NMAX + 10];
static int right[NMAX + 10][NMAX + 10];
static int f[NMAX + 10];

static void dfs(int i, int j) {
    if (marked[i][j])
        return;

    if (i == n)
        left[i][j] = right[i][j] = j;
    else
        left[i][j] = INT_MAX;

    marked[i][j] = true;

    const int dx[] = { 1, -1, 0, 0 };
    const int dy[] = { 0, 0, 1, -1 };
    for (int pos = 0; pos < 4; pos++) {
        int tx = dx[pos];
        int ty = dy[pos];

        if (h[i][j] > h[i + tx][j + ty]) {
            dfs(i + tx, j + ty);

            left[i][j] = min(left[i][j], left[i + tx][j + ty]);
            right[i][j] = max(right[i][j], right[i + tx][j + ty]);
        }
    }  // for
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++)
            h[i][j] = INT_MAX;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &h[i][j]);
}

int main() {
    initialize();

    for (int i = 1; i <= m; i++)
        if (!marked[1][i])
            dfs(1, i);

    int wcnt = 0;
    for (int i = 1; i <= m; i++)
        if (!marked[n][i])
            wcnt++;

    if (wcnt > 0) {
        printf("0\n%d\n", wcnt);
    } else {
        for (int i = 1; i <= m; i++) {
            f[i] = INT_MAX;

            for (int j = 1; j <= m; j++)
                if (left[1][j] <= i && i <= right[1][j])
                    f[i] = min(f[i], f[left[1][j] - 1] + 1);
        }  // for

        printf("1\n%d\n", f[m]);
    }

    return 0;
}  // function main
