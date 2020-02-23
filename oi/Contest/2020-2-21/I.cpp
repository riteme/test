#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

int n, m;
char w[NMAX + 10][NMAX + 10];
bool mark[NMAX + 10][NMAX + 10];
int dp[NMAX + 10][NMAX + 10];

int dfs(int x, int y) {
    if (dp[x][y]) return dp[x][y];
    if (mark[x][y]) {
        dp[x][y] = -1;
        return dp[x][y];
    }
    mark[x][y] = true;

    int tx = x, ty = y;
    if (w[x][y] == 'W') tx--;
    else if (w[x][y] == 'S') tx++;
    else if (w[x][y] == 'A') ty--;
    else ty++;

    dp[x][y] = dfs(tx, ty);
    return dp[x][y];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", w[i] + 1);

    for (int i = 0; i <= n + 1; i++)
        dp[i][0] = dp[i][m + 1] = 1;
    for (int i = 0; i <= m + 1; i++)
        dp[0][i] = dp[n + 1][i] = 1;

    int ans = 0;
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
        ans += dfs(i, j) == 1;
        // if (dp[i][j] == 1)
        //     printf("%d %d\n", i, j);
    }

    printf("%d\n", ans);
    return 0;
}