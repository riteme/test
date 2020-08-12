#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 30
#define MMAX 8
#define SMAX (1 << (2 * MMAX))

int n, m;
char a[NMAX + 10][MMAX + 10];
int f[NMAX + 10][SMAX];
int g[NMAX + 10][SMAX];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", a[i]);
    }

    for (int i = 0; i <= n; i++)
    for (int S = 0; S < SMAX; S++) {
        f[i][S] = -1;
    }
    f[0][0] = 0;

    int mask = (1 << m) - 1;
    for (int i = 1; i <= n; i++)
    for (int W = 0; W <= mask; W++) {
        int V = 0;
        for (int j = 0; j < m; j++) {
            if (a[i - 1][j] != '#' && ((W >> j) & 1)) {
                V |= 1 << j;
                if (j > 0)
                    V |= 1 << (j - 1);
                if (j < m - 1)
                    V |= 1 << (j + 1);
            }
        }

        int _R = (~V) & mask;
        for (int R = _R; true; R = (R - 1) & _R) {
            int S = (R << m) | W;
            if (f[i - 1][S] < 0) {
                if (R == 0)
                    break;
                else
                    continue;
            }

            for (int nW = 0; nW <= mask; nW++)
            if ((nW & R) == R) {
                bool ok = true;
                for (int j = 0; j < m; j++) {
                    if ((R >> j) & 1)
                        ok &= a[i][j] != '#';
                }

                if (!ok)
                    continue;

                int M = 0, cnt = 0;
                for (int j = 0; j < m; j++) {
                    if (a[i - 1][j] != '#' && ((W >> j) & 1)) {
                        M |= 1 << j;
                    }
                    if (a[i][j] != '#') {
                        if ((nW >> j) & 1) {
                            M |= 1 << j;
                            if (j > 0)
                                M |= 1 << (j - 1);
                            if (j < m - 1)
                                M |= 1 << (j + 1);
                        } else {
                            cnt++;
                        }
                    }
                }

                int nR = 0;
                for (int j = 0; j < m; j++) {
                    if (a[i][j] != '#' && !((M >> j) & 1))
                        nR |= 1 << j;
                }

                int T = (nR << m) | nW;
                int nv = f[i - 1][S] + cnt;
                if (nv > f[i][T]) {
                    f[i][T] = nv;
                    g[i][T] = S;
                }
            }

            if (R == 0)
                break;
        }
    }

    int maxv = -1, T;
    for (int S = 0; S <= mask; S++) {
        if (f[n][S] > maxv) {
            maxv = f[n][S];
            T = S;
        }
    }

    for (int i = n; i >= 1; i--) {
        //printf("%d\n", T);
        for (int j = 0; j < m; j++)
        if (a[i][j] != '#') {
            a[i][j] = ((T >> j) & 1) ? 'O' : 'X';
        }
        T = g[i][T];
    }

    for (int i = 1; i <= n; i++) {
        puts(a[i]);
    }

    return 0;
}
