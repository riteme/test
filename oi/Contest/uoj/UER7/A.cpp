#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2000

typedef long long int64;

static int n;
static int64 weight[NMAX * 2 + 10][NMAX * 20 + 10];

static void fill(int id, int v) {
    for (int i = n - id + 1; i <= n + id - 1; i++)
        weight[n - id + 1][i] = weight[n + id - 1][i] = weight[i][n - id + 1] =
            weight[i][n + id - 1] = v;
}

static void initialize() {
    scanf("%d", &n);
    n++;

    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);

        fill(i, v);
    }  // for
}

int main() {
    initialize();

    for (int i = 0; i < n * 2; i++)
        weight[0][i] = weight[i][0] = LLONG_MAX;

    for (int i = 1; i < n * 2; i++)
        for (int j = 1; j < n * 2; j++)
            if (i != 1 || j != 1)
                weight[i][j] += min(weight[i - 1][j], weight[i][j - 1]);

    printf("%lld\n", weight[n * 2 - 1][n * 2 - 1]);

    return 0;
}  // function main
