#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define BASE 434009

typedef unsigned long long u64;

struct Node {
    u64 hash;
    Node *lch, *rch;

    void update() {
        hash = lch->hash + rch->hash * BASE;
    }
};

static Node *null = new Node;

Node *alloc() {
    Node *x = new Node;
    x->hash = 0;
    x->lch = x->rch = null;
    return x;
}

Node *insert(Node *x, int pos, int l, int r) {
    x = x == null ? alloc() : new Node(*x);

    if (l == r)
        x->hash++;
    else {
        int m = (l + r) >> 1;

        if (pos <= m)
            x->lch = insert(x->lch, pos, l, m);
        else
            x->rch = insert(x->rch, pos, m + 1, r);

        x->update();
    }

    return x;
}

bool is_leaf(Node *x) {
    return x->lch == null && x->rch == null;
}

static int n, m;
static int id[NMAX + 10];
static int name[NMAX + 10];
static int col[NMAX + 10];
static bool marked[NMAX + 10];
static Node *dist[NMAX + 10];
static vector<int> G[NMAX + 10];

bool cmp(Node *x, Node *y) {
    int l = 1, r = n;
    while (l < r) {
        int m = (l + r) >> 1;
        if (x->lch->hash == y->lch->hash) {
            x = x->rch;
            y = y->rch;
            l = m + 1;
        } else {
            x = x->lch;
            y = y->lch;
            r = m;
        }
    }

    return x->hash < y->hash;
}

struct Pair {
    Pair(int _x, Node *_dis) : x(_x), dis(_dis) {}

    int x;
    Node *dis;

    bool operator<(const Pair &b) const {
        return cmp(b.dis, dis);
    }
};

void print(Node *x, int l, int r) {
    if (l == r) {
        for (int i = 0; i < x->hash; i++) {
            printf("%d ", name[l]);
        }
    } else {
        int m = (l + r) >> 1;
        print(x->lch, l, m);
        print(x->rch, m + 1, r);
    }
}

void initialize() {
    null->lch = null->rch = null;
    scanf("%d%d", &n, &m);

    int u, v;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &u);
        id[u] = i;
        name[i] = u;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", &u);
        col[i] = id[u];
    }

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

int main() {
    initialize();

    priority_queue<Pair> q;
    dist[1] = insert(null, col[1], 1, n);
    q.push(Pair(1, dist[1]));
    while (!q.empty()) {
        Pair u = q.top();
        q.pop();

        if (u.dis != dist[u.x])
            continue;

        marked[u.x] = true;
        for (size_t i = 0; i < G[u.x].size(); i++) {
            int v = G[u.x][i];

            if (marked[v])
                continue;

            Node *nd = insert(dist[u.x], col[v], 1, n);
            if (!dist[v] || cmp(nd, dist[v])) {
                dist[v] = nd;
                q.push(Pair(v, nd));
            }
        }
    }

    print(dist[n], 1, n);
    putchar('\n');

    return 0;
}
