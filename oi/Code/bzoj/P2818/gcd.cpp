#include <bits/stdc++.h>

using namespace std;

#define NMAX 10000000

typedef long long int64;

static int n;

static int pcnt;
static int prime[NMAX + 10];
static bool marked[NMAX + 10];
static int64 phi[NMAX + 10];
static int64 prephi[NMAX + 10];
static void compute_primes() {
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

    for (int i = 1; i <= n; i++) {
        prephi[i] = prephi[i - 1] + phi[i];
    }  // for
}

static void initialize() {
    scanf("%d", &n);

    compute_primes();
}

int main() {
    initialize();

    int64 answer = 0;
    int64 used = 0;
    for (int i = 1; i <= pcnt; i++) {
        if (prime[i] > n)
            break;
        answer += prephi[n / prime[i]];
        used++;
    }  // for

    printf("%lld\n", (answer - used) * 2 + used);

    return 0;
}  // function main
