#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 256

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Graph {
    Graph() {
        memset(mat, 0, sizeof(mat));
    }

    void dfs(int x, int y) {
        static int tx, ty;
        mark[x][y] = true;

        for (int i = 0; i < 4; i++) {
            tx = x + dx[i];
            ty = y + dy[i];

            if (!test(tx, ty) || mark[tx][ty])
                continue;

            dfs(tx, ty);
        }
    }

    void eval() {
        memset(mark, 0, sizeof(mark));
        ans = 0;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (!mark[x][y] && mat[x][y]) {
                    ans++;
                    dfs(x, y);
                }
            }
        }
    }

    void add(int x, int y) {
        ans += delta(x, y);
        mat[x][y] = true;
    }

    void del(int x, int y) {
        mat[x][y] = false;
        ans -= delta(x, y);
    }

    int delta(int x, int y) {
        int cnt = 0, ret = 0;
        for (int i = 0; i < 4; i++) {
            cnt += test(x + dx[i], y + dy[i]);
        }

        if (cnt != 1)
            ret++;
        if (cnt > 1) {
            memset(mark, 0, sizeof(mark));
            for (int i = 0; i < 4; i++) {
                int tx = x + dx[i];
                int ty = y + dy[i];

                if (test(tx, ty) && !mark[tx][ty]) {
                    ret--;
                    dfs(tx, ty);
                }
            }
        }

        return ret;
    }

    bool test(int x, int y) {
        return (x != -1) && (x != n) && (y != -1) && (y != m) && mat[x][y];
    }

    int n, m, ans;
    bool mat[NMAX][NMAX], mark[NMAX][NMAX];
};

static int n, m, q, lastans;
static char mat[NMAX + 10][NMAX + 10];
static Graph black, white;

void initialize() {
    scanf("%d%d%d", &n, &m, &q);
    black.n = white.n = n;
    black.m = white.m = m;

    for (int i = 0; i < n; i++) {
        scanf("%s", mat[i]);
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == '1')
                black.mat[i][j] = true;
            else
                white.mat[i][j] = true;
        }
    }

    black.eval();
    white.eval();
    lastans = black.ans + white.ans;
}

int main() {
    freopen("chessboard.in", "r", stdin);
    freopen("chessboard.out", "w", stdout);
    initialize();

    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        x ^= lastans;
        y ^= lastans;
        x--, y--;
        
        if (mat[x][y] == '1') {
            black.del(x, y);
            white.add(x, y);
            mat[x][y] = '0';
        } else {
            black.add(x, y);
            white.del(x, y);
            mat[x][y] = '1';
        }

        lastans = black.ans + white.ans;
        printf("%d\n", lastans);
    }

    return 0;
}
