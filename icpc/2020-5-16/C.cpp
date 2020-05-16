#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2010
#define MOD 1000000007

typedef long long i64;

int S[NMAX + 10][NMAX + 10];
int C[NMAX + 10][NMAX + 10];

int main() {
    S[0][0] = 1;
    for (int i = 1; i <= NMAX; i++)
    for (int j = 1; j <= i; j++)
        S[i][j] = (i64(i - 1) * S[i - 1][j] + S[i - 1][j - 1]) % MOD;
    for (int i = 0; i <= NMAX; i++)
        C[i][0] = 1;
    for (int i = 1; i <= NMAX; i++)
    for (int j = 1; j <= i; j++)
        C[i][j] = (i64(C[i - 1][j]) + C[i - 1][j - 1]) % MOD;

    int T;
    scanf("%d", &T);
    while (T--) {
        int n, A, B;
        scanf("%d%d%d", &n, &A, &B);
        i64 ans;
        if (A + B > n + 2)
            ans = 0;
        else
            ans = i64(S[n - 1][A + B - 2]) * C[A + B - 2][A - 1] % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}