#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define BASE 0x19260817

typedef unsigned long long u64;

int n;
int f[NMAX + 10][NMAX + 10];
//int len[NMAX + 10][NMAX + 10];
char a[NMAX + 10][NMAX + 10];
u64 pw[NMAX + 10];
u64 h[2][NMAX + 10][NMAX + 10];

int idx(int x, int y) {
    return min(n - x + 1, y);
}

void _main() {
    for (int i = 1; i <= n; i++) {
        //memset(mx[i] + 1, 0, sizeof(int) * n);
        scanf("%s", a[i] + 1);

        h[0][i][0] = 0;
        for (int j = 1; j <= n; j++) {
            h[0][i][j] = h[0][i][j - 1] * BASE + a[i][j];
        }
    }

    for (int j = 1; j <= n; j++) {
        h[1][n + 1][j] = 0;
        for (int i = n; i >= 1; i--) {
            h[1][i][j] = h[1][i + 1][j] * BASE + a[i][j];
        }
    }

    int ans = 1;
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        //mx[i][j] = max(mx[i][j], mx[i + 1][j - 1]);
        //ans = max(ans, idx(i, j) - mx[i][j]);

        int l = 1, r = min(i, n - j + 1);
        while (l < r) {
            int m = (l + r) / 2 + 1;
            u64 h0 = h[0][i][j + m - 1] - pw[m] * h[0][i][j - 1];
            u64 h1 = h[1][i - m + 1][j] - pw[m] * h[1][i + 1][j];
            if (h0 == h1)
                l = m;
            else
                r = m - 1;
        }

        //len[i][j] = l;
        //int x = i - l, y = j + l;
        //mx[x][y] = max(mx[x][y], idx(i, j));
        f[i][j] = min(f[i - 1][j + 1] + 1, l);
        ans = max(ans, f[i][j]);
    }

    printf("%d\n", ans);
}

int main() {
    pw[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        pw[i] = pw[i - 1] * BASE;
    }

    while (scanf("%d", &n) != EOF) {
        if (n == 0)
            break;
        _main();
    }
    return 0;
}
