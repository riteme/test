#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define MMAX 3000
#define INF 100000000000000

typedef long long i64;

static int n, m;
static i64 A[NMAX + 10];
static i64 f[MMAX + 10][MMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        A[i] += A[i - 1];
    }
}

inline i64 p(i64 x) {
    return x * x;
}

int main() {
    initialize();

    if (n > 3000) {
    } else {
        for (int i = 1; i <= n; i++) {
            f[0][i] = INF;
        }

        for (int j = 1; j <= m; j++) {
            for (int i = 0; i <= n; i++) {
                f[j][i] = INF;
                if (i >= j) {
                    for (int k = 0; k < i; k++) {
                        f[j][i] = min(f[j][i], f[j - 1][k] + p(A[i] - A[k]));
                    }
                }
            }
        }

        printf("%lld\n", m * f[m][n] - p(A[n]));
    }

    return 0;
}
