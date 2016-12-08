#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2000
#define MMAX 2000
#define VMAX 300
#define INFTY 1000000000

static int N, M, V, E;
static int C[NMAX + 10];
static int D[NMAX + 10];
static double P[NMAX + 10];
static int G[VMAX + 10][VMAX + 10];
static double f[NMAX + 10][NMAX + 10][2];

static void initialize() {
    scanf("%d%d%d%d", &N, &M, &V, &E);

    for (int i = 1; i <= N; i++)
        scanf("%d", C + i);
    for (int i = 1; i <= N; i++)
        scanf("%d", D + i);
    for (int i = 1; i <= N; i++)
        scanf("%lf", P + i);

    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            G[i][j] = INFTY;
    for (int i = 1; i <= V; i++)
        G[i][i] = 0;

    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        G[u][v] = G[v][u] = min(G[u][v], w);
    }

    for (int k = 1; k <= V; k++)
        for (int i = 1; i <= V; i++)
            for (int j = 1; j <= V; j++)
                G[i][j] = min(G[i][j],
                              G[i][k] + G[k][j]);
}

int main() {
    initialize();

    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= M; j++)
            f[i][j][0] = f[i][j][1] = INFTY;

    f[1][0][0] = f[1][1][1] = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= M; j++) {
            f[i + 1][j][0] = min(
                f[i + 1][j][0],
                min(
                    f[i][j][0] +
                    G[C[i]][C[i + 1]],
                    f[i][j][1] +
                    G[D[i]][C[i + 1]] * P[i] +
                    G[C[i]][C[i + 1]] * (1.0 - P[i])
                )
            );

            if (j < M) {
                f[i + 1][j + 1][1] = min(
                    f[i + 1][j + 1][1],
                    min(
                        f[i][j][0] +
                        G[C[i]][D[i + 1]] * P[i + 1] +
                        G[C[i]][C[i + 1]] * (1.0 - P[i + 1]),
                        f[i][j][1] +
                        G[D[i]][D[i + 1]] * P[i] * P[i + 1] +
                        G[D[i]][C[i + 1]] * P[i] * (1.0 - P[i + 1]) +
                        G[C[i]][D[i + 1]] * (1.0 - P[i]) * P[i + 1] +
                        G[C[i]][C[i + 1]] * (1.0 - P[i]) * (1.0 - P[i + 1])
                    )
                );
            }
        }
    }

    double answer = INFTY;
    for (int i = 0; i <= M; i++)
        answer = min(answer, min(f[N][i][0], f[N][i][1]));

    printf("%.2lf\n", answer);

    return 0;
}
