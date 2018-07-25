#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 262144
#define MOD 998244353
#define G 3

typedef long long i64;

inline i64 quick_pow(i64 a, i64 b) {
    i64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

inline i64 inv(i64 a) {
    return quick_pow(a, MOD - 2);
}

inline int next_pow(int n) {
    int ret = 1;
    while (n > ret) {
        ret <<= 1;
    }

    return ret;
}

static int t, n;
static i64 tpow[NMAX + 10];
static i64 fact[NMAX + 10];
static i64 wtable[NMAX + 10];
static i64 iwtable[NMAX + 10];
static i64 a[NMAX + 10];
static i64 A[NMAX + 10], B[NMAX + 10], C[NMAX + 10];
static i64 f[NMAX + 10];

bool cmp(const i64 x, const i64 y) {
    return x > y;
}

void preprocess() {
    scanf("%d", &t);

    tpow[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        tpow[i] = (tpow[i - 1] << 1) % MOD;
    }

    fact[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    for (int i = 2; i <= NMAX; i <<= 1) {
        wtable[i] = quick_pow(G, (MOD - 1) / i);
        iwtable[i] = quick_pow(G, MOD - 1 - (MOD - 1) / i);
    }
}

void initialize() {
    memset(a, 0, sizeof(a));
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    memset(C, 0, sizeof(C));
    memset(f, 0, sizeof(f));

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld", a + i);
    }

    sort(a, a + n, cmp);
}

void ntt(i64 *X, int n, bool reversed) {
    i64 *seq = new i64[n];
    memcpy(seq, X, sizeof(i64) * n);
    int rev = 0;
    for (int i = 0; i < n - 1; i++) {
        X[i] = seq[rev];
        int k = n >> 1;
        while (rev & k) {
            rev ^= k;
            k >>= 1;
        }

        rev |= k;
    }

    delete[] seq;

    for (int s = 2; s <= n; s <<= 1) {
        int len = s >> 1;
        i64 w_n = reversed ? quick_pow(G, MOD - 1 - (MOD - 1) / s) :
                             quick_pow(G, (MOD - 1) / s);

        for (int i = 0; i < n; i += s) {
            i64 w = 1;
            for (int j = i; j < i + len; j++) {
                i64 tmp = X[j];
                X[j] = (X[j] + w * X[j + len] % MOD) % MOD;
                X[j + len] = (tmp - w * X[j + len] % MOD) % MOD;
                w = w * w_n % MOD;
            }
        }
    }
}

int main() {
    preprocess();

    while (t--) {
        initialize();

        for (int i = 0; i < n; i++) {
            A[i] = a[i] * fact[i] % MOD;
            B[i] = tpow[n - i] * inv(fact[i]) % MOD;
        }

        for (int i = 0; i < n; i++) {
            C[i] = A[n - i - 1];
        }

        int m = next_pow(n << 1);
        ntt(C, m, false);
        ntt(B, m, false);

        for (int i = 0; i < m; i++) {
            C[i] = C[i] * B[i] % MOD;
        }

        ntt(C, m, true);

        i64 invm = inv(m);
        for (int i = 0; i < m; i++) {
            C[i] = C[i] * invm % MOD;
        }

        for (int i = 0; i < n; i++) {
            f[i] = inv(tpow[i + 1] * fact[i] % MOD) * C[n - i - 1] % MOD;
        }

        i64 sum = 0;
        for (int i = 0; i < n; i++) {
            sum = (sum + f[i]) % MOD;
            printf("%lld ", (sum + MOD) % MOD);
        }

        printf("\n");
    }

    return 0;
}
