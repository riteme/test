// #define NDEBUG

#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

#define MMAX 5
#define PFACTOR_MAX 100

static int64 p, n, m;
static int64 w[MMAX + 10];

static int pcnt;
static int64 primes[PFACTOR_MAX + 10];
static bool marked[PFACTOR_MAX + 10];
static void compute_primes() {
    marked[1] = true;
    for (int64 i = 2; i <= PFACTOR_MAX; i++) {
        if (!marked[i])
            primes[++pcnt] = i;
        for (int j = 1; j <= pcnt && primes[j] * i <= PFACTOR_MAX; j++) {
            marked[primes[j] * i] = true;

            if (i % primes[j] == 0)
                break;
        }
    }
}

static void initialize() {
    // scanf("%lld%lld%lld", &p, &n, &m);

    // for (int i = 1; i <= m; i++) {
    //     scanf("%lld", w + i);
    // }
}

int main() {
    initialize();
    compute_primes();

    for (int i = 1; i <= pcnt; i++) {
        printf("%lld ", primes[i]);
    }  // for

    return 0;
}  // function main
