#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 10000
#define MMAX 1000
#define INFTY 1000000000

static int n, m, k;
static int X[NMAX + 10];
static int Y[NMAX + 10];
static int L[NMAX + 10];
static int R[NMAX + 10];
static int f[NMAX + 10][MMAX + 10];
static bool g[NMAX + 10][MMAX + 10];

static void initiailize() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        L[i] = -1;
        R[i] = -1;
        scanf("%d%d", X + i, Y + i);
    }  // for

    for (int i = 0; i < k; i++) {
        int p, l, r;
        scanf("%d%d%d", &p, &l, &r);

        L[p] = l;
        R[p] = r;
    }  // for
}

inline bool test(int i) {
    for (int j = 0; j < m; j++) {
        if (g[i][j])
            return true;
    }  // for

    return false;
}

int main() {
    initiailize();

    for (int i = 0; i < m; i++) {
        if (L[0] > 0 && L[i] < i && i < R[i])
            g[0][i] = true;
        else
            f[0][i] = INFTY;
    }  // for

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m - X[i]; j++)
            g[i][j + X[i]] |= g[i][j] | g[i - 1][j];
        for (int j = m - 1; j >= Y[i]; j--)
            g[i][j - Y[i]] |= g[i - 1][j];

        for (int j = 0; j < m; j++)
            f[i][j] = INFTY;

        for (int j = 0; j < m - X[i]; j++)
            f[i][j + X[i]] = min(f[i][j], f[i - 1][j] + 1);
        for (int j = m - 1; j >= Y[i]; j--)
            f[i][j - Y[i]] = min(f[i][j - Y[i]], f[i - 1][j]);

        for (int j = 0; j < m; j++)
            if (!g[i][j])
                f[i][j] = INFTY;
    }  // for

    int pos;
    for (pos = n - 1; pos >= 0; pos--)
        if (test(pos))
            break;

    if (pos == m - 1)
        printf("1\n%d\n", *min_element(&g[pos][0], &g[pos][m]));
    else
        printf("0\n%d\n", pos);

    return 0;
}  // function main
