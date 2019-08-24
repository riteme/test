#include <cstdio>

#define KMAX 2000
#define MOD 1000000007

typedef long long int64;

static void exgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
    } else {
        int64 m, n;
        exgcd(b, a % b, m, n);
        x = n;
        y = m - (a / b) * n;
    }
}

static int64 inv(int64 x) {
    int64 r, k;
    exgcd(x, MOD, r, k);
    
    r %= MOD;
    if (r < 0)
        r += MOD;

    return r;
}

static int64 c[KMAX + 10][KMAX + 10];
static int64 table[KMAX + 10];

int main() {
    c[0][0] = 1;
    for (int i = 1; i <= KMAX; i++)
        c[i][i] = c[i - 1][i - 1] * i % MOD;
    for (int i = 1; i <= KMAX; i++)
        for (int j = 1; j < i; j++)
            c[i][j] = j * (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    for (int64 i = 1; i <= KMAX + 5; i++)
        table[i] = inv(i);

    int t;
    scanf("%d", &t);
    while (t--) {
        int64 n;
        int k;
        scanf("%lld%d", &n, &k);

        n %= MOD;
        int64 answer = 0;
        int64 comb = (n * (n + 1) % MOD) * inv(2) % MOD;
        for (int p = 1; p <= k; p++) {
            answer = (answer + c[k][p] * comb) % MOD;
            comb = (comb * (n - p) % MOD) * table[p + 2] % MOD;
        }

        if (answer < 0)
            answer += MOD;

        printf("%lld\n", answer);
    }

    return 0;
}
