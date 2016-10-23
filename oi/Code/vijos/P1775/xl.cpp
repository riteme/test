#include <cstdio>
#include <cstring>

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

#define NMAX 350
#define MMAX 40

static int n, m;
static int score[NMAX + 10];
static int cnt[10];
static int f[MMAX + 1][MMAX + 1][MMAX + 1][MMAX + 1];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", score + i);
    }  // for

    for (int i = 0; i < m; i++) {
        int id;
        scanf("%d", &id);

        cnt[id]++;
    }  // for
}

static int dfs(int a, int b, int c, int d) {
    if (a < 0 || b < 0 || c < 0 || d < 0)
        return 0;

    if (f[a][b][c][d])
        return f[a][b][c][d];
    else {
        int pos = a + 2 * b + 3 * c + 4 * d + 1;
        int result = max(max(dfs(a - 1, b, c, d), dfs(a, b - 1, c, d)),
                         max(dfs(a, b, c - 1, d), dfs(a, b, c, d - 1)));

        f[a][b][c][d] = result + score[pos];
        return result + score[pos];
    }
}

int main() {
    initialize();

    f[0][0][0][0] = score[1];
    printf("%d\n", dfs(cnt[1], cnt[2], cnt[3], cnt[4]));

    return 0;
}  // function main
