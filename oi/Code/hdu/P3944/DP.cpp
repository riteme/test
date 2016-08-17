/**
 * Accepted
 * Lucas
 */

#include <bits/stdc++.h>

using namespace std;

#define PMAX 10000
#define TABLE_MAX 1229

typedef long long int64;

static int64 pcnt;
static int64 prime[PMAX + 10];
static int64 prime_id[PMAX + 10];
static bool marked[PMAX + 10];
static void compute_primes() {
    for (int64 i = 2; i <= PMAX; i++) {
        if (!marked[i]) {
            prime[++pcnt] = i;
            prime_id[i] = pcnt;
        }
        for (int64 j = 1; j <= pcnt && prime[j] * i <= PMAX; j++) {
            marked[prime[j] * i] = true;
            if (i % prime[j] == 0)
                break;
        }  // for
    }      // for
}

static int64 f[TABLE_MAX + 10][PMAX + 10];
static int64 finv[TABLE_MAX + 10][PMAX + 10];
inline int64 quick_pow(int64 a, int64 b, int64 m) {
    int64 r = 1;
    while (b) {
        if (b & 1)
            r = (r * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return r;
}

static void compute_fact() {
    for (int64 i = 1; i <= pcnt; i++) {
        f[i][0] = finv[i][0] = 1;

        int64 p = prime[i];
        for (int64 j = 1; j < p; j++)
            f[i][j] = (f[i][j - 1] * j) % p;

        finv[i][p - 1] = quick_pow(f[i][p - 1], p - 2, p);
        for (int j = p - 2; j >= 1; j--)
            finv[i][j] = (finv[i][j + 1] * (j + 1)) % p;
    }  // for
}

inline int64 c_direct(int64 n, int64 k, int64 p) {
    if (n < k)
        return 0;

    int64 pid = prime_id[p];
    return (((f[pid][n] * finv[pid][k]) % p) * finv[pid][n - k]) % p;
}

static int64 c_lucas(int64 n, int64 k, int64 p) {
    if (n < p)
        return c_direct(n, k, p);

    return (c_direct(n % p, k % p, p) * c_lucas(n / p, k / p, p)) % p;
}

int main() {
    compute_primes();
    compute_fact();

    int64 n, k, p;
    int64 t = 1;
    while (scanf("%lld%lld%lld", &n, &k, &p) != EOF) {
        if (k <= n / 2)
            k = n - k;
        printf("Case #%lld: %lld\n", t, (c_lucas(n + 1, k + 1, p) + k % p) % p);

        t++;
    }  // while

    return 0;
}  // function main
