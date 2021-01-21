#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 500;
constexpr int PMAX = NMAX * NMAX;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

constexpr int I0 = 0;
constexpr int I1 = 1;
constexpr int J0 = 2;
constexpr int J1 = 3;

int n, m, sx, sy, tx, ty;

int idx(int i, int j) {
    return (i - 1) * m + j;
}

i64 a[NMAX + 10][NMAX + 10];
i64 b[NMAX + 10][NMAX + 10];
i64 w[NMAX + 10][NMAX + 10][4];
i64 d[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &tx, &ty);
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
        scanf("%lld", &a[i][j]);
    }
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
        scanf("%lld", &b[i][j]);
    }

    memset(w, 0x3f, sizeof(w));

    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m - 1; j++) {
        int c;
        scanf("%d", &c);
        w[i][j][J1] = c;
        w[i][j + 1][J0] = c;
    }
    for (int i = 1; i <= n - 1; i++)
    for (int j = 1; j <= m; j++) {
        int c;
        scanf("%d", &c);
        w[i][j][I1] = c;
        w[i + 1][j][I0] = c;
    }
}

int main() {
    initialize();

    struct State {
        int x, y;
        i64 t;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    priority_queue<State> q; 

    auto chk = [&q](int x, int y, i64 t) {
        if (x < 1 || x > n || y < 1 || y > m)
            return;
        if (d[x][y] > t) {
            d[x][y] = t;
            q.push({x, y, t});
        }
    };

    memset(d, 0x3f, sizeof(d));
    d[sx][sy] = 0;
    q.push({sx, sy, 0});

    do {
        auto u = q.top();
        q.pop();

        if (u.t > d[u.x][u.y])
            continue;

        int x = u.x;
        int y = u.y;
        i64 t = u.t;
        i64 r = t % (a[x][y] + b[x][y]);
        i64 wi = r < a[x][y] ? 0 : a[x][y] + b[x][y] - r;
        i64 wj = a[x][y] <= r ? 0 : a[x][y] - r;

        chk(x + 1, y, t + wi + w[x][y][I1]);
        chk(x - 1, y, t + wi + w[x][y][I0]);
        chk(x, y + 1, t + wj + w[x][y][J1]);
        chk(x, y - 1, t + wj + w[x][y][J0]);
    } while (q.size());

    i64 ans = d[tx][ty];
    printf("%lld\n", ans);

    return 0;
}
