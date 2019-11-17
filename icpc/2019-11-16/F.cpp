#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100

static int n;
static char A[NMAX + 10][NMAX + 10];
static char S[(NMAX + 10) * (NMAX + 10)];
static char B[NMAX + 10][NMAX + 10];
static bool v[NMAX + 10][NMAX + 10];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++)
            scanf("%s", A[i] + 1);

        int m = 0;
        for (int i = 1; i <= 2 * n - 1; i++) {
            int x = i & 1 ? min(n, i) : max(1, i - n + 1);
            int y = i - x + 1;
            int dx = i & 1 ? -1 : 1;
            int dy = i & 1 ? 1 : -1;
            for (int c = 0; c < min(i, 2 * n - i); c++, x += dx, y += dy)
                S[++m] = A[x][y];
        }

        //S[m + 1] = 0;
        //puts(S + 1);
        memset(v, 0, sizeof(v));
        int d[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int x = 1, y = 0, p = 0;
        for (int i = 1; i <= m; i++) {
            int tx = x + d[p][0], ty = y + d[p][1];
            if (tx < 1 || tx > n ||
                ty < 1 || ty > n ||
                v[tx][ty]) {
                i--;
                p = (p + 1) % 4;
            } else {
                x = tx;
                y = ty;
                B[x][y] = S[i];
                v[x][y] = true;
            }
        }

        for (int i = 1; i <= n; i++) {
            B[i][n + 1] = 0;
            puts(B[i] + 1);
        }
    }
    return 0;
}
