#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 5000011

static int n, k;
static int f[NMAX + 10][2];
static int g[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &k);
}

int main() {
    initialize();

    if (k == 0) {
        int answer = 1;
        for (int i = 1; i <= n; i++) {
            answer = (answer << 1) % MOD;
        }

        printf("%d\n", answer);
        return 0;
    }

    g[0] = 1;
    f[0][1] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = (f[i - 1][0] + f[i - 1][1]) % MOD;

        if (i <= k)
            f[i][1] = 1;
        else
            f[i][1] = g[i - k - 1];

        g[i] = (g[i - 1] + f[i][1]) % MOD;
    }

    printf("%d\n", (f[n][0] + f[n][1]) % MOD);

    return 0;
}
