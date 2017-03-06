// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

// typedef unsigned long long u64;
typedef long long i64;

struct Point {
    int x, y;
};

static int mode;
bool cmp(const Point &a, const Point &b) {
    if (mode)
        return a.x < b.x;
    return a.y < b.y;
}

class KDTree {
 public:
    KDTree(Point *seq, int n) {
        root = _build(1, n, seq, 1);
    }

    void modify_x(int left, int right, i64 v) {
        _modify_x(root, left, right, v, 1);
    }

    i64 query_y(int left, int right) {
        return _query_y(root, left, right, 1);
    }

 private:
    struct Node {
        Node(int _x, int _y)
            : x(_x), y(_y),
              xmin(_x), xmax(_x),
              ymin(_y), ymax(_y),
              value(0), sum(0),
              mark(0), size(1),
              left(NULL), right(NULL) {}

        int x, y;
        int xmin, xmax;
        int ymin, ymax;
        i64 value;
        i64 sum;
        i64 mark;
        i64 size;
        Node *left;
        Node *right;

        i64 get_sum() {
            return sum + mark * size;
        }

        i64 get_val() {
            return value + mark;
        }

        void pushdown() {
            if (mark) {
                value += mark;
                sum += mark * size;

                if (left)
                    left->mark += mark;
                if (right)
                    right->mark += mark;

                mark = 0;
            }
        }

        void update() {
            sum = value + (left ? left->get_sum() : 0)
                        + (right ? right->get_sum() : 0);
        }
    };

    Node *root;

    Node *_build(int left, int right, Point *seq, int axis) {
        if (right < left)
            return NULL;

        mode = axis;
        sort(seq + left, seq + right + 1, cmp);

        int mid = (left + right) / 2;
        Node *x = new Node(seq[mid].x, seq[mid].y);
        x->left = _build(left, mid - 1, seq, axis ^ 1);
        x->right = _build(mid + 1, right, seq, axis ^ 1);

        x->xmin = min(x->xmin,
                      min(x->left ? x->left->xmin : x->xmin,
                          x->right ? x->right->xmin : x->xmin)
                     );
        x->xmax = max(x->xmax,
                      max(x->left ? x->left->xmax : x->xmax,
                          x->right ? x->right->xmax : x->xmax)
                     );
        x->ymin = min(x->ymin,
                      min(x->left ? x->left->ymin : x->ymin,
                          x->right ? x->right->ymin : x->ymin)
                     );
        x->ymax = max(x->ymax,
                      max(x->left ? x->left->ymax : x->ymax,
                          x->right ? x->right->ymax : x->ymax)
                     );
        x->size += (x->left ? x->left->size : 0) +
                   (x->right ? x->right->size : 0);

        return x;
    }

    void _modify_x(Node *x, int left, int right, i64 v, int axis) {
        if (!x)
            return;
        if (left <= x->xmin && x->xmax <= right)
            x->mark += v;
        else {
            x->pushdown();

            if (left <= x->x && x->x <= right)
                x->value += v;

            if (axis) {
                if (left < x->x)
                    _modify_x(x->left, left, right, v, 0);
                if (right > x->x)
                    _modify_x(x->right, left, right, v, 0);
            } else {
                _modify_x(x->left, left, right, v, 1);
                _modify_x(x->right, left, right, v, 1);
            }

            x->update();
        }
    }

    i64 _query_y(Node *x, int left, int right, int axis) {
        if (!x)
            return 0;
        if (left <= x->ymin && x->ymax <= right)
            return x->get_sum();

        x->pushdown();

        i64 ret = 0;
        if (left <= x->y && x->y <= right)
            ret = x->get_val();
        
        if (axis) {
            ret += _query_y(x->left, left, right, 0);
            ret += _query_y(x->right, left, right, 0);
        } else {
            if (left < x->y)
                ret += _query_y(x->left, left, right, 1);
            if (right > x->y)
                ret += _query_y(x->right, left, right, 1);
        }

        return ret;
    }
};

static int n, q, root;
static vector<int> G[NMAX + 10];
static i64 weight[NMAX + 10];
static i64 initial[NMAX + 10];
static int cnt;
static int size[NMAX + 10];
static int father[NMAX + 10];
static int top[NMAX + 10];
static int id[NMAX + 10];
static Point seq[NMAX + 10];
static KDTree *tree;

void dfs(int x, int f) {
    size[x] = 1;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == f)
            continue;

        father[v] = x;
        dfs(v, x);
        size[x] += size[v];
    }
}

void decompose(int x, int f) {
    int next = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == f)
            continue;
        if (size[v] > size[next])
            next = v;
    }

    if (next) {
        top[next] = top[x];
        id[next] = ++cnt;
        decompose(next, x);
    }

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == f || v == next)
            continue;

        top[v] = v;
        id[v] = ++cnt;
        decompose(v, x);
    }
}

void modify(int u, i64 v) {
    i64 delta = v - weight[u];
    weight[u] = v;
    while (u) {
        tree->modify_x(id[top[u]], id[u], delta);
        u = father[top[u]];
    }
}

i64 query(int left, int right) {
    return tree->query_y(left, right);
}

void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", initial + i);
    }

    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u) {
            G[u].push_back(v);
            G[v].push_back(u);
        } else
            root = v;
    }

    dfs(root, 0);
    top[root] = root;
    id[root] = ++cnt;
    decompose(root, 0);

    for (int i = 1; i <= n; i++) {
        seq[i].x = id[i];
        seq[i].y = i;
    }
    tree = new KDTree(seq, n);

    for (int i = 1; i <= n; i++) {
        modify(i, initial[i]);
    }
}

int main() {
    initialize();

    while (q--) {
        int op, a, b;
        scanf("%d%d%d", &op, &a, &b);

        if (op == 1)
            modify(a, b);
        else
            printf("%lld\n", query(a, b));
    }

    return 0;
}
