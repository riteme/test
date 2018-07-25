#include <cstdio>
#include <algorithm>

using namespace std;

#define NMAX 200
#define MOD 1000000007

typedef long long int64;

static int n;
static int64 f[NMAX + 10][NMAX + 10][NMAX + 10][2];

int main() {
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
    scanf("%d", &n);

    f[1][0][1][1] = 1;
    f[1][1][1][0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= i; k++) {
                f[i + 1][j + 1][k + 1][0] += f[i][j][k][0];
                f[i + 1][j + 1][k + 1][0] %= MOD;
                f[i + 1][j][k + 1][1] += f[i][j][k][0];
                f[i + 1][j][k + 1][1] %= MOD;
                f[i + 1][j + 1][max(k, j + 1)][k < j + 1 ? 0 : 1] += f[i][j][k][1];
                f[i + 1][j + 1][max(k, j + 1)][k < j + 1 ? 0 : 1] %= MOD;
                f[i + 1][j][k + 1][1] += f[i][j][k][1];
                f[i + 1][j][k + 1][1] %= MOD;
            }
        }
    }

    int64 answer = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            answer = (answer + j * (f[n][i][j][0] + f[n][i][j][1])) % MOD;

    printf("%lld\n", answer);

    fclose(stdin);
    fclose(stdout);
    return 0;
}

