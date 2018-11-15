// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100
#define KMAX 1000
#define INF 1000000001

typedef long long i64;

static int n, m, K;
static i64 B[NMAX + 10][KMAX + 10];
static i64 S[NMAX + 10][KMAX + 10];
static i64 D[NMAX + 10][NMAX + 10];
static i64 C[NMAX + 10][NMAX + 10];
static i64 W[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= K; j++) {
            scanf("%lld%lld", B[i] + j, S[i] + j);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;

            i64 maxv = 0;
            for (int k = 1; k <= K; k++) {
                if (B[i][k] < 0 || S[j][k] < 0)
                    continue;

                maxv = max(maxv, S[j][k] - B[i][k]);
            }

            C[i][j] = maxv;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            D[i][j] = i == j ? 0 : INF;
        }
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);

        D[u][v] = w;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
}

bool test(i64 k) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            W[i][j] = k * D[i][j] - C[i][j];
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && W[i][j] + W[j][i] <= 0)
                    return true;

                W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
            }
        }
    }

    return false;
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();

    i64 l = 0, r = 1000000007;
    while (l < r) {
        i64 mid = (l + r) / 2 + 1;

        if (test(mid))
            l = mid;
        else
            r = mid - 1;
    }

    printf("%lld\n", l);

    return 0;
}
