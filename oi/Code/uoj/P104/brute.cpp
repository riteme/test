#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define KMAX 200

typedef long long int64;

static int n, k;
static int64 seq[NMAX + 10];
static int64 pre[NMAX + 10];
static int64 f[NMAX + 10][KMAX + 10];
static int maxp[NMAX + 10][KMAX + 10];
static int op[KMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
        pre[i] = pre[i - 1] + seq[i];
    }  // for
}

int main() {
    initialize();

    for (int j = 1; j <= k; j++) {
        for (int i = j + 1; i <= n; i++) {
            for (int l = 1; l < i; l++) {
                int64 val = f[l][j - 1] + pre[l] * (pre[i] - pre[l]);

                if (val >= f[i][j]) {
                    f[i][j] = val;
                    maxp[i][j] = l;
                }
            }  // for
        }      // for
    }          // for

    printf("%lld\n", f[n][k]);

    int x = n;
    for (int i = k; i >= 1; i--) {
        op[i] = maxp[x][i];
        x = op[i];
    }  // for

    for (int i = 1; i <= k; i++) {
        printf("%d ", op[i]);
    }  // for
    printf("\n");

    return 0;
}  // function main
