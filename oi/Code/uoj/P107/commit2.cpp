// #define NDEBUG

#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

#define NMAX 500
#define PINCH (NMAX + 10)
#define INFTY 0x3f3f3f3f

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define CW 0
#define CCW 1

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

static int n, w, h;

struct State {
    void update() {
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                for (int m = l; m < r; m++) {
                    data[l][r] = min(data[l][r], data[l][m] + data[m + 1][r]);
                }  // for
            }      // for
        }          // for
    }

    int *operator[](int x) {
        return &data[x][0];
    }

    int data[10][10];
};  // struct State

struct Point {
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    int x, y;

    bool empty() {
        return x == 0 && y == 0;
    }

    bool operator==(const Point &b) const {
        return x == b.x && y == b.y;
    }

    explicit operator bool() const {
        return x > 0 && y > 0;
    }
};  // struct Point

static char G[NMAX + 10][NMAX + 10];
static Point toward[4][NMAX + 10][NMAX + 10];
static State f[NMAX + 10][NMAX + 10];
static bool exist[NMAX + 10][NMAX + 10];
static int mark;
static int marked[4][NMAX + 10][NMAX + 10];

inline int rotate(int d, int c) {
    if (c == CW) {
        switch (d) {
            case UP: return RIGHT;
            case RIGHT: return DOWN;
            case DOWN: return LEFT;
            case LEFT: return UP;
        }  // switch to d
    } else {
        switch (d) {
            case UP: return LEFT;
            case LEFT: return DOWN;
            case DOWN: return RIGHT;
            case RIGHT: return UP;
        }  // switch to d
    }

    return 5;
}

Point walk(int d, int x, int y) {
    marked[d][x][y] = mark;

    if (G[x][y] == 'A')
        d = rotate(d, CCW);
    else if (G[x][y] == 'C')
        d = rotate(d, CW);

    if (toward[d][x][y].empty()) {
        int tx = x + dx[d], ty = y + dy[d];

        if (tx < 1 || tx > h || ty < 1 || ty > w || G[tx][ty] == 'x')
            toward[d][x][y] = {x, y};
        else if (marked[d][tx][ty] == mark)
            toward[d][x][y] = {-1, -1};
        else
            toward[d][x][y] = walk(d, tx, ty);
    } else
        return toward[d][x][y];
    return toward[d][x][y];
}

void initialize() {
    scanf("%d%d%d", &n, &w, &h);

    memset(f, 0x3f, sizeof(f));
    for (int x = 1; x <= h; x++) {
        scanf("%s", &G[x][1]);

        for (int y = 1; y <= w; y++) {
            if (isdigit(G[x][y])) {
                int d = G[x][y] - '1';
                f[x][y][d][d] = 0;
                G[x][y] = '.';
            }
        }  // for
    }      // for

    for (int d = 0; d < 4; d++) {
        for (int x = 1; x <= h; x++) {
            for (int y = 1; y <= w; y++) {
                mark++;
                walk(d, x, y);
            }  // for
        }      // for
    }          // for
}

int main() {
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
    initialize();

    queue<Point> q;
    for (int d = 0; d < n; d++) {
        for (int x = 1; x <= h; x++) {
            for (int y = 1; y <= w; y++) {
                if (f[x][y][d][d] == 0) {
                    q.push({x, y});
                    exist[x][y] = true;
                }
            }  // for
        }      // for
    }          // for

    while (!q.empty()) {
        Point u = q.front();
        q.pop();

        exist[u.x][u.y] = false;
        State &s = f[u.x][u.y];
        s.update();
        for (int d = 0; d < 4; d++) {
            Point v = toward[d][u.x][u.y];
            assert(!v.empty());

            if (!v || u == v)
                continue;

            bool flag = false;
            State &t = f[v.x][v.y];
            for (int l = 0; l < n; l++) {
                for (int r = l; r < n; r++) {
                    if (s[l][r] + 1 < t[l][r]) {
                        flag = true;
                        t[l][r] = s[l][r] + 1;
                    }
                }  // for
            }      // for

            if (flag && !exist[v.x][v.y]) {
                q.push(v);
            }
        }  // for
    }      // while

    int answer = INFTY;
    for (int x = 1; x <= h; x++) {
        for (int y = 1; y <= w; y++) {
            answer = min(answer, f[x][y][0][n - 1]);
        }  // for
    }      // for

    if (answer == INFTY)
        printf("-1\n");
    else
        printf("%d\n", answer);

    return 0;
}  // function main
