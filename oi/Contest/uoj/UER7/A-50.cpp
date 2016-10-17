#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000

typedef long long int64;

static int n;
static int64 weight[NMAX + 10];
static int64 f[NMAX * 2 + 10][NMAX + 10];

static void fill(int id, int64 v) {
    for (int i = n - id + 1; i <= n + id - 1; i++)
        f[i][n - id + 1] = v;
}

static void initialize() {
    scanf("%d", &n);
    n++;

    for (int i = 1; i <= n; i++) {
        int64 v;
        scanf("%lld", &v);

        weight[i] = v;
        fill(i, v);
    }  // for
}

int main() {
    initialize();

    for (int i = 2; i <= 2 * n - 1; i++) {
        for (int j = 1; f[i][j] > 0; j++) {
            int64 maxv = LLONG_MAX;

            if (f[i - 1][j] > 0 && f[i - 1][j] < maxv)
                maxv = f[i - 1][j];
            if (f[i][j - 1] > 0 && f[i][j - 1] < maxv)
                maxv = f[i][j - 1];

            f[i][j] += maxv;
        }
    }  // for

    int64 answer = LLONG_MAX;
    int pos = 0;
    for (int i = 1; i <= n; i++) {
        if (f[n + i - 1][n - i + 1] < answer) {
            answer = f[n + i - 1][n - i + 1];
            pos = i;
        }
    }

    printf("%lld\n", answer * 2 - weight[pos]);

    return 0;
}  // function main
