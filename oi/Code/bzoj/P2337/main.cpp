/**
 * 同HNOI2013游走
 * 首先位运算拆位处理
 * 与游走一题不同的是，游走我们知道1号点的期望经过次数
 * 这里我们设的是每个点到n的期望，所以初值是n号点为0
 * ret没有swap居然过了游走......数据有多水.....
 */

#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 10000
#define SMAX 30

struct Edge {
    int u, v, w;
};

static int n, m;
static Edge edges[MMAX + 10];
static double deg[NMAX + 10];
static double mat[NMAX + 10][NMAX + 10];
static double ret[NMAX + 10];

void guass() {
    for (int i = 1; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j <= n; j++) {
            if (fabs(mat[j][i]) > fabs(mat[pivot][i]))
                pivot = j;
        }

        if (pivot != i) {
            for (int j = i; j <= n; j++) {
                swap(mat[pivot][j], mat[i][j]);
            }
            swap(ret[pivot], ret[i]);
        }

        for (int j = i + 1; j <= n; j++) {
            double r = mat[j][i] / mat[i][i];

            for (int k = i; k <= n; k++) {
                mat[j][k] -= mat[i][k] * r;
            }
            ret[j] -= ret[i] * r;
        }
    }

    for (int i = n; i >= 1; i--) {
        ret[i] /= mat[i][i];

        for (int j = 1; j < i; j++) {
            ret[j] -= ret[i] * mat[j][i];
        }
    }
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d",
              &edges[i].u, &edges[i].v, &edges[i].w);
        deg[edges[i].u] += 1.0;
        
        if (edges[i].u != edges[i].v)
            deg[edges[i].v] += 1.0;
    }

    for (int i = 1; i <= n; i++) {
        deg[i] = 1.0 / deg[i];
    }
}

inline void add_edge(int u, int v, bool w) {
    if (u == n)
        return;

    if (w) {
        mat[u][v] += deg[u];
        ret[u] += deg[u];
    } else
        mat[u][v] -= deg[u];
}

int main() {
    initialize();

    double answer = 0.0;
    double tpow = 1.0;
    for (int s = 0; s <= SMAX; s++) {
        memset(mat, 0, sizeof(mat));
        memset(ret, 0, sizeof(ret));

        for (int i = 1; i <= n; i++) {
            mat[i][i] = 1.0;
        }

        for (int i = 1; i <= m; i++) {
            Edge &e = edges[i];
            add_edge(e.u, e.v, (e.w >> s) & 1);

            if (e.u != e.v)
                add_edge(e.v, e.u, (e.w >> s) & 1);
        }

        guass();

        answer += ret[1] * tpow;
        tpow *= 2.0;
    }

    printf("%.3lf\n", answer);

    return 0;
}
