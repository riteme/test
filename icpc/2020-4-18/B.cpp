#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 2000
#define MOD 100000007

i64 f[NMAX + 10][NMAX + 10][2];

void add(i64 &a, i64 b) {
    a = (a + b) % MOD;
}

void solve(int n, int K) {
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= 2 * i; j++)
        memset(f[i][j], 0, sizeof(f[i][j]));

    f[1][1][0] = 1;
    f[1][2][1] = 1;

    for (int i = 1; i < n; i++)
    for (int j = 1; j <= 2 * i; j++) {
        add(f[i + 1][j][0], f[i][j][0] + 2 * f[i][j][1]);
        add(f[i + 1][j][1], f[i][j][1]);
        add(f[i + 1][j + 1][0], f[i][j][0] + f[i][j][1]);
        add(f[i + 1][j + 1][1], 2 * f[i][j][0] + 2 * f[i][j][1]);
        // add(f[i + 1][j + 2][0], 0);
        add(f[i + 1][j + 2][1], f[i][j][0] + f[i][j][1]);
    }

    i64 ans = (f[n][K][0] + f[n][K][1]) % MOD;
    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, K;
        scanf("%d%d", &n, &K);
        solve(n, K);
    }

    return 0;
}