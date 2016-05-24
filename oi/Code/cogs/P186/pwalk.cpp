#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, q;
static vector<Edge *> G[NMAX + 10];
static int dist[NMAX + 10];
static vector<int> children[NMAX + 10];
static bool marked[NMAX + 10];

static void set_root(int x) {
    marked[x] = true;

    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (not marked[v]) {
            dist[v] = dist[x] + e->w;
            children[x].push_back(v);
            set_root(v);
        }
    }  // for
}

static int cnt;
static int seq[NMAX * 3];
static int depth[NMAX * 3];
static int pos[NMAX + 10];

#define LOGN 15
static int st[NMAX * 3][LOGN + 1];

static bool cmp(const int a, const int b) {
    return depth[a] < depth[b];
}

static void initialize_st() {
    for (int i = 1; i <= cnt; i++) {
        st[i][0] = i;
    }  // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= cnt; i++) {
            int next = i + (1 << (j - 1));
            if (next <= cnt)
                st[i][j] = min(st[i][j - 1], st[next][j - 1], cmp);
        }  // for
    }      // for
}

static int query_min(int left, int right) {
    if (left == right) {
        return depth[left];
    } else {
        int len = right - left + 1;
        int k = 0;
        while (len >> (k + 1) > 0)
            k++;
        return min(st[left][k], st[right - (1 << k) + 1][k], cmp);
    }
}

static void travel(int x, int d) {
    seq[++cnt] = x;
    depth[cnt] = d;
    if (pos[x] == 0)
        pos[x] = cnt;

    for (unsigned i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        travel(v, d + 1);
        seq[++cnt] = x;
        depth[cnt] = d;
    }  // for
}

static int lca(int u, int v) {
    if (pos[u] > pos[v])
        swap(u, v);

    int x = query_min(pos[u], pos[v]);
    return seq[x];
}

static int get_distance(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[lca(u, v)];
}

inline void add_edge(int u, int v, int w) {
    Edge *e = new Edge(u, v, w);

    G[u].push_back(e);
    G[v].push_back(e);
}

static void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        add_edge(u, v, c);
    }  // for
}

int main() {
    freopen("pwalk.in", "r", stdin);
    freopen("pwalk.out", "w", stdout);
    initialize();
    set_root(1);
    travel(1, 1);
    initialize_st();

    for (int i = 0; i < q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        printf("%d\n", get_distance(u, v));
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
