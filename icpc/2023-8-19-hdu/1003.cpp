#include <cstdio>
#include <cassert>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 200;

int n;
int X, Y, R;
int B[NMAX + 10];
int f[NMAX + 10][NMAX * NMAX + 10];

void solve() {
    scanf("%d%d%d%d", &n, &X, &Y, &R);

    for (int i = 1; i <= n; i++) {
        scanf("%d", B + i);
    }

    for (int i = 0; i <= NMAX; i++) {
        for (int j = 0; j <= R; j++) {
            f[i][j] = -1;
        }
    }
    f[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= B[i]; j++) {
            for (int k = 0; k < R; k++) {
                if (j >= X && k >= X)
                    f[j][k] = max(f[j][k], f[j - X][k - X]);
                if (j >= Y && k >= Y)
                    f[j][k] = max(f[j][k], f[j - Y][k - Y]);
            }

            for (int k = R - 1; k >= 0; k--) {
                if (k + X < R && k + Y < R)
                    break;
                if (j >= X && k + X >= R)
                    f[j][R] = max(f[j][R], f[j - X][k]);
                if (j >= Y && k + Y >= R)
                    f[j][R] = max(f[j][R], f[j - Y][k]);
            }
        }

        for (int k = 0; k <= R; k++) {
            int mx = -1;
            for (int j = 0; j <= B[i]; j++) {
                if (f[j][k] >= 0)
                    mx = max(mx, f[j][k] + (B[i] - j) * (B[i] - j));
                f[j][k] = -1;
            }
            f[0][k] = mx;
            // printf("i=%d, k=%d, mx=%d\n", i, k, mx);
        }
    }

    printf("%d\n", f[0][R]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
