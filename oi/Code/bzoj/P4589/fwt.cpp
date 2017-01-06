#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MMAX 65536
#define MOD 1000000007
#define INV2 500000004 

typedef long long int64;

static int n, m;
static int64 vec[MMAX + 10];
static bool marked[MMAX + 10];
static int cnt;
static int primes[MMAX + 10];

inline int next_pow(int x) {
    int k = 1;
    while (k < x) {
        k <<= 1;
    }

    return k;
}

inline int64 quick_pow(int64 a, int64 b) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

static void evaluate_primes() {
    for (int i = 2; i <= MMAX; i++) {
        if (!marked[i])
            primes[cnt++] = i;

        for (int j = 0; j < cnt && i * primes[j] <= MMAX; j++) {
            marked[i * primes[j]] = true;

            if (i % primes[j] == 0)
                break;
       }
    }
}

static void fwt(int64 *X) {
    for (int s = 2; s <= m; s <<= 1) {
        for (int i = 0; i < m; i += s) {
            int mid = i + (s >> 1);
            for (int j = 0; j < (s >> 1); j++) {
                int64 t = X[i + j];
                X[i + j] = (X[i + j] + X[mid + j]) % MOD;
                X[mid + j] = (t - X[mid + j]) % MOD;
            }
        }
    }
}

static void rfwt(int64 *X) {
    for (int s = 2; s <= m; s <<= 1) {
        for (int i = 0; i < m; i += s) {
            int mid = i + (s >> 1);
            for (int j = 0; j < (s >> 1); j++) {
                int64 t = X[i + j];
                X[i + j] = (X[i + j] + X[mid + j]) * INV2 % MOD;
                X[mid + j] = (t - X[mid + j]) * INV2 % MOD;
            }
        }
    }
}

int main() {
    evaluate_primes();

    while (scanf("%d%d", &n, &m) != EOF) {
        memset(vec, 0, sizeof(vec));
        for (int i = 0; i < cnt && primes[i] <= m; i++) {
            vec[primes[i]] = 1;
        }

        m = next_pow(m + 1);  // contain at least m + 1 elements

        fwt(vec);

        for (int i = 0; i < m; i++) {
            vec[i] = quick_pow(vec[i], n);
        }

        rfwt(vec);

        if (vec[0] < 0)
            vec[0] += MOD;

        printf("%lld\n", vec[0]);
    }
}
