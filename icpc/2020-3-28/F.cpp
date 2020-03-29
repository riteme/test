#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

int n, m;
char a[32][32];
char f[32][32][32][32][2];
char out[32][32][32][32][2];

struct z {
    z(int _x1, int _y1, int _x2, int _y2, int _t)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2), t(_t) {}

    char x1, y1, x2, y2, t;
};

void solve() {
    int xq, yq, xa, ya;
    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= m; y++) {
        if (a[x][y] == 'Q')
            xq = x, yq = y;
        else if (a[x][y] == 'A')
            xa = x, ya = y;
    }

    for (int i = 0; i <= n + 1; i++)
        a[i][0] = a[i][m + 1] = '#';
    for (int i = 0; i <= m + 1; i++)
        a[0][i] = a[n + 1][i] = '#';

    queue<z> q;
    for (int x1 = 1; x1 <= n; x1++)
    for (int y1 = 1; y1 <= m; y1++)
    for (int x2 = 1; x2 <= n; x2++)
    for (int y2 = 1; y2 <= m; y2++)
    for (int t = 0; t < 2; t++) {
        char &v = f[x1][y1][x2][y2][t];
        if (x1 == x2 && y1 == y2)
            v = 1;
        else if (a[x1][y1] == 'E' && t == 0)
            v = 0;
        else v = 2;
        if (v != 2 && a[x1][y1] != '#' && a[x2][y2] != '#')
            q.push(z(x1, y1, x2, y2, t));

        char &cnt = out[x1][y1][x2][y2][t];
        cnt = 0;
        constexpr int dx[] = {-1, 1, 0, 0, 0};
        constexpr int dy[] = {0, 0, -1, 1, 0};
        for (int i = 0; i < 5; i++) {
            int tx1 = x1 + (t ? 0 : dx[i]);
            int ty1 = y1 + (t ? 0 : dy[i]);
            int tx2 = x2 + (t ? dx[i] : 0);
            int ty2 = y2 + (t ? dy[i] : 0);
            if (a[tx1][ty1] == '#' || a[tx2][ty2] == '#')
                continue;
            cnt++;
        }
    }

    do {
        z u = q.front();
        q.pop();

        char x = f[u.x1][u.y1][u.x2][u.y2][u.t];
        // fprintf(stderr, "Q(%d,%d)A(%d,%d), cur = %s, win = %s\n", int(u.x1), int(u.y1), int(u.x2), int(u.y2), u.t ? "A" : "Q", x ? "A" : "Q");

        constexpr int dx[] = {-1, 1, 0, 0, 0};
        constexpr int dy[] = {0, 0, -1, 1, 0};
        for (int i = 0; i < 5; i++) {
            int tx1 = u.x1 + (u.t ? dx[i] : 0);
            int ty1 = u.y1 + (u.t ? dy[i] : 0);
            int tx2 = u.x2 + (u.t ? 0 : dx[i]);
            int ty2 = u.y2 + (u.t ? 0 : dy[i]);
            if (a[tx1][ty1] == '#' || a[tx2][ty2] == '#')
                continue;

            char &y = f[tx1][ty1][tx2][ty2][u.t^1];
            if (y != 2) continue;

            char &c = out[tx1][ty1][tx2][ty2][u.t^1];
            if (x == u.t) {
                c--;
                // fprintf(stderr, "Q(%d,%d)A(%d,%d)@%s=%s → ", int(u.x1), int(u.y1), int(u.x2), int(u.y2), u.t ? "A" : "Q", x ? "A" : "Q");
                // fprintf(stderr, "Q(%d,%d)A(%d,%d)@%s cnt = %d\n", tx1, ty1, tx2, ty2, u.t^1 ? "A" : "Q", c);
                if (!c) {
                    y = u.t;
                    // fprintf(stderr, "Q(%d,%d)A(%d,%d)@%s=%s → ", int(u.x1), int(u.y1), int(u.x2), int(u.y2), u.t ? "A" : "Q", x ? "A" : "Q");
                    // fprintf(stderr, "Q(%d,%d)A(%d,%d)@%s=%s (due2 c=0)\n", tx1, ty1, tx2, ty2, u.t^1 ? "A" : "Q", y ? "A" : "Q");
                }
            } else {
                y = u.t^1;
                // fprintf(stderr, "Q(%d,%d)A(%d,%d)@%s=%s → ", int(u.x1), int(u.y1), int(u.x2), int(u.y2), u.t ? "A" : "Q", x ? "A" : "Q");
                // fprintf(stderr, "Q(%d,%d)A(%d,%d)@%s=%s (due2 win)\n", tx1, ty1, tx2, ty2, u.t^1 ? "A" : "Q", y ? "A" : "Q");
            }

            if (y != 2)
                q.push(z(tx1, ty1, tx2, ty2, u.t^1));
        }
    } while (!q.empty());

    char v = f[xq][yq][xa][ya][0];
    if (v == 0) puts("Queen can escape.");
    else if (v == 1) puts("Army can catch Queen.");
    else puts("Queen can not escape and Army can not catch Queen.");
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        swap(n, m);
        for (int i = 1; i <= n; i++)
            scanf("%s", a[i] + 1);
        solve();
    }
    return 0;
}