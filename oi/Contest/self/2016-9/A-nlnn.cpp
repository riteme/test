// #define NDEBUG

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long int64;

#define NMAX 5000000
#define BLOCKSIZE 10000

static int n;

static int pcnt;
static int64 prime[NMAX + 10];
static int64 phi[NMAX + 10];
static bool marked[NMAX + 10];
static void evaluate_primes() {
    marked[1] = true;
    phi[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!marked[i]) {
            prime[++pcnt] = i;
            phi[i] = i - 1;
        }

        for (int j = 1; j <= pcnt && prime[j] * i <= n; j++) {
            marked[prime[j] * i] = true;

            if (i % prime[j] == 0) {
                phi[prime[j] * i] = phi[i] * prime[j];
                break;
            } else
                phi[prime[j] * i] = phi[prime[j]] * phi[i];
        }  // for
    }      // for
}

static int64 f[NMAX + 10];
static int64 pre[NMAX + 10];
static void evaluate_f() {
    memcpy(f, phi, sizeof(f));

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + f[i];
        for (int j = i + i; j <= n; j += i) {
            f[j] -= f[i];
        }  // for
    }      // for
}

static void initialize() {
    scanf("%d", &n);

    evaluate_primes();
    evaluate_f();
}

int main() {
    initialize();

    int64 answer = 0;

    for (int i = 1; i <= n; i++) {
        answer += f[i];
    }  // for

    printf("%lld\n", answer);

    return 0;
}  // function main
