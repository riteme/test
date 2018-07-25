#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 400
#define MOD 998244353

typedef long long int64;

static int n, k;
static int64 answer;
static int D[NMAX + 10][NMAX + 10];
static bool G[NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &D[i][j]);
       }
    }
}

int main() {
    initialize();

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (k != i && k != j &&
                    D[i][k] + D[k][j] == D[i][j])
                    G[i][j] = true;
            }
        }
    }

    answer = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (G[i][j])
                answer = (answer * (k - D[i][j] + 1)) % MOD;
        }
    }

    printf("%lld\n", answer);

    return 0;
}
