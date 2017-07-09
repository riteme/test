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

                if (x->lch->has) {
                    x = x->lch;
                    r = m;
                } else {
                    x = x->rch;
                    l = m + 1;
                }
            }

            return l;
        } else
            return 0;
    } else {
        int m = (l + r) >> 1;
        int ret = 0;

        if (a <= m)
            ret = query(x->lch, l, m, a, b);
        if (ret)
            return ret;
        if (b > m)
            ret = query(x->rch, m + 1, r, a, b);
        return ret;
    }
}

static int n, m, q, s, t, lastans;
static int col[NMAX + 10];
static i64 dist[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

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
    initialize();
    dijkstra();
    
    scanf("%d", &q);
    while (q--) {
    }

    return 0;
}
