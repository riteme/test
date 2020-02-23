#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 20

static i64 S[NMAX + 10][NMAX + 10];

int main() {
    S[0][0] = 1;
    for (int i = 1; i <= NMAX; i++)
    for (int j = 1; j <= i; j++)
        S[i][j] += S[i - 1][j - 1] + (i - 1) * S[i - 1][j];

    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n, K, num = 0, dem;
        scanf("%lld%lld", &n, &K);
        dem = 1;
        for (i64 i = 2; i <= n; i++)
            dem *= i;
        for (i64 j = 1; j <= K; j++)
            num += (n - 1) * S[n - 1][j];
        printf("%.4lf\n", (double) num / dem);
    }

    return 0;
}
