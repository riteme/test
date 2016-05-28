#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long ntype;

struct Edge {
    Edge(int _u, int _v, ntype _w) : u(_u), v(_v), w(_w) {}

    int u, v;
    ntype w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, m;
static vector<Edge *> G[NMAX + 10];
static int father[NMAX + 10];
static int depth[NMAX + 10];
static ntype weight[NMAX + 10];
static ntype sum[NMAX + 10];
static bool marked[NMAX + 10];

static void set_root(int x) {
    marked[x] = true;

    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (not marked[v]) {
            depth[v] = depth[x] + 1;
            weight[v] = e->w;
            father[v] = x;

            set_root(v);
            sum[x] += e->w + sum[v];
        }
    }  // for
}

static void update(int u, int v, ntype w) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    ntype deta = w - weight[u];
    weight[u] = w;

    u = father[u];
    while (u) {
        sum[u] += deta;
        u = father[u];
    }  // while
}

static ntype solve() {
    ntype answer = 0;

    for (int i = 2; i <= n; i++) {
        ntype energy = (sum[1] - sum[i] - weight[i]) * sum[i];
        answer += energy;
    }  // for

    return answer;
}

inline void add_edge(int u, int v, ntype w) {
    Edge *e = new Edge(u, v, w);
    G[u].push_back(e);
    G[v].push_back(e);
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        ntype w;
        scanf("%d%d%lld", &u, &v, &w);

        add_edge(u, v, w);
    }  // for

    set_root(1);
}

int main() {
    freopen("nuclear.in", "r", stdin);
    freopen("nuclear.out", "w", stdout);
    initialize();

    for (int i = 0; i < m; i++) {
        int u, v;
        ntype w;
        scanf("%d%d%lld", &u, &v, &w);

        update(u, v, w);
        printf("%lld\n", solve());
        // printf("%lld\n", 1LL);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
