#include <cstdio>
#include <cstring>

#define NMAX 1000
#define MMAX 200
#define KMAX 200
#define MOD 1000000007

static int n, m, k;
static int f[NMAX + 10][KMAX + 10];
static int sum[NMAX + 10][KMAX + 10];
static char A[NMAX + 10];
static char B[MMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s%s", A + 1, B + 1);

    f[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        memcpy(sum, f, sizeof(sum));

        for (int j = 1; j <= n; j++)
            for (int p = 0; p < k; p++)
                sum[j][p] = (sum[j][p] + sum[j - 1][p]) % MOD;

        for (int j = n; j >= 1; j--) {
            if (A[j] != B[i])
                for (int p = 0; p <= k; p++)
                    f[j][p] = 0;
            else
                for (int p = k; p >= 1; p--)
                    f[j][p] = (f[j - 1][p] + sum[j - 1][p - 1]) % MOD;
        }

        f[0][0] = 0;
    }

    int answer = 0;
    for (int i = 1; i <= n; i++)
        if (A[i] == B[m])
            answer = (answer + f[i][k]) % MOD;

    printf("%d\n", answer);

    return 0;
}
