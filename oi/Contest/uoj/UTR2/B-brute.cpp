#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 4
#define KMAX 5

static int n, k;
static int answer;
static int D[NMAX + 10][NMAX + 10];
static int G[NMAX + 10][NMAX + 10];
static int W[NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &D[i][j]);
       }
    }
}

static void floyd() {
    memcpy(W, G, sizeof(W));

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (W[i][k] + W[k][j] < W[i][j])
                    W[i][j] = W[i][k] + W[k][j];
            }
        }
    }
}

static void dfs(int u, int v) {
    if (u == n) {
        floyd();
        
        if (memcmp(W, D, sizeof(D)) == 0)
            answer++;
    } else if (v > n) {
        dfs(u + 1, u + 2);
    } else {
        for (int w = 0; w <= k; w++) {
            G[u][v] = G[v][u] = w;

            dfs(u, v + 1);
        }
    }
}

int main() {
    initialize();
    dfs(1, 2);
    printf("%d\n", answer);

    return 0;
}
