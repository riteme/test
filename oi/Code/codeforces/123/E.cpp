#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 100000

static int n;
static vector<int> G[NMAX + 10];
static int X[NMAX + 10];
static int Y[NMAX + 10];
static double pin[NMAX + 10];
static double pout[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    double xsum = 0;
    double ysum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", X + i, Y + i);

        xsum += X[i];
        ysum += Y[i];
    }

    for (int i = 1; i <= n; i++) {
        pin[i] = X[i] / xsum;
        pout[i] = Y[i] / ysum;
    }
}

static bool marked[NMAX + 10];
static int size[NMAX + 10];
static double weight[NMAX + 10];
static double E[NMAX + 10];

static void build_tree(int x) {
    marked[x] = true;

    size[x] = 1;
    weight[x] = pin[x];
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            build_tree(v);

            size[x] += size[v];
            weight[x] += weight[v];
        }
    }
}

static void dfs(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        E[x] += size[v] * weight[v];
    }  // for

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (marked[v])
            continue;

        size[x] = n - size[v];
        size[v] = n;
        weight[x] = 1.0L - weight[v];
        weight[v] = 1.0L;

        dfs(v);

        size[v] = n - size[x];
        size[x] = n;
        weight[v] = 1.0L - weight[x];
        weight[x] = 1.0L;
    }  // for
}

int main() {
    freopen("cf123e_maze.in", "r", stdin);
    freopen("cf123e_maze.out", "w", stdout);

    initialize();

    build_tree(1);

    memset(marked, 0, sizeof(marked));
    dfs(1);

    double answer = 0.0L;

    for (int i = 1; i <= n; i++) {
        answer += E[i] * pout[i];
    }  // for

    printf("%.12lf\n", answer);

    return 0;
}
