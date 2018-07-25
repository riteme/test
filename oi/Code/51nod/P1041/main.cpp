#include <cstdio>

#define NMAX 1000
#define MOD 1000000007

typedef long long int64;

static int n;
static int64 f1[NMAX * 9 + 10];
static int64 f2[NMAX * 9 + 10];

int main() {
    scanf("%d", &n);

    for (int i = 0; i <= 9; i++)
        f1[i] = 1;
    for (int i = 1; i <= 9; i++)
        f2[i] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 9 * i; j >= 0; j--) {
            for (int p = 1; p <= 9; p++) {
                if (j - p >= 0) {
                    f1[j] += f1[j - p];
                    f2[j] += f2[j - p];
                    f1[j] %= MOD;
                    f2[j] %= MOD;
                }
            }
        }
    }

    int64 answer = 0;
    for (int i = 0; i <= n * 9; i++) {
        answer += f1[i] * f2[i];
        answer %= MOD;
    }

    printf("%lld\n", answer);

    return 0;
}
