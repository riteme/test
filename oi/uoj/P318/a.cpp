#define NDEBUG

#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2000
#define INF 0x3f3f3f3f

#ifndef NDEBUG
#define DEBUG(msg, ...) printf(msg, __VA_ARGS__);
#else
#define DEBUG(...)
#endif

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, int _w, int _c) : u(_u), v(_v), w(_w), c(_c) {}

    int u, v, w, c;
    Edge *rev;
};

static int n, Q, k, m, s, t;
static int A[NMAX + 10], S[NMAX + 10], C[NMAX + 10], X[NMAX + 10], R[NMAX + 10];
static i64 ans[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static i64 dist[NMAX + 10];
static Edge *fa[NMAX + 10];

bool sp() {
    static bool in[NMAX + 10];
    memset(dist + 1, 0xaf, sizeof(i64) * t);
    memset(fa + 1, 0, sizeof(Edge *) * t);

    queue<int> q;
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in[u] = false;

        for (auto e : G[u]) {
            int v = e->v;
            if (!e->c) continue;
            if (dist[v] < dist[u] + e->w) {
                dist[v] = dist[u] + e->w;
                fa[v] = e;
                if (!in[v]) {
                    in[v] = true;
                    q.push(v);
                }
            }
        }
    }

    return fa[t];
}

i64 maxflow() {
    i64 ret = 0;
    while (sp()) {
        i64 sum = 0;
        int x = t, mc = INF;
        do {
            mc = min(mc, fa[x]->c);
            sum += fa[x]->w;
            x = fa[x]->u;
        } while (x != s);

        ret += sum * mc;
        DEBUG("sum = %lld, mc = %d\n", sum, mc);
        x = t;
        do {
            DEBUG("%d <- ", x);
            fa[x]->c -= mc;
            fa[x]->rev->c += mc;
            x = fa[x]->u;
        } while (x != s);
        DEBUG("%d\n", s);
    }
    return ret;
}

inline void link(int u, int v, int w, int c) {
    Edge *e = new Edge(u, v, w, c);
    Edge *re = new Edge(v, u, -w, 0);
    e->rev = re;
    re->rev = e;
    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    scanf("%d%d%d", &n, &Q, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d%d", A + i, S + i, C + i, X + i);
    for (int i = 1; i <= k; i++) {
        scanf("%d", R + i);
        m = max(m, R[i]);
    }
    s = n + m + 1;
    t = s + 1;
}

void setup() {
    for (int i = 1; i <= n; i++) {
        link(s, i, S[i], 1);
        link(s, i, 0, INF);

        if (X[i] == 0)
            link(i, s - 1, A[i], C[i]);
        else {
            int j;
            for (j = 1; j < m && j * X[i] <= C[i]; j++)
                link(i, n + j, A[i], X[i]);
            link(i, n + j, A[i], C[i] - (j - 1) * X[i]);
        }
    }

    for (int i = 1; i < m; i++)
        link(n + i + 1, n + i, 0, INF);
}

int main() {
    initialize();
    setup();

    for (int i = 1; i <= m; i++) {
        link(n + i, t, 0, Q);
        ans[i] = ans[i - 1] + maxflow();
    }

    for (int i = 1; i <= k; i++)
        printf("%lld\n", ans[R[i]]);

    return 0;
}
