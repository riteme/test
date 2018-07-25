#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

#define NMAX 30

typedef long long int64;

static int n, m, q;
static bool map[NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int state;
            scanf("%d", &state);
            map[i][j] = !state;
        }  // for
    }      // for
}

struct Point {
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    int x, y;
};  // struct Point

static bool marked[NMAX + 10][NMAX + 10];
static int64 dist[NMAX + 10][NMAX + 10];

static void search(int sx, int sy, int tx, int ty) {
    memset(marked, 0, sizeof(marked));
    memset(dist, 0, sizeof(dist));

    queue<Point> q;
    q.push(Point(sx, sy));

    marked[sx][sy] = true;

    while (!q.empty()) {
        Point u = q.front();
        q.pop();

        if (u.x == tx && u.y == ty)
            break;

        const int dx[] = { 1, -1, 0, 0 };
        const int dy[] = { 0, 0, 1, -1 };
        for (size_t pos = 0; pos < 4; pos++) {
            Point v = Point(u.x + dx[pos], u.y + dy[pos]);

            if (marked[v.x][v.y] || map[v.x][v.y] || v.x < 1 || v.x > n ||
                v.y < 1 || v.y > m)
                continue;

            marked[v.x][v.y] = true;
            dist[v.x][v.y] = dist[u.x][u.y] + 1;

            q.push(v);
        }  // for
    }      // while
}

struct State {
    State(const Point &_position, const Point &_empty, const int64 &_dist)
            : position(_position), empty(_empty), dist(_dist) {}

    Point position;
    Point empty;
    int64 dist;
};  // struct State

static int64 length[NMAX + 10][NMAX + 10];
// static bool visited[NMAX + 10][NMAX + 10];

static int64 solve(int ex, int ey, int sx, int sy, int tx, int ty) {
    // memset(visited, 0, sizeof(visited));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            length[i][j] = LLONG_MAX;
        }  // for
    }      // for

    queue<State> q;
    q.push(State(Point(sx, sy), Point(ex, ey), 0));
    // visited[sx][sy] = true;
    length[sx][sy] = 0;

    while (!q.empty()) {
        State u = q.front();
        q.pop();

        if (u.dist < length[u.position.x][u.position.y])
            length[u.position.x][u.position.y] = u.dist;

        if (u.position.x == tx && u.position.y == ty)
            continue;

        const int dx[] = { 1, -1, 0, 0 };
        const int dy[] = { 0, 0, 1, -1 };
        for (size_t pos = 0; pos < 4; pos++) {
            Point v = Point(u.position.x + dx[pos], u.position.y + dy[pos]);

            if (/*visited[v.x][v.y] || */ map[v.x][v.y] || v.x < 1 || v.x > n ||
                v.y < 1 || v.y > m)
                continue;

            map[u.position.x][u.position.y] = true;
            search(u.empty.x, u.empty.y, v.x, v.y);
            map[u.position.x][u.position.y] = false;

            if (dist[v.x][v.y] == 0 && (v.x != u.empty.x || v.y != u.empty.y))
                continue;

            if (u.dist + dist[v.x][v.y] + 1 < length[v.x][v.y]) {
                // visited[v.x][v.y] = true;
                q.push(State(v, u.position, u.dist + dist[v.x][v.y] + 1));
            }
        }  // for
    }

    if (length[tx][ty] == LLONG_MAX)
        return -1;
    return length[tx][ty];
}

int main() {
    initialize();

    while (q--) {
        int ex, ey, sx, sy, tx, ty;
        scanf("%d%d%d%d%d%d", &ex, &ey, &sx, &sy, &tx, &ty);

        printf("%lld\n", solve(ex, ey, sx, sy, tx, ty));
    }  // while

    return 0;
}  // function main
