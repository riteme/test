#define NDEBUG

#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

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

struct Array2D {
    int *operator[](int x) {
        return &data[x][0];
    }

    int data[NMAX + 10][NMAX + 10];
};  // struct Array2D

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

template <typename T>
class Queue {
 public:
    Queue() : head(0), tail(0) {}

    void push(const T &v) {
        vec[tail++] = v;
    }

    void pop() {
        head++;
    }

    T &front() {
        return vec[head];
    }

    T *begin() {
        return vec + head;
    }

    T *end() {
        return vec + tail;
    }

    void reset() {
        head = tail = 0;
    }

    size_t size() const {
        return tail - head;
    }

    bool empty() const {
        return tail == head;
    }

 private:
    size_t head, tail;
    T vec[NMAX * NMAX + 10];
};  // class Queue

static int n, w, h;
static char G[NMAX + 10][NMAX + 10];
static int mark;
static Point toward[4][NMAX + 10][NMAX + 10];
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

static Array2D f[10][10];
static bool visited[NMAX + 10][NMAX + 10];
static Queue<Point> q1, q2;

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

    for (int d = 0; d < 4; d++) {
        for (int x = 1; x <= h; x++) {
            for (int y = 1; y <= w; y++) {
                mark++;
                walk(d, x, y);
            }  // for
        }      // for
    }          // for
}

void process(int l, int r, Array2D &dp) {
    q1.reset();
    q2.reset();
    memset(visited, 0, sizeof(visited));

    for (int x = 1; x <= h; x++) {
        for (int y = 1; y <= w; y++) {
            if (dp[x][y] < INFTY)
                q1.push({x, y});
        }  // for
    }      // for

    sort(q1.begin(), q1.end(), [&dp](const Point &a, const Point &b) {
        return dp[a.x][a.y] < dp[b.x][b.y];
    });

    while (!q1.empty() || !q2.empty()) {
        Point u;
        if (q1.empty()) {
            u = q2.front();
            q2.pop();
        } else if (q2.empty()) {
            u = q1.front();
            q1.pop();
        } else {
            Point a = q1.front();
            Point b = q2.front();

            if (dp[a.x][a.y] < dp[b.x][b.y]) {
                u = a;
                q1.pop();
            } else {
                u = b;
                q2.pop();
            }
        }

        visited[u.x][u.y] = true;

        int dist = dp[u.x][u.y] + 1;
        for (int d = 0; d < 4; d++) {
            Point p = toward[d][u.x][u.y];

            // if (!p)
            // continue;

            if (!visited[p.x][p.y] && dist < dp[p.x][p.y]) {
                visited[p.x][p.y] = true;
                dp[p.x][p.y] = dist;
                q2.push(p);
            }
        }  // for
    }      // while
}

int main() {
    // freopen("robot.in", "r", stdin);
    // freopen("robot.out", "w", stdout);
    initialize();

    for (int len = 0; len < n; len++) {
        for (int l = 0; l < n - len; l++) {
            int r = l + len;
            for (int m = l; m < r; m++) {
                for (int x = 1; x <= h; x++) {
                    for (int y = 1; y <= w; y++) {
                        f[l][r][x][y] = min(f[l][r][x][y],
                                            f[l][m][x][y] + f[m + 1][r][x][y]);
                    }  // for
                }      // for
            }          // for

            process(l, r, f[l][r]);
        }  // for
    }      // for

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
