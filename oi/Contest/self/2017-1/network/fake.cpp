#define NDEBUG

#include <cassert>
#include <cstring>

#include <vector>
#include <algorithm>

#include "network.h"

using namespace std;

#define NMAX 100000
#define QMAX 200000
#define STACKSIZE 32

class UnionFind {
 public:
    void reset(int n) {
        _component_count = n;

        memset(_set, 0, sizeof(_set));
    }

    int find_root(int x) const {
        while (_set[x]) {
            x = _set[x];
        }

        return x;
    }

    void link(int x, int y) {
        assert(find_root(x) != find_root(y));
        assert(x == find_root(x));
        assert(y == find_root(y));

        _set[y] = x;
        _component_count--;
    }

    void cut(int x, int y) {
        assert(_set[x] == y || _set[y] == x);

        if (_set[x] == y)
            swap(x, y);

        _set[y] = 0;
        _component_count++;
    }

    int component_count() const {
        return _component_count;
    }

 private:
    int _set[NMAX + 1];
    int _component_count;
};

struct Edge {
    Edge (int _u, int _v)
        : u(_u), v(_v), idu(0), idv(0) {}

    int u, v;
    int idu, idv;
};

class IntervalTree {
 public:
    struct Node {
        Node (int l, int r)
            : left(l), right(r), marked(false),
              leftchild(nullptr),
              rightchild(nullptr) {}

        int left, right;
        bool marked;
        vector<Edge *> edges;
        Node *leftchild;
        Node *rightchild;
    };

    void reset(int left, int right) {
        _root = _build(left, right);
    }

    void modify(int left, int right, Edge *e) {
        _modify(_root, left, right, e);
    }

    Node *root() {
        return _root;
    }

 private:
    Node *_root;

    Node *_build(int left, int right) {
        Node *x = new Node(left, right);

        if (left < right) {
            int mid = (left + right) / 2;
            x->leftchild = _build(left, mid);
            x->rightchild = _build(mid + 1, right);
        }

        return x;
    }

    void _modify(Node *x, int left, int right, Edge *e) {
        if (left <= x->left && x->right <= right)
            x->edges.push_back(e);
        else {
            int mid = (x->left + x->right) / 2;

            if (left <= mid)
                _modify(x->leftchild, left, right, e);
            if (right > mid)
                _modify(x->rightchild, left, right, e);
        }
    }
};

static int current;
static UnionFind uf;
static IntervalTree tree;
static int answer[QMAX + 1];
static int stkpos;
static IntervalTree::Node *stk[STACKSIZE];

inline void add_node(IntervalTree::Node *x) {
    for (size_t i = 0; i < x->edges.size(); i++) {
        Edge *e = x->edges[i];

        e->idu = uf.find_root(e->u);
        e->idv = uf.find_root(e->v);
        if (e->idu == e->idv) {
            e->idu = e->idv = 0;
            continue;
        }

        uf.link(e->idu, e->idv);
    }
}

inline void del_node(IntervalTree::Node *x) {
    for (size_t i = 0; i < x->edges.size(); i++) {
        Edge *e = x->edges[i];

        if (e->idu != 0) {
            assert(e->idv != 0);
            uf.cut(e->idu, e->idv);
        }
    }
}

static void dfs() {
    while (stkpos) {
        auto x = stk[stkpos];

        if (!x->marked) {
            if (x->left < x->right) {
                if (!x->leftchild->marked) {
                    add_node(x->leftchild);

                    stk[++stkpos] = x->leftchild;
                    continue;
                } else if (!x->rightchild->marked) {
                    add_node(x->rightchild);

                    stk[++stkpos] = x->rightchild;
                    continue;
                }
            } else
                answer[x->left] = uf.component_count();
        }

        x->marked = true;

        if (x->right == current)
            return;

        del_node(x);
        stkpos--;
    }
}

void initialize(int n, int q) {
    uf.reset(n);
    tree.reset(1, q);

    stkpos = 1;
    stk[1] = tree.root();
}

void add_connection(int u, int v, int t) {
    current++;
    Edge *e = new Edge(u, v);
    tree.modify(current, current + t - 1, e);

    if (current == 1)
        add_node(stk[1]);
}

int query() {
    dfs();
    return answer[current];
}

void finalize() {}
