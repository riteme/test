#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define NMAX 100000
#define MMAX 500000

typedef long long int64;

struct Edge {
    int u, v;
    int64 w;

    int either(int x) const {
        return u == x ? v : u;
    }
};  // struct Edge

struct Command {
    int u, v;
    int64 s;
    bool answer;
};

static int  n, m, cnt, q;
static bool is_petrol[NMAX + 10];
static int epos;
static Edge edges[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static Command commands[NMAX  + 10];
static Command *ref[NMAX + 10];

inline void add_edge(int u, int v, int64 w) {
    epos++;
    Edge *e = edges + epos;
    e->u = u;
    e->v = v;
    e->w = w;

    G[u].push_back(e);
    G[v].push_back(e);
}

static void initialize() {
    scanf("%d%d%d%d", &n, &m, &cnt, &q);

    for (int i = 0; i < cnt; i++) {
        int x;
        scanf("%d", &x);

        is_petrol[x] = true;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        int64 w;
        scanf("%d%d%lld", &u, &v, &w);

        add_edge(u, v, w);
    }

    for (int i = 1; i <= q; i++) {
        scanf("%d%d%lld", &commands[i].u, &commands[i].v, &commands[i].s);
        ref[i] = commands + i;
    }
}

static int64 dist[NMAX + 10];
static int source[NMAX + 10];
static bool marked[NMAX + 10];

struct Compare {
    bool operator()(const int a, const int b) const {
        return dist[a] > dist[b];
    }
};

typedef priority_queue<int, vector<int>, Compare> Heap;

static void find_nearest() {
    memset(marked, 0, sizeof(marked));
    Heap q;
    for (int i = 1; i <= n; i++) {
        if (is_petrol[i]) {
            dist[i] = 0;
            source[i] = i;
            q.push(i);
        } else
            dist[i] = LLONG_MAX;   
    }

    while (!q.empty()) {
        int u = q.top();
        q.pop();

        if (marked[u])
            continue;
        marked[u] = true;

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            if (marked[v])
                continue;

            if (dist[u] + e->w < dist[v]) {
                dist[v] = dist[u] + e->w;
                source[v] = source[u];
                q.push(v);
            }
        }
    }
}

static bool cmp_command(const Command *a, const Command *b) {
    return a->s < b->s;
}

static bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

static int set[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }
}

inline int find_set(int x) {
    return set[x] == x ? x : set[x] = find_set(set[x]);
}

inline void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);

    set[x] = y;
}


int main() {
    freopen("petrol.in", "r", stdin);
    freopen("petrol.out", "w", stdout);
    initialize();

    find_nearest();

    for (int i = 1; i <= m; i++) {
        Edge &e = edges[i];
        e.w += dist[e.u] + dist[e.v];
        e.u = source[e.u];
        e.v = source[e.v];
    }

    sort(ref + 1, ref + q + 1, cmp_command);
    sort(edges + 1, edges + m + 1, cmp_edge);

    int gpos = 1, cpos = 1;
    make_set();
    while (cpos <= q) {
        Command *comm = ref[cpos];

        while (gpos <= m && edges[gpos].w <= comm->s) {
            union_set(edges[gpos].u, edges[gpos].v);
            gpos++;
        }

        comm->answer = find_set(comm->u) == find_set(comm->v);
        cpos++;
    }

    for (int i = 1; i <= q; i++) {
        puts(commands[i].answer ? "YES" : "NO");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
