#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define INF (1LL << 61)

typedef long long i64;

static int n;
static i64 k;

struct Edge {
    Edge(int _v, i64 _w)
        : v(_v), r(_w), w(_w - k) {}

    int v;
    i64 r, w, a, b;
};

static vector<Edge> G[NMAX + 10];

void initialize() {
    scanf("%d%lld", &n, &k);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        i64 w;
        scanf("%d%d%lld", &u, &v, &w);
        G[u].push_back(Edge(v, w));
        G[v].push_back(Edge(u, w));
    }
}

#undef NULL

struct Node {
    int weight;
    i64 w, a, b;
    i64 dw, da, db;
    i64 mina, minb;
    Node *lch, *rch;

    i64 gmina() {
        return mina + da;
    }

    i64 gminb() {
        return minb + db;
    }

    void pushdown() {
        if (dw) {
            w += dw;
            lch->dw += dw;
            rch->dw += dw;
            dw = 0;
        }

        if (da) {
            a += da;
            mina += da;
            lch->da += da;
            rch->da += da;
            da = 0;
        }

        if (db) {
            b += db;
            minb += db;
            lch->db += db;
            rch->db += db;
            db = 0;
        }
    }

    void update() {
        mina = min(a, min(lch->gmina(), rch->gmina()));
        minb = min(b, min(lch->gmina(), rch->gmina()));
    }
};

void split(Node *x, i64 key, Node *&a, Node *&b, Node *&c) {
    if (!x) {
        a = NULL;
        b = NULL;
        c = NULL;
        return;
    }

    x->pushdown();
    if (key < x->w) {
    } else if (key > x->w) {
    } else {
        a = x->lch;
        b = x;
        c = x->rch;
        x->lch = x->rch = NULL;
        x->mina = x->a;
        x->minb = x->b;
    }
}

#define MEMMAX 3000000
static size_t mempos;
static Node mem[MEMMAX];

inline Node *alloc() {
    Node *x = mem + mempos;
    mempos++;
    x->w = x->a = x->b = x->dw = x->da = x->db = 0;
    x->lch = x->rch = NULL;
    x->mina = x->minb = INF;
    return x;
}

i64 solve() {
}

int main() {
    srand(time(0));
    for (int i = 0; i < MEMMAX; i++) {
        mem[i].weight = rand();
    }

    // freopen("ex_soda1.in", "r", stdin);
    initialize();

    i64 l = 0, r = 1e13;
    while (l < r) {
        i64 m = (l + r) / 2 + 1;

        for (int u = 1; u <= n; u++) {
            for (auto &e : G[u]) {
                e.a = e.r - m - k;
                e.b = k - m - e.r;
            }
        }

        if (solve() < 0)
            r = m - 1;
        else
            l = m;
    }

    printf("%lld\n", l);

    return 0;
}
