#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 10

static int n, m, C, D, mod;
static bool mat[NMAX + 10][NMAX + 10];

struct Path {
    Path(int _s, int _cnt)
        : s(_s), cnt(_cnt) {}

    int s, cnt;
};

static vector<Path> P;

void dfs(int x, int y, int s, int cnt) {
    if (x == n && y == m) {
        P.push_back(Path(s ^ (1 << ((n - 1) * m + m - 1)), cnt));
    } else if (x > n || y > m)
        return;
    else {
        dfs(x + 1, y, s | (1 << (x * m + y - 1)), cnt + mat[x + 1][y]);
        dfs(x, y + 1, s | (1 << ((x - 1) * m + y)), cnt + mat[x][y + 1]);
    }
}

void initialize() {
    memset(mat, 0, sizeof(mat));
    scanf("%d%d%d%d%d", &n, &m, &C, &D, &mod);

    for (int i = 0; i < C; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        mat[x][y] = true;
    }
}

int main() {
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdout);
    int T;
    scanf("%d", &T);

    while (T--) {
        initialize();
        P.clear();
        dfs(1, 1, 0, 0);

        int ans = 0;
        for (int i = 0; i < P.size(); i++) {
            for (int j = i + 1; j < P.size(); j++) {
                Path &u = P[i], &v = P[j];

                if ((u.s & v.s) || u.cnt + v.cnt > D)
                    continue;
                ans++;
                if (ans == mod)
                    ans = 0;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
