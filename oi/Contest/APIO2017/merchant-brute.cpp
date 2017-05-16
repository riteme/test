#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100
#define KMAX 1000

static int n, m, K;
static i64 B[NMAX + 10][KMAX + 10];
static i64 S[NMAX + 10][KMAX + 10];
static i64 G[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= K; j++) {
            scanf("%lld%lld", B[i] + j, S[i] + j);
        }
    }
    
    memset(G, 0x3f, sizeof(G));
    for (int i = 1; i <= n; i++) {
        G[i][i] = 0;
    }
    
    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);

        G[u][v] = w;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }

    i64 ans = 0;
    for (int i = 2; i <= n; i++) {
        i64 maxv = 0;
        for (int j = 1; j <= K; j++) {
            if (B[1][j] < 0 || S[i][j] < 0)
                continue;

            maxv = max(maxv, S[i][j] - B[1][j]);
        }

        i64 ret = maxv / (G[1][i] + G[i][1]);
        if (ret > ans)
            ans = ret;
    }

    printf("%lld\n", ans);
    return 0;
}
