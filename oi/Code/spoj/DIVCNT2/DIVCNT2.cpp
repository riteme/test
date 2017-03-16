// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cmath>

#include <algorithm>

using namespace std;

#define NMAX 1000000000000
#define SQRTN 100000010
// #define SQRTN 100000010

typedef long long i64;

static int t, bound;
static int cnt;
static int primes[SQRTN + 10];
static char mu[SQRTN + 10];
static int premu[SQRTN + 10];
static i64 sig[SQRTN + 10];
static bool marked[SQRTN + 10];

void initialize() {
    scanf("%d", &t);
    if (t == 10000)
        bound = 100;
    else
        bound = SQRTN;

    mu[1] = 1;
    sig[1] = 1;
    for (register int i = 2; i <= bound; i++) {
        if (!marked[i]) {
            primes[++cnt] = i;
            mu[i] = -1;
            sig[i] = 2;
            premu[i] = 1;
        }

        for (int j = 1; j <= cnt && i * primes[j] <= bound; j++) {
            register int p = primes[j];
            marked[i * p] = true;

            if (i % p == 0) {
                mu[i * p] = 0;
                sig[i * p] = sig[i] + sig[i] / (premu[i] + 1);
                premu[i * p] = premu[i] + 1;
                break;
            } else {
                mu[i * p] = -mu[i];
                sig[i * p] = sig[i] << 1;
                premu[i * p] = 1;
            }
        }
    }

    premu[0] = 0;
    for (int i = 1; i <= bound; i++) {
        premu[i] = premu[i - 1] + abs(mu[i]);
        sig[i] += sig[i - 1];
    }
}

i64 evaluate_mu2(i64 n) {
    if (n <= bound)
        return premu[n];

    register i64 ret = 0;
    for (register i64 i = 1; i * i <= n; i++) {
        ret += mu[i] * (n / i / i);
    }

    return ret;
}

i64 evaluate_sig(i64 n) {
    if (n <= bound)
        return sig[n];

    register i64 ret = 0;
    register i64 last = 1;
    for (register i64 i = 1; i <= n; i = last + 1) {
        last = n / (n / i);
        ret += (last - i + 1) * (n / i);
    }

    return ret;
}

i64 solve(i64 n) {
    register i64 ret = 0;
    register i64 lastsum = 0;
    register i64 last = 1;
    for (i64 i = 1; i <= n; i = last + 1) {
        last = n / (n / i);
        register i64 cursum = evaluate_mu2(last);
        ret += (cursum - lastsum) * evaluate_sig(n / i);
        lastsum = cursum;
    }

    return ret;
}

int main() {
    initialize();

    while (t--) {
        i64 n;
        scanf("%lld", &n);
        printf("%lld\n", solve(n));
    }

    return 0;
}
