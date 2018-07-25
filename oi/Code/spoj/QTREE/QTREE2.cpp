#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 10000
#define LOGN 14

struct Edge {
    int u;
    int v;
    int weight;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static Edge memory[NMAX + 10];
static int memcnt;

inline void refresh_memory() {
    memcnt = 0;
}

inline Edge *allocate() {
    return &memory[memcnt++];
}

static int n = 0;
static vector<Edge *> G[NMAX + 10];
static bool marked[NMAX + 10];
static int depth[NMAX + 10];
static int dist[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];

static void prepare() {}

static void cleanup() {
    for (unsigned i = 1; i <= n; i++) {
        G[i].clear();
    }  // for

    memset(marked, false, sizeof(marked));
    // memset(depth, 0, sizeof(depth));
    // memset(dist, 0, sizeof(dist));
    memset(f, 0, sizeof(f));

    refresh_memory();
}

inline void add_edge(int u, int v, int w) {
    Edge *e = allocate();
    e->u = u;
    e->v = v;
    e->weight = w;

    G[u].push_back(e);
    G[v].push_back(e);
}

static void read_graph() {
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        add_edge(u, v, c);
    }  // for
}

static void make_root(int root) {
    marked[root] = true;
    f[root][0] = root;
    depth[root] = 1;
    dist[root] = 0;

    queue<int> q;
    q.push(root);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (unsigned i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            if (!marked[v]) {
                marked[v] = true;
                q.push(v);

                f[v][0] = u;
                depth[v] = depth[u] + 1;
                dist[v] = dist[u] + e->weight;
            }
        }  // for
    }      // while
}

static void prepare_lca() {
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }  // for
    }      // for
}

static void initialize() {
    read_graph();
    make_root(1);
    prepare_lca();
}

inline int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int d = depth[u] - depth[v];
    for (int i = LOGN; i >= 0; i--) {
        if (d & (1 << i)) {
            u = f[u][i];
        }
    }  // for

    if (u == v) {
        return u;
    }

    for (int i = LOGN; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }  // for

    return f[u][0];
}

inline int kth(int u, int k) {
    int d = depth[u] - k;
    for (int i = LOGN; i >= 0; i--) {
        if (d & (1 << i)) {
            u = f[u][i];
        }
    }  // for

    return u;
}

static void process() {
    char buffer[10];

    while (true) {
        scanf("%s", buffer);

        if (buffer[1] == 'I') {  // DIST
            int a, b;
            scanf("%d%d", &a, &b);

            int p = lca(a, b);
            printf("%d\n", dist[a] + dist[b] - 2 * dist[p]);
        } else if (buffer[1] == 'T') {  // KTH
            int a, b, k;
            scanf("%d%d%d", &a, &b, &k);

            int p = lca(a, b);
            int llength = depth[a] - depth[p] + 1;
            int rlength = depth[b] - depth[p] + 1;
            if (k <= llength) {
                printf("%d\n", kth(a, depth[a] - k + 1));
            } else {
                printf("%d\n",
                       kth(b, depth[b] - (rlength - (k - llength)) + 1));
            }
        } else {
            break;
        }
    }  // while
}

int main() {
    prepare();

    int t;
    scanf("%d", &t);
    while (t > 0) {
        cleanup();
        initialize();
        process();

        t--;
    }  // while

    return 0;
}  // function main
