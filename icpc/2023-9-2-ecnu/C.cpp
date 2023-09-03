#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 5000;
constexpr int MMAX = 10;
constexpr int SMAX = 1 << MMAX;
constexpr int MOD = 998244353;

int n, m;
int f[NMAX + 10][MMAX + 1][SMAX];

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    f[1][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int S = 0; S < (1 << m); S++) {
                if (j == m) {
                    add(f[i + 1][0][S], f[i][j][S]);
                } else {
                    if (((S >> j) & 1) == 1)
                        add(f[i][j + 1][S & ~(1 << j)], f[i][j][S]);
                    if (((S >> j) & 1) == 0)
                        add(f[i][j + 1][S | (1 << j)], f[i][j][S]);
                    if (j + 1 < m && ((S >> j) & 1) == 0 && ((S >> (j + 1)) & 1) == 0) {
                        add(f[i][j + 2][S & ~(3 << j)], f[i][j][S]);
                        add(f[i][j + 2][S | (3 << j)], f[i][j][S]);
                    }
                }
            }
        }
    }

    printf("%d\n", f[n][m][0]);
    return 0;
}
