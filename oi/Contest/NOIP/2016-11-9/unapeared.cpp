#include <cstdio>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define QMAX 10

static int n, q;
static int seq[NMAX + 10];
static int lastpos[NMAX + 10];
static int f[NMAX + 10];

int main() {
    freopen("unapeared.in", "r", stdin);
    freopen("unapeared.out", "w", stdout);
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }

    for (int i = 1; i <= n + 1; i++) {
        f[i] = INT_MAX;
        for (int j = 1; j <= q; j++) {
            f[i] = min(f[i], f[lastpos[j]] + 1);
        }

        lastpos[seq[i]] = i;
    }

    printf("%d\n", f[n + 1]);

    return 0;
}
