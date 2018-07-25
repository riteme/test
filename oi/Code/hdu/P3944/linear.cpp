#include <bits/stdc++.h>

#define PMAX 80000000

static int pcnt;
static int prime[PMAX + 10];
static int prime_id[PMAX + 10];
static bool marked[PMAX + 10];
static void compute_primes() {
    for (int i = 2; i <= PMAX; i++) {
        if (!marked[i]) {
            prime[++pcnt] = i;
            prime_id[i] = pcnt;
        }
        for (int j = 1; j <= pcnt && prime[j] * i <= PMAX; j++) {
            marked[prime[j] * i] = true;
            if (i % prime[j] == 0)
                break;
        }  // for
    }      // for
}

int main() {
    compute_primes();
    printf("%d\n", prime[pcnt]);

    return 0;
}  // function main
