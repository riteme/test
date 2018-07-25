#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define INFTY 1000000000

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, int _capacity, i64 _w)
        : u(_u), v(_v), capacity(_capacity), w(_w) {}

    int u, v;
    int capacity;
    i64 w;
    Edge *reverse_edge;
};

static int n, m;
static int s, t;
static vector<Edge *> G[NMAX + 10];

void link(int u, int v, int capacity, i64 w) {
    Edge *e = new Edge(u, v, capacity, w);
    Edge *re = new Edge(v, u, 0, -w);
    e->reverse_edge = re;
    re->reverse_edge = e;
    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    scanf("%d%d", &n, &m);
    s = n + 2;
    t = n + 3;

    i64 last = 0;
    for (int i = 1; i <= n; i++) {
        i64 a;
        scanf("%lld", &a);

        if (a < last)
            link(i, t, last - a, 0);
        else
            link(s, i, a - last, 0);
        
        last = a;
    }
    link(n + 1, t, last, 0);

    for (int i = 0; i < m; i++) {
        int l, r;
        i64 w;
        scanf("%d%d%lld", &l, &r, &w);

        link(l, r + 1, INFTY, w);
    }

    for (int i = 1; i <= n; i++) {
        link(i + 1, i, INFTY, 0);
    }
}

static bool exist[NMAX + 10];
static i64 dist[NMAX + 10];
static Edge *edge[NMAX + 10];

void spfa() {
    memset(dist, 0x3f, sizeof(dist));
    memset(exist, 0, sizeof(exist));

    queue<int> q;
    dist[s] = 0;
    exist[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        exist[u] = false;

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (e->capacity == 0)
                continue;

            i64 ndist = dist[u] + e->w;
            if (dist[v] > ndist) {
                dist[v] = ndist;
                edge[v] = e;

                if (!exist[v]) {
                    exist[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

i64 sap() {
    i64 ret = 0;

    while (true) {
        spfa();

        if (dist[t] == 0x3f3f3f3f3f3f3f3f)
            break;

        int w = INFTY;
        int x = t;
        while (x != s) {
            w = min(w, edge[x]->capacity);
            x = edge[x]->u;
        }

        x = t;
        while (x != s) {
            ret += edge[x]->w * w;
            edge[x]->capacity -= w;
            edge[x]->reverse_edge->capacity += w;
            x = edge[x]->u;
        }
    }

    return ret;
}

int main() {
    initialize();

    // for (int i = 1; i <= t; i++) {
    //     for (size_t j = 0; j < G[i].size(); j++) {
    //         Edge *e = G[i][j];

    //         if (e->capacity == 0)
    //             continue;

    //         printf("%d -> %d (capacity = %d, w = %lld)\n",
    //                e->u, e->v, e->capacity, e->w);
    //     }
    // }

    printf("%lld\n", sap());

    return 0;
}
