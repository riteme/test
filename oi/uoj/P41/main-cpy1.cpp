#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200
#define MMAX 400

struct Point {
    int x, y;
};

static int n, m, T;
static int mat[NMAX + 10][MMAX + 10];
static int tail[NMAX + 10];
static Point seq[NMAX + 10][NMAX + 10];
static int ans[NMAX + 10], right[NMAX + 10];

Point last(int x) {
    while (true) {
        Point &p = seq[x][tail[x]];

        if (ans[p.x] != x && p.y >= right[p.x])
            tail[x]--;
        else
            break;
    }

    return seq[x][tail[x]];
}

void dfs(int x) {
    Point p = last(x);
    int y = ans[p.x];
    ans[p.x] = x;
    right[p.x] = p.y;
    if (y)
        dfs(y);
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        right[i] = m + 1;
        for (int j = 1; j <= m; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    memset(tail, 0, sizeof(tail));
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (!mat[i][j])
                continue;

            int x = mat[i][j];
            seq[x][++tail[x]] = {i, j};
        }
    }
}

int main() {
    scanf("%d", &T);

    while (T--) {
        initialize();

        memset(ans, 0, sizeof(ans));
        for (int i = 1; i <= n; i++) {
            dfs(i);
        }

        for (int i = 1; i <= n; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }

    return 0;
}

