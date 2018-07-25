#include <bits/stdc++.h>

using namespace std;

#define NMAX 10000000

typedef long long int64;

static int n, m;

static int pcnt;
static int prime[NMAX + 10];
static bool marked[NMAX + 10];
static int miu[NMAX + 10];
static int f[NMAX + 10];
static int g[NMAX + 10];
static int64 preg[NMAX + 10];
static void compute_primes() {
    marked[1] = true;
    miu[1] = 1;

    for (int i = 2; i <= NMAX; i++) {
        if (!marked[i]) {
            prime[++pcnt] = i;
            miu[i] = -1;
            f[i] = 1;
            g[i] = 1;
        }

        for (int j = 1; j <= pcnt && prime[j] * i <= NMAX; j++) {
            int p = prime[j];
            marked[p * i] = true;

            if (i % p == 0) {
                miu[p * i] = 0;

                if (f[i] == 1)
                    f[p * i] = p;
                else
                    f[p * i] = 0;

                g[p * i] = miu[i];
                break;
            } else {
                miu[p * i] = miu[p] * miu[i];
                f[p * i] = f[i];

                if (miu[i] == 0) {
                    if (f[i] > 1)
                        g[p * i] = -miu[i / f[i]];
                    else
                        g[p * i] = 0;
                } else
                    g[p * i] = (g[i] > 0 ? -1 : 1) - g[i];
            }
        }  // for
    }      // for

    for (int i = 1; i <= NMAX; i++) {
        preg[i] = preg[i - 1] + g[i];
    }  // for
}

static void initialize() {
    scanf("%d%d", &n, &m);
}

int main() {
    freopen("YYnoGCD.in", "r", stdin);
    freopen("YYnoGCD.out", "w", stdout);

    compute_primes();

    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        int bound = min(n, m);
        int last = 0;
        int64 answer = 0;
        for (int i = 1; i <= bound; i = last + 1) {
            last = min(n / (n / i), m / (m / i));
            answer += int64(n / i) * int64(m / i) * (preg[last] - preg[i - 1]);
        }  // for

        printf("%lld\n", answer);
    }  // while

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
