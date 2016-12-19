#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 200000

struct Edge {
    Edge ()
        : walked(false) {}

    int id;
    int u;
    int v;
    bool walked;

    int either(int x) const  {
        return u == x ? v : u;
    }
};

static int type;
static int n, m;
static Edge edges[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];

inline void add_edge(int u, int v, int id) {
    Edge *e = edges + id;
    e->id = id;
    e->u = u;
    e->v = v;

    G[u].push_back(e);
    in[v]++;
    out[u]++;
    
    if (type == 1)
        G[v].push_back(e);
}

static void initialize() {
    scanf("%d%d%d", &type, &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        add_edge(u, v, i);
    }
}

struct Direction {
    Edge *edge;
    int from;
};

static int pos;
static Direction path[MMAX + 10];
static int current[NMAX + 10];

static void walk(int x) {
    for (int &i = current[x]; i < G[x].size(); i++) {
        Edge *e = G[x][i];

        if (e->walked)
            continue;

        e->walked = true;
        walk(e->either(x));
        path[pos--] = { e, x };
    }
}

static bool solve() {
    if (type == 1) {
        for (int i = 1; i <= n; i++)
            if ((in[i] + out[i]) & 1)
                return false;
    } else {
        for (int i = 1; i <= n; i++)
            if (in[i] != out[i])
                return false;
    }

    for (int i = 1; i <= n; i++) {
        if (!G[i].empty()) {
            pos = m;
            walk(i);
            break;
        }
    }

    return pos == 0;
}

int main() {
    initialize();

    if (solve()) {
        printf("YES\n");

        for (int i = 1; i <= m; i++) {
            if (type == 1 && path[i].from != path[i].edge->u)
                printf("%d ", -path[i].edge->id);
            else
                printf("%d ", path[i].edge->id);
        }
    } else
        printf("NO\n");

    return 0;
}
