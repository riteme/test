#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

#define NMAX 10
#define EPSILON 0.00001

inline bool almost_equal(const double a, const double b) {
    return fabs(a - b) < EPSILON;
}

static int n;
static double P[NMAX + 10][NMAX + 10];
static double A[NMAX + 10][NMAX + 10];
static double x[NMAX + 10];
static double y[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lf", &P[i][j]);
        }  // for

        if (i > 1) {
            for (int j = 1; j <= n; j++) {
                A[i - 1][j] = -2.0 * P[i - 1][j] + 2.0 * P[i][j];
                x[i - 1] += -P[i - 1][j] * P[i - 1][j] + P[i][j] * P[i][j];
            }  // for
        }
    }  // for
}

static void gauss() {
    for (int i = 1; i <= n; i++) {
        int pos = i;
        for (int j = i + 1; j <= n; j++) {
            if (fabs(A[j][i]) > fabs(A[pos][i]))
                pos = j;
        }  // for

        if (pos != i) {
            for (int j = i; j <= n; j++) {
                swap(A[pos][j], A[i][j]);
            }  // for
            swap(x[pos], x[i]);
        }

        for (int j = i + 1; j <= n; j++) {
            double ratio = A[j][i] / A[i][i];

            for (int k = i; k <= n; k++) {
                A[j][k] -= ratio * A[i][k];
            }  // for

            x[j] -= ratio * x[i];
        }  // for
    }      // for

    for (int i = n; i >= 1; i--) {
        y[i] = x[i] / A[i][i];

        for (int j = i - 1; j >= 1; j--) {
            x[j] -= A[j][i] * y[i];
        }  // for
    }      // for
}

int main() {
    freopen("bzoj_1013.in", "r", stdin);
    freopen("bzoj_1013.out", "w", stdout);

    initialize();
    gauss();

    for (int i = 1; i <= n; i++) {
        printf("%.3lf ", almost_equal(y[i], 0.0) ? 0.0 : y[i]);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
