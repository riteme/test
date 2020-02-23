#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2000

static int n, K;
static int w[NMAX + 10];
static int f[2][NMAX + 10];

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);
    for (int k = 1; k <= K; k++) {
        for (int i = 1; i <= n; i++)
            f[1][i] = max(f[1][i - 1], f[0][i - 1] + w[i]);
        memcpy(f[0] + 1, f[1] + 1, sizeof(int) * n);
    }
    printf("%d\n", f[0][n]);
    return 0;
}