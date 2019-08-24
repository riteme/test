/**
 * 依然有个问题，为什么
 * { I, f, f^-1, g, g^-1, ...}
 * 是置换群？
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define CMAX 20
#define NMAX 60
#define MMAX 60

static int n, m, Sr, Sb, Sg, P;
static int perm[MMAX + 10][NMAX + 10];
static int cnt;
static int len[NMAX + 10];
static bool marked[NMAX + 10];
static int f[CMAX + 10][CMAX + 10][CMAX + 10];

static int dp() {
    memset(f, 0, sizeof(f));

    f[0][0][0] = 1;
    for (int i = 1; i <= cnt; i++) {
        int l = len[i];

        for (int r = Sr; r >= 0; r--) {
            for (int b = Sb; b >= 0; b--) {
                for (int g = Sg; g >= 0; g--) {
                    if (r >= l)
                        f[r][b][g] += f[r - l][b][g];
                    if (b >= l)
                        f[r][b][g] += f[r][b - l][g];
                    if (g >= l)
                        f[r][b][g] += f[r][b][g - l];

                    f[r][b][g] %= P;
                }
            }
        }
    }

    return f[Sr][Sb][Sg];
}

static int dfs(int x, int *p) {
    if (marked[x])
        return 0;

    marked[x] = true;
    return dfs(p[x], p) + 1;
}

static int evaluate(int x) {
    memset(marked, 0, sizeof(marked));
    cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (!marked[i]) {
            len[++cnt] = dfs(i, &perm[x][0]);
        }
    }

    return dp();
}

static void initialize() {
    scanf("%d%d%d%d%d", &Sr, &Sb, &Sg, &m, &P);
    n = Sr + Sb + Sg;

    for (int i = 1; i <= n; i++) {
        perm[0][i] = i;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &perm[i][j]);
        }
    }
}

inline int quick_pow(int a, int b, int m) {
    int r = 1;

    while (b) {
        if (b & 1)
            r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }

    return r;
}

inline int inv(int x, int p) {
    return quick_pow(x, p - 2, p);
}

int main() {
    initialize();
    
    int sum = 0;
    for (int i = 0; i <= m; i++) {
        sum += evaluate(i);
        sum %= P;
    }

    printf("%d\n", sum * inv(m + 1, P) % P);

    return 0;
}
