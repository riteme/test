#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200

int n, m;
int loc[NMAX + 10];
double ln[100];
double G1[NMAX + 10][NMAX + 10], G2[NMAX + 10][NMAX + 10];

void floyd(double G[NMAX + 10][NMAX + 10]) {
    for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
        G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
}

double solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        int p;
        scanf("%d", &p);
        G1[i][j] = i == j ? 0 : ln[p];
    }

    floyd(G1);

    scanf("%d", &m);
    for (int i = 0; i < m; i++)
        scanf("%d", loc + i);
    loc[m++] = 1;
    loc[m++] = 2;

    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
        G2[i][j] = i == j ? 0 : 1e99;

    for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++) {
        int u = loc[i];
        int v = loc[j];
        G2[u][v] = 1 / exp(-G1[u][v]);
    }

    floyd(G2);

    int holyshit;
    scanf("%d", &holyshit);
    return holyshit * G2[1][2];
}

int main() {
    ln[0] = 1e99;
    for (int i = 1; i <= 100; i++)
        ln[i] = -log(i / 100.0);

    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        double ans = solve();
        printf("%.9lf\n", ans);
    }
    return 0;
}