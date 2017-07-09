#define USE_FILE_IO

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFER_SIZE 65536
static unsigned _i = BUFFER_SIZE;
static char buffer[BUFFER_SIZE];
inline char _getchar() {
    if (_i == BUFFER_SIZE) {
        _i = 0;
        fread(buffer, 1, BUFFER_SIZE, stdin);
    }

    return buffer[_i++];
}

template <typename TInteger>
inline TInteger read() {
    TInteger x = 0;
    char c = _getchar();
    while (c < '0' or c > '9')
        c = _getchar();
    while ('0' <= c and c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }
    return x;
}

#define NMAX 100000

typedef long long ntype;

struct Edge {
    Edge(int _to, ntype _w) : to(_to), w(_w) {}

    int to;
    ntype w;
};  // struct Edge

static int n, m;
static vector<Edge *> G[NMAX + 10];
static vector<int> children[NMAX + 10];
static int father[NMAX + 10];
static ntype weight[NMAX + 10];
static ntype sum[NMAX + 10];
static int son[NMAX + 10];
static ntype size[NMAX + 10];
static int top[NMAX + 10];
static int location[NMAX + 10];
static int cnt;

static void set_root(int x) {
    size[x] = 1;

    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (not size[v]) {
            children[x].push_back(v);
            father[v] = x;
            weight[v] = e->w;
            set_root(v);

            size[x] += size[v];
            sum[x] += e->w + sum[v];
            if (size[v] > size[son[x]]) {
                son[x] = v;
            }
        }
    }  // for
}

static void _decompose(int x) {
    if (son[x]) {
        int v = son[x];
        top[v] = top[x];
        location[v] = ++cnt;

        _decompose(v);
    }

    for (unsigned i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        if (v != son[x]) {
            top[v] = v;
            location[v] = ++cnt;

            _decompose(v);
        }
    }  // for
}

static void decompose(int x) {
    top[x] = x;
    _decompose(x);
}

static ntype a[NMAX + 10];
static ntype b[NMAX + 10];
static ntype ab[NMAX + 10];

static void prepare() {
    for (int i = 2; i <= n; i++) {
        a[location[i]] = sum[i];
        b[location[i]] = sum[1] - sum[i] - weight[i];
        ab[location[i]] = a[location[i]] * b[location[i]];
    }  // for
}

struct Node {
    struct Mark {
        Mark() : a(0), b(0) {}

        ntype a, b;
    };  // struct Mark

    struct Sum {
        Sum() : ab(0), a(0), b(0) {}

        ntype ab, a, b;
    };  // struct Sum

    ntype left, right;
    Mark mark;
    Sum sum;

    Node *leftchild, *rightchild;

    ntype size() const {
        return right - left + 1;
    }
};  // struct Node

inline ntype sum_a(Node *x) {
    return x->sum.a + x->mark.a * x->size();
}

inline ntype sum_b(Node *x) {
    return x->sum.b + x->mark.b * x->size();
}

inline ntype sum_ab(Node *x) {
    return x->sum.ab + x->mark.a * x->sum.b + x->mark.b * x->sum.a +
           x->mark.a * x->mark.b * x->size();
}

inline void pushdown(Node *x) {
    if (x->mark.a != 0 || x->mark.b != 0) {
        x->sum.a += x->mark.a * x->size();
        x->sum.b += x->mark.b * x->size();
        x->sum.ab += x->mark.a * x->sum.b + x->mark.b * x->sum.a +
                     x->mark.a * x->mark.b * x->size();
        x->leftchild->mark.a += x->mark.a;
        x->leftchild->mark.b += x->mark.b;
        x->rightchild->mark.a += x->mark.a;
        x->rightchild->mark.b += x->mark.b;
        x->mark.a = 0;
        x->mark.b = 0;
    }
}

inline void update(Node *x) {
    x->sum.a = sum_a(x->leftchild) + sum_a(x->rightchild);
    x->sum.b = sum_b(x->leftchild) + sum_b(x->rightchild);
    x->sum.ab = sum_ab(x->leftchild) + sum_ab(x->rightchild);
}

static void modify(Node *x, ntype left, ntype right, ntype deta_a,
                   ntype deta_b) {
    if (right < x->left or left > x->right) {
        return;
    }

    if (left <= x->left and x->right <= right) {
        x->mark.a += deta_a;
        x->mark.b += deta_b;
    } else {
        pushdown(x);
        ntype mid = (x->left + x->right) / 2;
        if (right <= mid) {
            modify(x->leftchild, left, right, deta_a, deta_b);
        } else if (left > mid) {
            modify(x->rightchild, left, right, deta_a, deta_b);
        } else {
            modify(x->leftchild, left, right, deta_a, deta_b);
            modify(x->rightchild, left, right, deta_a, deta_b);
        }

        update(x);
    }
}

static Node *build(ntype left, ntype right) {
    if (left == right) {
        Node *x = new Node;
        x->left = x->right = left;
        x->leftchild = x->rightchild = NULL;
        x->sum.a = a[left];
        x->sum.b = b[left];
        x->sum.ab = ab[left];

        return x;
    }

    ntype mid = (left + right) / 2;
    Node *x = new Node;
    x->left = left;
    x->right = right;
    x->leftchild = build(left, mid);
    x->rightchild = build(mid + 1, right);
    update(x);

    return x;
}

static void initialize() {
    n = read<int>();
    m = read<int>();

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        ntype w;
        u = read<int>();
        v = read<int>();
        w = read<ntype>();

        G[u].push_back(new Edge(v, w));
        G[v].push_back(new Edge(u, w));
    }  // for

    set_root(1);
    decompose(1);
    prepare();
}

static Node *tree;

int main() {
#ifdef USE_FILE_IO
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
#endif
    initialize();
    tree = build(1, n - 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        ntype w;
        u = read<int>();
        v = read<int>();
        w = read<ntype>();

        if (father[v] == u)
            u = v;

        ntype deta = w - weight[u];
        weight[u] = w;

        tree->mark.b += deta;
        modify(tree, location[u], location[u], 0, -deta);

        int x = father[u];
        while (x) {
            int t = top[x];
            modify(tree, location[t], location[x], deta, -deta);

            x = father[t];
        }  // while

        printf("%lld\n", sum_ab(tree));
    }  // for

    return 0;
}  // function main
