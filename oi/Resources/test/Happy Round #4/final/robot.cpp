#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 50000
#define LOGN 20

struct Query {
    int u, v;
};  // struct Query

static int n;
static int rcnt = 0;
static int qcnt = 0;
static Query q[NMAX + 10];
static int father[NMAX + 10];
static double w[NMAX + 10];
static double sum[NMAX + 10];
static double powsum[NMAX + 10];
static int depth[NMAX + 10];
static int f[NMAX + 10][LOGN];

void initialize() {
    scanf("%d", &n);

    w[0] = 0.0;
    father[0] = 0;
    sum[0] = 0.0;
    depth[0] = 0;
    powsum[0] = 0.0;
    while (n > 0) {
        char c = getchar();
        while (c != 'A' and c != 'B') {
            c = getchar();
        }  // while

        switch (c) {
            case 'A':
                int a;
                double b;
                scanf("%d%lf", &a, &b);
                rcnt++;
                father[rcnt] = a;
                depth[rcnt] = depth[a] + 1;
                sum[rcnt] = sum[a] + b;
                powsum[rcnt] = powsum[a] + b * b;
                w[rcnt] = b;

                break;
            case 'B':
                Query &query = q[++qcnt];
                scanf("%d%d", &query.u, &query.v);

                break;
        }  // switch to c

        n--;
    }  // while

    // for(int i=1;i<=rcnt;i++){
    // 	printf("sum[%d] = %lf\n",i,sum[i]);
    // }
    // printf("\n");

    // LCA
    for (int i = 1; i <= rcnt; i++) {
        f[i][0] = father[i];
    }

    for (int i = 1; i <= rcnt; i++) {
        for (int j = 1; j < LOGN; j++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
}

inline int lca(int x, int y) {
    if (depth[x] < depth[y]) {
        swap(x, y);
    }

    int distance = depth[x] - depth[y];
    for (int i = 0; i <= LOGN; i++) {
        if ((1 << i) & distance) {
            x = f[x][i];
        }
    }

    if (x == y)
        return x;

    for (int i = LOGN - 1; i >= 0; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }

    return father[x];
}

int main() {
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
    initialize();

    for (int i = 1; i <= qcnt; i++) {
        int u = q[i].u;
        int v = q[i].v;
        int ancestor = lca(u, v);
        double allsum =
            sum[u] + sum[v] - 2 * sum[father[ancestor]] - w[ancestor];
        double allpowsum = powsum[u] + powsum[v] -
                           2 * powsum[father[ancestor]] -
                           w[ancestor] * w[ancestor];
        double allcnt = depth[u] + depth[v] - 2 * depth[father[ancestor]] - 1;
        double average = allsum / allcnt;
        double offestsum =
            allpowsum + allcnt * average * average - 2 * average * allsum;

        // printf("LCA(%d, %d) = %d, allsum = %lf, allcnt = %lf, average = %lf,
        // offestsum = %lf\n",u,v,ancestor,allsum,allcnt,average,offestsum);
        printf("%.6lf\n", offestsum / allcnt);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
