// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 10000

namespace Treap {

#define SEED (233)
static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

static int tree[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];
static int size[NMAX + 10];
static int mark[NMAX + 10];
static int value[NMAX + 10];
static int weight[NMAX + 10];

static void initialize() {
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(mark, 0, sizeof(mark));
    memset(value, 0, sizeof(value));
    memset(tree, 0, sizeof(tree));

    for (unsigned i = 1; i <= NMAX; i++) {
        size[i] = 1;
        weight[i] = randint();
    }  // for
    size[0] = 0;
    weight[0] = INT_MAX;
}

inline void update(int x) {
    size[x] = size[left[x]] + size[right[x]] + 1;
}

inline void pushdown(int x) {
    if (mark[x] != 0) {
        value[x] += mark[x];
        mark[left[x]] += mark[x];
        mark[right[x]] += mark[x];
        mark[x] = 0;
    }
}

inline int left_rotate(int x) {
    int y = left[x];
    left[x] = right[y];
    right[y] = x;

    update(x);
    update(y);
    return y;
}

inline int right_rotate(int x) {
    int y = right[x];
    right[x] = left[y];
    left[y] = x;

    update(x);
    update(y);
    return y;
}

static int insert(int x, int y) {
    if (!x) {
        return y;
    }

    assert(mark[y] == 0);
    pushdown(x);
    if (value[y] < value[x]) {
        left[x] = insert(left[x], y);

        if (weight[left[x]] < weight[x]) {
            x = left_rotate(x);
        }
    } else {
        right[x] = insert(right[x], y);

        if (weight[right[x]] < weight[x]) {
            x = right_rotate(x);
        }
    }

    update(x);
    return x;
}

static bool contain(int x, int v) {
    if (!x) {
        return false;
    }

    pushdown(x);
    if (v < value[x]) {
        return contain(left[x], v);
    } else if (v > value[x]) {
        return contain(right[x], v);
    } else {
        return true;
    }
}

static int merge(int x, int y) {
    if (!y) {
        return x;
    }

    pushdown(y);
    int lc = left[y];
    int rc = right[y];
    left[y] = right[y] = 0;
    size[y] = 1;
    x = insert(x, y);

    x = merge(x, lc);
    x = merge(x, rc);

    return x;
}

}  // namespace Treap

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) const {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, k;
static vector<Edge *> G[NMAX + 10];
static bool marked[NMAX + 10];

inline void add_edge(int u, int v, int c) {
    Edge *e = new Edge(u, v, c);

    G[u].push_back(e);
    G[v].push_back(e);
}

static void read_graph() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int a, b;
        while (scanf("%d", &a) && a) {
            scanf("%d", &b);
            add_edge(i, a, b);
        }  // while
    }      // for
}

static void initialize() {
    read_graph();
}

static bool process(int x, int y) {
    using namespace Treap;
    if (!y) {
        return false;
    }

    pushdown(y);
    if (contain(x, k - value[y])) {
        return true;
    } else {
        return process(x, left[y]) || process(x, right[y]);
    }
}

static bool solve(int x) {
    using namespace Treap;
    marked[x] = true;

    bool flag = false;
    int mx = 0;
    for (unsigned i = 0; not flag && i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (not marked[v]) {
            flag = solve(v);

            mark[tree[v]] += e->w;
            if (size[tree[v]] > size[tree[x]]) {
                tree[x] = tree[v];
                mx = v;
            }
        }
    }  // for

    if (not flag && tree[x] != 0) {
        for (unsigned i = 0; not flag && i < G[x].size(); i++) {
            Edge *e = G[x][i];
            int v = e->either(x);

            if (not marked[v]) {
                if (v != mx) {
                    flag = process(tree[x], tree[v]);
                    tree[x] = merge(tree[x], tree[v]);
                }
            }
        }  // for

        if (not flag) {
            flag = contain(tree[x], k);
            tree[x] = insert(tree[x], x);
        }
    }

    if (tree[x] == 0) {
        tree[x] = x;
    }

    marked[x] = false;
    return flag;
}

int main() {
    initialize();

    while (scanf("%d", &k) && k) {
        memset(marked, false, sizeof(marked));
        Treap::initialize();

        if (solve(1)) {
            puts("AYE");
        } else {
            puts("NAY");
        }
    }  // while
    puts(".");

    return 0;
}  // function main
