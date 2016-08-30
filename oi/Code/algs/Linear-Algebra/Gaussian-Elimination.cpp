#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define NMAX 100

static int n;
static double A[NMAX + 10][NMAX + 10];
static double x[NMAX + 10];
static double y[NMAX + 10];

static void guass() {
    for (int i = 1; i <= n; i++) {
        int pos = i;

        for (int j = i + 1; j <= n; j++) {
            if (fabs(A[j][i]) > fabs(A[pos][i]))
                pos = j;
        }  // for

        if (pos != i) {
            for (int j = i; j <= n; j++)
                swap(A[pos][j], A[i][j]);
            swap(x[pos], x[i]);
        }

        for (int j = i + 1; j <= n; j++) {
            double ratio = (A[j][i] / A[i][i]);
            for (int k = i; k <= n; k++) {
                A[j][k] -= ratio * A[i][k];
            }  // for

            x[j] -= ratio * x[i];
        }  // for
    }      // for
}

static void reverse_guass() {
    for (int i = n; i >= 1; i--) {
        y[i] = x[i] / A[i][i];
        for (int j = 1; j <= i - 1; j++) {
            x[j] -= A[j][i] * y[i];
        }  // for
    }      // for
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lf", &A[i][j]);
        }  // for

        scanf("%lf", &x[i]);
    }  // for

    guass();

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         printf("%lf ", A[i][j]);
    //     }  // for
    //     printf("%lf\n", x[i]);
    // }  // for

    reverse_guass();

    for (int i = 1; i <= n; i++) {
        printf("%d ", int(y[i] + 0.5));
    }  // for

    return 0;
}  // function main
