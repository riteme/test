#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 50
#define QMAX 100000

enum Direction {
    UNKNOWN, DOWN, RIGHT
};

static int n, m, q;
static char buf[NMAX + 10];
static Direction type[NMAX + 10][NMAX + 10];
static struct {
    int x, y;
} op[QMAX + 10];

void read() {
    memset(type, 0, sizeof(type));

    for (int i = 1; i <= n; i++) {
        scanf("%s", buf + 1);

        for (int j = 1; j <= m; j++) {
            if (buf[j] == 'L')
                type[i][j] = RIGHT;
            else if (buf[j] == 'U')
                type[i][j] = DOWN;
        }
    }
}

void rotate(int x, int y) {
    op[++q] = {x, y};

    if (type[x][y] == RIGHT) {
        type[x][y] = type[x][y + 1] = DOWN;
        type[x + 1][y] = UNKNOWN;
    } else if (type[x][y] == DOWN) {
        type[x][y] = type[x + 1][y] = RIGHT;
        type[x][y + 1] = UNKNOWN;
    }
}

void require(int x, int y, Direction d) {
    if (type[x][y] == d)
        return;

    if (d == RIGHT) {
        if (type[x][y + 1] != DOWN)
            require(x, y + 1, DOWN);
    } else {
        if (type[x + 1][y] != RIGHT)
            require(x + 1, y, RIGHT);
    }

    rotate(x, y);
}

void solve() {
    read();

    if (m & 1) {
        for (int j = 1; j <= m; j++) {
            for (int i = 1; i <= n; i += 2) {
                require(i, j, DOWN);
            }
        }
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j += 2) {
                require(i, j, RIGHT);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    solve();
    int head = q + 1;
    solve();
    reverse(op + head, op + q + 1);

    printf("%d\n", q);
    for (int i = 1; i <= q; i++) {
        printf("%d %d\n", op[i].x, op[i].y);
    }

    return 0;
}
