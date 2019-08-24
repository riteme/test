#include <cstdio>
#include <cstring>

#define NMAX 1000
#define MMAX 200
#define KMAX 200
#define MOD 1000000007

static int n, m, k;
static int f[MMAX + 10][NMAX + 10][KMAX + 10];
static char A[NMAX + 10];
static char B[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s%s", A + 1, B + 1);

    f[0][0][0] = 1;
    for (int i = 1; i <= m; i++) {
        // for (int j = 0; j <= n; j++)
        //     f[i][j][0] = 1;

        for (int j = 1; j <= n; j++) {
            if (B[i] != A[j])
                continue;

            for (int p = 1; p <= k; p++) {
                f[i][j][p] = f[i - 1][j - 1][p];

                for (int l = 0; l <= j - 1; l++)
                    f[i][j][p] = (f[i][j][p] + f[i - 1][l][p - 1]) % MOD;
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; i++)
        if (A[i] == B[m])
            answer = (answer + f[m][i][k]) % MOD;

    printf("%d\n", answer);

    return 0;
}
