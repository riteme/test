#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define BMOD 1073741823

typedef unsigned int u32;

static u32 pcnt;
static u32 primes[NMAX + 10];
static bool marked[NMAX + 10];
static int mindiv[NMAX + 10];
static int mincnt[NMAX + 10];
static int d[NMAX + 10];

static int q;

void initialize() {
    scanf("%d", &q);

    d[1] = 1;
    for (int i = 2; i <= NMAX; i++) {
        if (!marked[i]) {
            primes[++pcnt] = i;
            mindiv[i] = i;
            mincnt[i] = 1;
            d[i] = 2;
        }

        for (int j = 1; j <= pcnt && i * primes[j] <= NMAX; j++) {
            int p = primes[j];
            int u = i * p;
            marked[u] = true;
            mindiv[u] = p;

            if (i % p) {
                mincnt[u] = 1;
                d[u] = d[i] * 2;
            } else {
                mincnt[u] = mincnt[i] + 1;
                d[u] = d[i] + d[i] / (mincnt[i] + 1);
                break;
            }
        }
    }
}

int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    initialize();

    while (q--) {
        int n, m;
        scanf("%d%d", &n, &m);

        i64 answer = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                answer = answer +
                    ((d[i * i] * d[j * j] & BMOD) * d[i * j] & BMOD)
                    & BMOD;
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}
