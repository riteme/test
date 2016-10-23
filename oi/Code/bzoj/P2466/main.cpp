#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 100

static int n;
static bool A[NMAX + 10][NMAX + 10];
static bool x[NMAX + 10];
static bool y[NMAX + 10];
static bool freeman[NMAX + 10];

static void initialize() {
    memset(A, 0, sizeof(A));
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));

    for (int i = 1; i <= n; i++) {
        x[i] = true;
        A[i][i] = true;
    }  // for

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        A[u][v] = A[v][u] = true;
    }  // for
}

static void gauss() {
    for (int i = 1; i < n; i++) {
        int pivot = 0;
        for (int j = i; j <= n && !pivot; j++)
            if (A[j][i])
                pivot = j;

        if (pivot == 0) {
            freeman[i] = true;
            continue;
        }

        if (pivot != i) {
            for (int j = i; j <= n; j++)
                swap(A[pivot][j], A[i][j]);
            swap(x[pivot], x[i]);
        }

        for (int j = i + 1; j <= n; j++) {
            if (!A[j][i])
                continue;

            for (int k = i; k <= n; k++)
                A[j][k] ^= A[i][k];
            x[j] ^= x[i];
        }  // for
    }      // for

    for (int i = n; i >= 1; i--) {
        y[i] = x[i];

        if (!y[i])
            continue;

        for (int j = 1; j < i; j++)
            if (A[j][i])
                x[j] ^= 1;
    }  // for
}

int main() {
    while (scanf("%d", &n)) {
        if (n == 0)
            break;

        initialize();
        gauss();

        int answer = 0;
        for (int i = 1; i <= n; i++)
            if (y[i])
                answer++;

        printf("%d\n", answer);
    }  // while

    return 0;
}  // function main
