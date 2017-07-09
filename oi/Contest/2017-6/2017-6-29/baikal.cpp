#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 500
#define INF 1e50

typedef long double f128;

static int n;
static f128 A[NMAX + 10], B[NMAX + 10];
static f128 D[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%Lf", A + i);
        B[i] = A[i] + B[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            D[i][j] = (A[i] - A[j]) * B[i] * B[j] / 2 / A[i] / A[j];
        }
    }
}

int main() {
    freopen("baikal.in", "r", stdin);
    freopen("baikal.out", "w", stdout);
    initialize();

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                D[i][j] = max(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    f128 ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, D[i][i]);
    }

    printf("%.5Lf\n", ans);

    return 0;
}
