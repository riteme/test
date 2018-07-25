#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <bitset>
#include <algorithm>

using namespace std;

#define NMAX 200

struct Bitset2D {
    typedef bitset<NMAX * NMAX> Bitset;

    void reset() {
        bits.reset();
    }

    Bitset::reference operator()(const int x, const int y) {
        return bits[(x - 1) * NMAX + y - 1];
    }

    Bitset bits;
};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Graph {
    struct Point {
        Point(int _x, int _y) : x(_x), y(_y) {}

        int x, y;
    };

    void bfs(int x, int y) {
        queue<Point> q;
        q.push(Point(x, y));

        while (!q.empty()) {
            Point u = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int tx = u.x + dx[i];
                int ty = u.y + dy[i];

                if (!test(tx, ty) || mark(tx, ty))
                    continue;

                mark(tx, ty) = true;
                q.push(Point(tx, ty));
            }
        }
    }

    void eval() {
        mark.reset();
        ans = 0;
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                if (!mark(x, y) && mat(x, y)) {
                    ans++;
                    bfs(x, y);
                }
            }
        }
    }

    void add(int x, int y) {
        ans += delta(x, y);
        mat(x, y) = true;
    }

    void del(int x, int y) {
        mat(x, y) =  false;
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
            mark.reset();
            for (int i = 0; i < 4; i++) {
                int tx = x + dx[i];
                int ty = y + dy[i];

                if (test(tx, ty) && !mark(tx, ty)) {
                    ret--;
                    bfs(tx, ty);
                }
            }
        }

        return ret;
    }

    bool test(int x, int y) {
        return 1 <= x && x <= n && 1 <= y && y <= m && mat(x, y);
    }

    int n, m, ans;
    Bitset2D mat, mark;
};

static int n, m, q, lastans;
static char mat[NMAX + 10][NMAX + 10];
static Graph black, white;

void initialize() {
    scanf("%d%d%d", &n, &m, &q);
    black.n = white.n = n;
    black.m = white.m = m;

    for (int i = 1; i <= n; i++) {
        scanf("%s", mat[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (mat[i][j] == '1')
                black.mat(i, j) = true;
            else
                white.mat(i, j) = true;
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
