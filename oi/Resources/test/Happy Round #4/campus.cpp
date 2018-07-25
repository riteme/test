#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define NMAX 200000
#define LOGN 20

struct Edge {
    Edge() : u(0), v(0), w(0) {}
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u;
    int v;
    int w;

    int another(int x) {
        return x == u ? v : u;
    }
};  // struct  Edge

static int n;
static int m;
static int edgeCount = 0;
static Edge edges[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static bool marked[NMAX + 10];
static int dist[NMAX + 10];
static int depth[NMAX + 10];
static int father[NMAX + 10];
static int f[NMAX + 10][LOGN];
static int tmpcnt;
static int tmp[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i < n; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);

        edgeCount++;
        edges[edgeCount].u = a;
        edges[edgeCount].v = b;
        edges[edgeCount].w = w;
        G[a].push_back(&edges[edgeCount]);
        G[b].push_back(&edges[edgeCount]);
    }

    memset(marked, false, sizeof(marked));
    queue<int> q;
    marked[1] = true;
    father[1] = 0;
    dist[1] = 0;
    depth[1] = 1;
    father[0] = 0;
    dist[0] = 0;
    depth[0] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->another(u);

            if (!marked[v]) {
                marked[v] = true;
                father[v] = u;
                depth[v] = depth[u] + 1;
                dist[v] = e->w;

                q.push(v);
            }
        }
    }  // while

    // for (int i=1;
    //      i<=n;
    //      i++) {
    //     printf("dist[%d] = %d\n",i,dist[i]);
    // }  // for

    // LCA
    for (int i = 1; i <= n; i++) {
        f[i][0] = father[i];
    }

    for (int i = 1; i <= n; i++) {
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
    for (int i = LOGN - 1; i >= 0; i--) {
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
    freopen("campus.in", "r", stdin);
    freopen("campus.out", "w", stdout);
    initialize();

    // for(int i=1;i<=n;i++){
    //  for(int j=i;j<=n;j++){
    //      printf("LCA(%d, %d) = %d\n",i,j,lca(i,j));
    //  }
    // }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u == v) {
            printf("0\n");
            continue;
        }

        int answer = 0;
        int ancestor = lca(u, v);
        int maxedge = -INT_MAX;
        tmpcnt = depth[u] + depth[v] - 2 * depth[ancestor];

        int x = u;
        int index = 1;
        while (x != ancestor) {
            tmp[index++] = dist[x];
            x = father[x];
        }  // while

        index = 0;
        x = v;
        while (x != ancestor) {
            tmp[tmpcnt - index] = dist[x];
            x = father[x];
            index++;
        }  // while

        // for(int i=1;i<=tmpcnt;i++){
        //  printf("%d ",tmp[i]);
        // }
        // printf("\n");

        tmp[0] = 0;
        for (int j = 1; j <= tmpcnt; j++) {
            maxedge = max(maxedge, tmp[j]);
            tmp[j] = max(max(tmp[j - 1] + tmp[j], 0), max(tmp[j], 0));
            answer = max(answer, tmp[j]);
        }

        if (answer == 0) {
            answer = maxedge;
        }

        printf("%d\n", answer);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
