#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned long long u64;

#define NMAX 200000
#define BASE 19260817

u64 pw[NMAX + 10];

struct Node {
    int l, r;
    u64 hash;
    Node *lch, *rch;

    Node(int _l, int _r) : l(_l), r(_r), hash(0), lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
        }
    }

    void update() {
        hash = lch->hash * pw[rch->r - rch->l + 1] + rch->hash;
    }

    void print() {
        if (l == r)
            putchar(hash);
        else {
            lch->print();
            rch->print();
        }
    }
};

Node *modify(Node *x, int i, int v) {
    x = new Node(*x);
    if (x->l == x->r) x->hash = v;
    else {
        if (i <= x->lch->r)
            x->lch = modify(x->lch, i, v);
        else
            x->rch = modify(x->rch, i, v);
        x->update();
    }
    return x;
}

int cmp(Node *x, Node *y) {
    if (x->hash == y->hash)
        return 0;
    if (x->l == x->r)
        return x->hash < y->hash ? -1 : 1;
    return x->lch->hash != y->lch->hash ? cmp(x->lch, y->lch) : cmp(x->rch, y->rch);
}

struct Edge {
    int v;
    char c;
};

int n, m;
bool mark[NMAX + 10];
int to[NMAX + 10];
int dist[NMAX + 10];
vector<Edge> G[NMAX + 10];
Node *tr[NMAX + 10];

int main() {
    pw[0] = 1;
    for (int i = 1; i <= NMAX; i++)
        pw[i] = pw[i - 1] * BASE;

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        char buf[8];
        scanf("%d%d%s", &u, &v, buf);
        G[u].push_back({v, buf[0]});
        G[v].push_back({u, buf[0]});
    }

    queue<int> q;
    q.push(1);
    dist[1] = 1;
    do {
        int u = q.front();
        q.pop();
        for (auto &e : G[u]) {
            int v = e.v;
            if (!dist[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    } while (!q.empty());

    q.push(n);
    mark[n] = true;
    tr[n] = new Node(1, dist[n] - 1);
    do {
        int u = q.front();
        q.pop();
        for (auto &e : G[u]) {
            int v = e.v;
            if (!mark[v] && dist[v] + 1 == dist[u]) {
                mark[v] = true;
                q.push(v);
            }
        }

        char c = 'z' + 1;
        for (auto &e : G[u]) {
            int v = e.v;
            if (dist[u] + 1 != dist[v])
                continue;
            if (!tr[v])
                continue;
            if (e.c < c) {
                c = e.c;
                to[u] = v;
                tr[u] = tr[v];
            } else if (e.c == c) {
                if (!tr[u] || cmp(tr[v], tr[u]) < 0) {
                    to[u] = v;
                    tr[u] = tr[v];
                }
            }
        }

        if (tr[u])
            tr[u] = modify(tr[u], dist[u], c);
    } while (!q.empty());

    printf("%d\n", dist[n] - 1);
    for (int x = 1; x; x = to[x])
        printf("%d ", x);
    puts("");
    tr[1]->print();
    puts("");
    return 0;
}