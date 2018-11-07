#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 600
#define BMAX (NMAX * 3 + 6)

typedef long long i64;

static int n, m;
static char map[NMAX + 10][NMAX + 10];
static int pre[3 * NMAX + 10][3 * NMAX + 10];

#define S(i, j) pre[NMAX + (i)][NMAX + (j)]


void show() {
    for (int i = 1; i <= n; i++)
        printf("%s\n", map[i] + 1);
    puts("");
}

void rotate() {
    static char buf[NMAX + 10][NMAX + 10];
    memcpy(buf, map, sizeof(buf));
    memset(map, 0, sizeof(map));
    for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++)
        map[i][j] = buf[n - j + 1][i];
    swap(n, m);
    // show();
}

i64 eval() {
    memset(pre, 0, sizeof(pre));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
        S(i, j) = map[i][j] == '#';
    for (int i = 0; i <= BMAX; i++) for (int j = 1; i >= j; j++)
        pre[i - j][j] += pre[i - j + 1][j - 1];

    i64 r = 0;
    for (int i = 1; i <= n + m; i++)
        for (int j = 0; i - j >= 1; j++) if (map[i - j][j + 1] == '#')
        for (int k = j + 1; i - k >= 1; k++) if (map[i - k][k + 1] == '#') {
            int d = (k - j) << 1;
            r += S(i - j - d, j + 1) - S(i - k, k - d + 1);
        }
    return r;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", map[i] + 1);

    i64 ans = eval();
    rotate();
    ans += eval();
    rotate();
    ans += eval();
    rotate();
    ans += eval();
    printf("%lld\n", ans);

    return 0;
}
