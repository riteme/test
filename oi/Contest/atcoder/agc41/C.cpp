#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define CMAX 100000

static int c;
static int m[NMAX + 10][NMAX + 10];

bool solve(int n) {
    int p = n / 2;
    if (n <= 2)
        return false;
    else if (n & 1) {
        if (n == 3) {
            m[1][1] = m[2][1] = ++c;
            m[3][2] = m[3][3] = ++c;
        } else {
            for (int i = 3; i < n; i++) {
                m[i - 1][i] = m[i - 1][i + 1] = ++c;
                m[i][i] = m[i + 1][i] = ++c;
            }
            m[1][1] = m[2][1] = ++c;
            m[1][2] = m[1][3] = ++c;
            m[3][1] = m[3][2] = ++c;
            m[1][n] = m[2][n] = ++c;
            m[n][1] = m[n][2] = ++c;
            m[n - 1][n] = m[n][n] = ++c;
        }
    } else {
        if (n == 4) {
            m[1][1] = m[1][2] = ++c;
            m[2][1] = m[2][2] = ++c;
            m[3][3] = m[3][4] = ++c;
            m[4][3] = m[4][4] = ++c;
            m[1][3] = m[2][3] = ++c;
            m[1][4] = m[2][4] = ++c;
            m[3][1] = m[4][1] = ++c;
            m[3][2] = m[4][2] = ++c;
        } else {
            if (!solve(n / 2))
                return false;
            for (int i = 1; i <= p; i++)
            for (int j = 1; j <= p; j++)
                m[p + i][p + j] = m[i][j] ? m[i][j] + c : 0;
            c *= 2;
        }
    }
    return true;
}

static vector<int> G[CMAX + 10];
static bool mark[100];
static char z[CMAX + 10];

int main() {
    int n;
    scanf("%d", &n);
    if (solve(n)) {
        for (int x = 1; x <= n; x++)
        for (int y = 1; y <= n; y++) {
            constexpr int dx[] = {-1, 1, 0, 0};
            constexpr int dy[] = {0, 0, -1, 1};
            for (int i = 0; i < 4; i++) {
                int tx = x + dx[i];
                int ty = y + dy[i];
                if (1 <= tx && tx <= n &&
                    1 <= ty && ty <= n &&
                    m[x][y] != m[tx][ty])
                    G[m[x][y]].push_back(m[tx][ty]);
            }
        }

        for (int u = 1; u <= c; u++) {
            for (int v : G[u])
                mark[z[v]] = true;
            for (z[u] = 1; mark[z[u]]; z[u]++) ;
            for (int v : G[u])
                mark[z[v]] = false;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                putchar(m[i][j] ? 'a' + z[m[i][j]] - 1 : '.');
            putchar('\n');
        }
    } else puts("-1");
    return 0;
}
