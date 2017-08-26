#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

#undef NULL

using namespace std;

#define NMAX 100000

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};

struct Pair {
    Pair(int _x, i64 _dis)
        : x(_x), dis(_dis) {}

    int x;
    i64 dis;

    bool operator<(const Pair &b) const {
        return dis > b.dis;
    }
};

struct Node {
    bool has;
    Node *lch, *rch;

    void update() {
        has = lch->has | rch->has;
    }
};

static Node *NULL;

Node *modify(Node *x, int pos, int l, int r) {
    x = new Node(*x);

    if (l == r)
        x->has = true;
    else {
        int m = (l + r) >> 1;
        
        if (pos <= m)
            x->lch = modify(x->lch, pos, l, m);
        else
            x->rch = modify(x->rch, pos, m + 1, r);

        x->update();
    }

    return x;
}

int query(Node *x, int l, int r, int a, int b) {
    if (a <= l && r <= b) {
        if (x->has) {
            while (l < r) {
                int m = (l + r) >> 1;

                if (x->rch->has) {
                    x = x->rch;
                    l = m + 1;
                } else {
                    x = x->lch;
                    r = m;
                }
            }

            return l;
        } else
            return 0;
    } else {
        int m = (l + r) >> 1;
        int ret = 0;

        if (b > m)
            ret = query(x->rch, m + 1, r, a, b);
        if (ret)
            return ret;
        if (a <= m)
            ret = query(x->lch, l, m, a, b);
        return ret;
    }
}

static int n, m, q, s, t, lastans;
static int col[NMAX + 10];
static i64 dist[NMAX + 10];
static int fa[NMAX + 10], depth[NMAX + 10];
static int size[NMAX + 10], top[NMAX + 10], nxt[NMAX + 10];
static int in[NMAX + 10], out[NMAX + 10], id[NMAX + 10], cur;
static vector<Edge *> G[NMAX + 10];
static vector<int> T[NMAX + 10], D[NMAX + 10], up[NMAX + 10];
static vector<int> bucket[NMAX + 10];
static Node *pre[NMAX + 10], *suf[NMAX + 10];

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    priority_queue<Pair> q;
    q.push(Pair(s, 0));
    while (!q.empty()) {
        Pair u = q.top();
        q.pop();

        if (dist[u.x] != u.dis)
            continue;

        for (size_t i = 0; i < G[u.x].size(); i++) {
            Edge *e = G[u.x][i];
            int v = e->either(u.x);

            if (dist[v] > dist[u.x] + e->w) {
                dist[v] = dist[u.x] + e->w;
                q.push(Pair(v, dist[v]));
            }
        }
    }
}

bool cmp(int a, int b) {
    return col[a] < col[b];
}

void dfs(int u) {
    size[u] = in[u] = 1;
    for (size_t i = 0; i < D[u].size(); i++) {
        int v = D[u][i];

        if (!in[v]) {
            T[u].push_back(v);
            depth[v] = depth[u] + 1;
            fa[v] = u;
            dfs(v);
            size[u] += size[v];
        } else
            up[v].push_back(u);
    }
}

void decompose(int u) {
    in[u] = ++cur;
    id[cur] = u;
    for (size_t i = 0; i < T[u].size(); i++) {
        int v = T[u][i];

        if (size[v] > size[nxt[u]])
            nxt[u] = v;
    }

    if (nxt[u]) {
        top[nxt[u]] = top[u];
        decompose(nxt[u]);
    }

    for (size_t i = 0; i < T[u].size(); i++) {
        int v = T[u][i];

        if (v == nxt[u])
            continue;

        top[v] = v;
        decompose(v);
    }

    out[u] = cur;
}

void build() {
    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            if (dist[u] + e->w == dist[v])
                D[u].push_back(v);
        }

        sort(D[u].begin(), D[u].end(), cmp);
    }

    dfs(s);
    memset(in, 0, sizeof(in));
    top[s] = s;
    decompose(s);

    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < up[u].size(); i++) {
            int v = up[u][i];
            bucket[in[v]].push_back(in[u]);
        }
    }

    pre[0] = suf[n + 1] = NULL;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        for (size_t j = 0; j < bucket[i].size(); j++) {
            int v = bucket[i][j];
            pre[i] = modify(pre[i], v, 1, n);
        }
    }

    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1];
        for (size_t j = 0; j < bucket[i].size(); j++) {
            int v = bucket[i][j];
            suf[i] = modify(suf[i], v, 1, n);
        }
    }
}

void initialize() {
    NULL = new Node;
    NULL->has = false;
    NULL->lch = NULL->rch = NULL;

    scanf("%d%d%d%d", &n, &m, &s, &t);

    for (int i = 1; i <= n; i++) {
        scanf("%d", col + i);
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        if (u == v)
            continue;

        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }
}

int main() {
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
    initialize();
    dijkstra();
    build();
    
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (t) {
            u ^= lastans;
            v ^= lastans;
        }

        if (in[v] <= in[u] || out[u] < in[v])
            continue;

        int p = v;
        while (true) {
            if (top[u] == top[p]) {
                p = nxt[u];
                break;
            }

            if (fa[p] == u)
                break;

            if (p != top[p])
                p = top[p];
            else
                p = fa[p];
        }

        Node *seg1 = pre[in[p] - 1], *seg2 = suf[out[p] + 1];
        while (true) {
            int r = in[v], l = max(in[u], in[top[v]]);
            int ret = max(
                query(seg1, 1, n, l, r),
                query(seg2, 1, n, l, r)
            );

            if (ret) {
                v = id[ret];
                break;
            }

            if (top[u] == top[v]) {
                v = u;
                break;
            } else
                v = fa[top[v]];
        }

        lastans = depth[v] - depth[u];
        printf("%d\n", lastans);
    }

    return 0;
}
