#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000

static char mat[NMAX + 10][NMAX + 10];
static bool mark[NMAX + 10][NMAX + 10];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", mat[i] + 1);
    struct Point {
        int x, y, s = 0;
    };
    queue<Point> q;
    for (int x = 1; x <= n; x++) for (int y = 1; y <= m; y++) if (mat[x][y] == '#') {
        q.push({x, y});
        mark[x][y] = true;
    }
    int ans;
    while (!q.empty()) {
        auto u = q.front();
        ans = u.s;
        q.pop();
        constexpr int dx[] = {-1, 1, 0, 0};
        constexpr int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int tx = u.x + dx[i], ty = u.y + dy[i];
            if (1 <= tx && tx <= n && 1 <= ty && ty <= m && !mark[tx][ty]) {
                mark[tx][ty] = true;
                q.push({tx, ty, u.s + 1});
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}

