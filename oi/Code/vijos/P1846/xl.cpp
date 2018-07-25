#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 30
#define INFTY 1000000000

struct Point {
    Point(int _x, int _y)
        : x(_x), y(_y) {}

    int x, y;
};

struct State {
    State(int _len, const Point &_p, const Point &_w)
        : len(_len), pos(_p), white(_w) {}

    int len;
    Point pos;
    Point white;
};

static int n, m, q;
static bool rock[NMAX + 10][NMAX + 10];
static int dist[NMAX + 10][NMAX + 10][4][NMAX + 10][NMAX + 10];
static bool marked[NMAX + 10][NMAX + 10];

static void bfs(int x, int y, int arr[][NMAX + 10]) {
    memset(marked, 0, sizeof(marked));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            arr[i][j] = INFTY;

            if (rock[i][j])
                marked[i][j] = true;
        }
    }

    if (x < 1 || x > n || y < 1 || y > m || marked[x][y])
        return;

    queue<Point> q;
    marked[x][y] = true;
    arr[x][y] = 0;
    q.push(Point(x, y));
    while (!q.empty()) {
        Point u = q.front();
        q.pop();

        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        for (size_t pos = 0; pos < 4; pos++) {
            int tx = u.x + dx[pos];
            int ty = u.y + dy[pos];

            if (1 <= tx && tx <= n && 1 <= ty && ty <= m &&
                !marked[tx][ty]) {
                marked[tx][ty] = true;
                arr[tx][ty] = arr[u.x][u.y] + 1;
                q.push(Point(tx, ty));
            }
        }
    }
}

static int len[NMAX + 10][NMAX + 10];

static void spfa(int ex, int ey, int sx, int sy) {
    memset(marked, 0, sizeof(marked));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            len[i][j] = INFTY;

    if (rock[sx][sy])
        return;

    queue<State> q;
    len[sx][sy] = 0;
    q.push(State(0, Point(sx, sy), Point(ex, ey)));
    while (!q.empty()) {
        State u = q.front();
        marked[u.pos.x][u.pos.y] = true;
        q.pop();

        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        for (size_t pos = 0; pos < 4; pos++) {
            int cx = u.pos.x + dx[pos];
            int cy = u.pos.y + dy[pos];
            int dis = dist[u.pos.x][u.pos.y][pos][u.white.x][u.white.y];

            if (marked[cx][cy])
                continue;
            if (dis >= INFTY)
                continue;

            if (u.len + dis + 1 <= len[cx][cy]) {
                len[cx][cy] = u.len + dis + 1; 

                q.push(State(len[cx][cy], Point(cx, cy), u.pos));
            }
        }
    }
}

static void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);

            rock[i][j] = !x;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!rock[i][j]) {
                rock[i][j] = true;

                bfs(i - 1, j, &dist[i][j][0][0]);
                bfs(i + 1, j, &dist[i][j][1][0]);
                bfs(i, j - 1, &dist[i][j][2][0]);
                bfs(i, j + 1, &dist[i][j][3][0]);

                rock[i][j] = false;
            }
        }
    }
}

int main() {
    initialize();

    while (q--) {
        int ex, ey, sx, sy, tx, ty;
        scanf("%d%d%d%d%d%d", &ex, &ey, &sx, &sy, &tx, &ty);

        spfa(ex, ey, sx, sy);
        if (len[tx][ty] >= INFTY)
            puts("-1");
        else
            printf("%d\n", len[tx][ty]);
    }
}
