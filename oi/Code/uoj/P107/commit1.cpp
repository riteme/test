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

struct Point {
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    int x, y;

    bool empty() {
        return x == 0 && y == 0;
    }

    explicit operator bool() const {
        return x > 0 && y > 0;
    }
};  // struct Point

static int n, w, h;
static char G[NMAX + 10][NMAX + 10];
static Point toward[4][NMAX + 10][NMAX + 10];
static int f[10][10][NMAX + 10][NMAX + 10];
static bool used[10][10];
static int mark;
static bool marked[4][NMAX + 10][NMAX + 10];

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
                f[d][d][x][y] = 0;
                G[x][y] = '.';
            }
        }  // for
    }      // for

    for (int x = 1; x <= h; x++) {
        for (int y = 1; y <= w; y++) {
            for (int d = 0; d < 4; d++) {
                mark++;
                walk(d, x, y);
            }  // for
        }      // for
    }          // for
}

typedef pair<Point, int> State;

struct Compare {
    bool operator()(const State &a, const State &b) const {
        return a.second < b.second;
    }
};  // struct Compare

int main() {
    initialize();

    while (true) {
        for (int l = 0; l < 10; l++) {
            for (int r = 0; r < 10; r++) {
                for (int m = l; m < r; m++) {
                    for (int x = 1; x <= h; x++) {
                        for (int y = 1; y <= w; y++) {
                            f[l][r][x][y] =
                                min(f[l][r][x][y],
                                    f[l][m][x][y] + f[m + 1][r][x][y]);
                        }  // for
                    }      // for
                }          // for
            }              // for
        }                  // for

        if (used[0][n - 1])
            break;

        bool flag = true;
        for (int l = 0; l < 10; l++) {
            for (int r = 0; r < 10; r++) {
                if (used[l][r])
                    continue;

                int *dp = &f[l][r][0][0];
                priority_queue<State, vector<State>, Compare> q;
                for (int x = 1; x <= h; x++) {
                    for (int y = 1; y <= w; y++) {
                        if (dp[x * PINCH + y] < INFTY)
                            q.push(make_pair(Point(x, y), dp[x * PINCH + y]));
                    }  // for
                }      // for

                if (q.empty())
                    continue;

                flag = false;
                used[l][r] = true;
                while (!q.empty()) {
                    State u = q.top();
                    q.pop();

                    int x = u.first.x, y = u.first.y;
                    int v = u.second;
                    if (v > dp[x * PINCH + y])
                        continue;

                    for (int d = 0; d < 4; d++) {
                        Point p = toward[d][x][y];
                        assert(!p.empty());

                        if (!p)
                            continue;

                        if (v + 1 < dp[p.x * PINCH + p.y]) {
                            dp[p.x * PINCH + p.y] = v + 1;
                            q.push(make_pair(p, v + 1));
                        }
                    }  // for
                }      // while
            }          // for
        }              // for

        if (flag)
            break;
    }  // while

    int answer = INFTY;
    for (int x = 1; x <= h; x++) {
        for (int y = 1; y <= w; y++) {
            answer = min(answer, f[0][n - 1][x][y]);
        }  // for
    }      // for

    if (answer == INFTY)
        printf("-1\n");
    else
        printf("%d\n", answer);

    return 0;
}  // function main
