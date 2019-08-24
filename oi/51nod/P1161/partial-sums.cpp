#include <cstdio>

#define NMAX 5000
#define MOD 1000000007

typedef long long int64;

static int64 n, k;
static int64 seq[NMAX + 10];
static int64 answer[NMAX + 10];

inline int64 quick_pow(int64 a, int64 b) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

inline int64 inv(int64 x) {
    return quick_pow(x, MOD - 2);
}

static int64 invt[NMAX + 10];

int main() {
    scanf("%lld%lld", &n, &k);

    for (int i = 1; i <= n; i++)
        scanf("%lld", seq + i);

    for (int64 i = 1; i <= n; i++)
        invt[i] = inv(i);

    for (int64 i = 1; i <= n; i++) {
        int64 c = 1;
        for (int64 j = i; j <= n; j++) {
            answer[j] += c * seq[i];
            answer[j] %= MOD;
            c = (c * (k + j - i) % MOD) * invt[j - i + 1] % MOD;
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%lld\n", answer[i]);

    return 0;
}
