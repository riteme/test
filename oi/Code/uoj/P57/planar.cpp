// #define NDEBUG

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define DEBUG(fmt, ...) printf(fmt, __VA_ARGS__)
#define DEBUG_PUTS(str) puts(str);
#else
#define DEBUG
#define DEBUG_PUTS
#endif

#define NMAX 100000
#define LOGN 17

#define EPSILON 0.00000001

template <typename T>
inline bool equ(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

struct Vector {
    Vector() : x(0.0), y(0.0) {}
    Vector(const double _x, const double _y)
        : x(_x), y(_y) {}

    double x, y;

    double tangent() const {
        return y / x;
    }

    friend Vector operator+(const Vector &a, const Vector &b) {
        return Vector(a.x + b.x, a.y + b.y);
    }

    friend Vector operator-(const Vector &a, const Vector &b) {
        return Vector(a.x - b.x, a.y - b.y);
    }

    friend Vector operator-(const Vector &a) {
        return Vector(-a.x, -a.y);
    }

    Vector &operator+=(const Vector &b) {
        x += b.x;
        y += b.y;

        return *this;
    }

    Vector &operator-=(const Vector &b) {
        x -= b.x;
        y -= b.y;

        return *this;
    }
};

inline double cross(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
}

inline double dot(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y;
}

inline int area_id(const Vector &a) {
    if (0 <= a.x && 0 < a.y)
        return 1;
    if (0 < a.x && 0 >= a.y)
        return 2;
    if (0 >= a.x && 0 > a.y)
        return 3;
    return 4;
}

struct Edge {
    Edge(int _u, int _v, int _w);

    int u, v, w;
    int dual_id;
    Edge *reverse_edge;
    Edge *next;
};

struct Point {
    Vector pos;
    int dual_id;
};

static int n, m, q, dual_cnt;
static Vector position[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static Point qu[NMAX + 10], qv[NMAX + 10];

Edge::Edge(int _u, int _v, int _w)
    : u(_u), v(_v), w(_w),
      dual_id(0),
      reverse_edge(nullptr),
      next(nullptr) {}

inline void link(int u, int v, int w) {
    Edge *e1 = new Edge(u, v, w);
    Edge *e2 = new Edge(v, u, w);
    e1->reverse_edge = e2;
    e2->reverse_edge = e1;
    G[u].push_back(e1);
    G[v].push_back(e2);
}

void dfs(Edge *e, int id) {
    if (e->dual_id)
        return;

    DEBUG(" -> %d", e->v);
    e->dual_id = id;
    dfs(e->reverse_edge->next, id);
}

void decompose() {
    // Sort all edges in CW order
    for (int u = 1; u <= n; u++) {
        sort(G[u].begin(), G[u].end(),
            [u](const Edge *a, const Edge *b) {
                Vector va = position[a->v] - position[u];
                Vector vb = position[b->v] - position[u];
                int ida = area_id(va);
                int idb = area_id(vb);
                
                if (ida != idb)
                    return ida < idb;
                return cross(va, vb) < 0;
            });

        for (size_t i = 0; i < G[u].size(); i++) {
            if (i != G[u].size() - 1)
                G[u][i]->next = G[u][i + 1];
            else
                G[u][i]->next = G[u][0];
        }
    }

    // Split planar graph
    int p = 1;
    for (int u = 2; u <= n; u++) {
        if (position[u].x < position[p].x)
            p = u;
    }

    Edge *start = nullptr;
    for (auto e : G[p]) {
        if (!start ||
            cross(
                position[start->v] - position[p],
                position[e->v] - position[p]
            ) > 0)
            start = e;
    }

    DEBUG("R1: %d", p);
    dfs(start, 1);
    DEBUG_PUTS("");

    dual_cnt = 1;
    for (int u = 1; u <= n; u++) {
        for (auto e : G[u]) {
            if (!e->dual_id) {
                dual_cnt++;
                DEBUG("R%d: %d", dual_cnt, u);
                dfs(e, dual_cnt);
                DEBUG_PUTS("");
            }
        }
    }
}

enum EventType {
    DELETE,
    INSERT,
    QUERY
};

struct EventPoint {
    EventType type;
    double x;
    union {
        Edge *edge;
        Point *point;
    } data;
};

#define SEED 577777777

static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

inline bool cmp(const Edge *a, const Edge *b) {
    return (cross(position[a->v] - position[a->u],
                  position[b->u] - position[a->u]) <= 0 &&
            cross(position[a->v] - position[a->u],
                  position[b->v] - position[a->u]) <= 0) ||
           (cross(position[b->v] - position[b->u],
                  position[a->u] - position[b->u]) >= 0 &&
            cross(position[b->v] - position[b->u],
                  position[a->v] - position[b->u]) >= 0);
}

class Treap {
 public:
    Treap() : root(nullptr) {}

    void insert(Edge *key) {
        root = _insert(root, key);
    }

    void remove(Edge *key) {
        root = _remove(root, key);
    }

    Edge *lower_bound(const Vector &p) {
        return _lower_bound(root, p)->key;
    }

 private:
    struct Node {
        Node(Edge *_key)
            : weight(randint()), key(_key),
              left(nullptr), right(nullptr) {}

        int weight;
        Edge *key;
        Node *left;
        Node *right;

        Node *left_rotate() {
            Node *y = left;
            left = y->right;
            y->right = this;
            return y;
        }

        Node *right_rotate() {
            Node *y = right;
            right = y->left;
            y->left = this;
            return y;
        }
    };

    Node *root;

    Node *_insert(Node *x, Edge *key) {
        if (!x)
            return new Node(key);

        if (cmp(key, x->key)) {
            x->left = _insert(x->left, key);

            if (x->left->weight < x->weight)
                return x->left_rotate();
        } else {
            x->right = _insert(x->right, key);

            if (x->right->weight < x->weight)
                return x->right_rotate();
        }

        return x;
    }

    Node *_remove(Node *x, Edge *key) {
        assert(x);

        if (key == x->key)
            return _remove(x);
        if (cmp(key, x->key))
            x->left = _remove(x->left, key);
        else
            x->right = _remove(x->right, key);
        return x;
    }

    Node *_remove(Node *x) {
        Node *y;
        if (x->left && x->right) {
            if (x->left->weight < x->right->weight) {
                y = x->left_rotate();
                y->right = _remove(x);
            } else {
                y = x->right_rotate();
                y->left = _remove(x);
            }
        } else {
            y = x->left;
            if (x->right)
                y = x->right;

            delete x;
        }

        return y;
    }

    Node *_lower_bound(Node *x, const Vector &p) {
        if (!x)
            return nullptr;

        if (cross(position[x->key->v] - position[x->key->u],
                  p - position[x->key->u]) >= 0) {
            Node *ret = _lower_bound(x->left, p);
            return ret ? ret : x;
        } else
            return _lower_bound(x->right, p);
    }
};

static int tail;
static EventPoint seq[NMAX * 4 + 10];

void scanline() {
    // Prepare event points
    seq[0].type = INSERT;
    seq[0].x = -1;
    position[n + 1] = {-1, -1};
    position[n + 2] = {10000001, -1};
    seq[0].data.edge = new Edge(n + 1, n + 2, 0);
    seq[0].data.edge->dual_id = 1;
    tail = 1;

    for (int u = 1; u <= n; u++) {
        for (auto e : G[u]) {
            if (position[e->u].x > position[e->v].x ||
                equ(position[e->u].x, position[e->v].x))
                continue;

            seq[tail].type = INSERT;
            seq[tail].x = position[e->u].x;
            seq[tail].data.edge = e;
            tail++;
            seq[tail].type = DELETE;
            seq[tail].x = position[e->v].x;
            seq[tail].data.edge = e;
            tail++;
        }
    }

    for (int i = 1; i <= q; i++) {
        seq[tail].type = QUERY;
        seq[tail].x = qu[i].pos.x;
        seq[tail].data.point = qu + i;
        tail++;
        seq[tail].type = QUERY;
        seq[tail].x = qv[i].pos.x;
        seq[tail].data.point = qv + i;
        tail++;
    }

    // Sort event points
    sort(seq, seq + tail,
        [](const EventPoint &a, const EventPoint &b) {
            if (equ(a.x, b.x))
                return a.type < b.type;
            return a.x < b.x;
        }
    );

    // Scanline main algorithm
    Treap tree;
    for (int i = 0; i < tail; i++) {
        EventPoint &event = seq[i];

        switch (event.type) {
            case DELETE: {
                tree.remove(event.data.edge);
            } break;

            case INSERT: {
                tree.insert(event.data.edge);
            } break;

            case QUERY: {
                auto iter = tree.lower_bound(event.data.point->pos);
                event.data.point->dual_id = iter->dual_id;
                DEBUG("(%lf, %lf) locate to R%d\n",
                      event.data.point->pos.x,
                      event.data.point->pos.y,
                      event.data.point->dual_id);
            } break;
        }
    }
}

struct DirectedEdge {
    DirectedEdge(int _v, int _w)
        : v(_v), w(_w) {}

    int v, w;
};

static vector<DirectedEdge *> D[NMAX + 10];
static bool marked[NMAX + 10];
static int depth[NMAX + 10];
static int f[LOGN + 1][NMAX + 10];
static int maxv[LOGN + 1][NMAX + 10];

inline int evaluate_lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int delta = depth[u] - depth[v];
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1)
            u = f[i][u];
    }

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (f[i][u] != f[i][v]) {
            u = f[i][u];
            v = f[i][v];
        }
    }

    return f[0][u];
}

inline int evaluate_max(int u, int p) {
    int delta = depth[u] - depth[p];
    int ret = 0;
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1) {
            ret = max(ret, maxv[i][u]);
            u = f[i][u];
        }
    }

    return ret;
}

int query(int u, int v) {
    int p = evaluate_lca(u, v);

    if (u == 1 || v == 1 || !p)
        return -1;

    return max(evaluate_max(u, p), evaluate_max(v, p));
}

inline void link_dual(int u, int v, int w) {
    DirectedEdge *e1 = new DirectedEdge(v, w);
    DirectedEdge *e2 = new DirectedEdge(u, w);

    D[u].push_back(e1);
    D[v].push_back(e2);
}

static int uf[NMAX + 10];

inline int find_set(int x) {
    return uf[x] ? uf[x] = find_set(uf[x]) : x;
}

static int eu[NMAX + 10];
static int ev[NMAX + 10];
static int ew[NMAX + 10];
static int sorted[NMAX + 10];

void kruskal() {
    for (int i = 1; i <= m; i++) {
        sorted[i] = i;
    }

    sort(sorted + 1, sorted + m + 1,
        [](const int a, const int b) {
            return ew[a] < ew[b];
        });

    int ecnt = 0;
    for (int i = 1; i <= m; i++) {
        int p = sorted[i];
        int idu = find_set(eu[p]);
        int idv = find_set(ev[p]);

        if (idu != idv) {
            uf[idu] = idv;
            link_dual(eu[p], ev[p], ew[p]);
            DEBUG("Selected %d - %d: %d\n", eu[p], ev[p], ew[p]);
            ecnt++;
        }
    }
}

void build_tree(int x) {
    marked[x] = true;

    for (auto e : D[x]) {
        int v = e->v;

        if (!marked[v]) {
            depth[v] = depth[x] + 1;
            f[0][v] = x;
            maxv[0][v] = e->w;

            build_tree(v);
        }
    }
}

void build_dual_graph() {
    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        for (auto e : G[u]) {
            if (u > e->v ||
                e->dual_id == 1 ||
                e->reverse_edge->dual_id == 1)
                continue;

            cnt++;
            eu[cnt] = e->dual_id;
            ev[cnt] = e->reverse_edge->dual_id;
            ew[cnt] = e->w;
        }
    }

    n = dual_cnt;
    m = cnt;
    kruskal();

    for (int u = 2; u <= n; u++) {
        if (!marked[u])
            build_tree(u);
    }

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 2; i <= n; i++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
            maxv[j][i] = max(maxv[j - 1][i], maxv[j - 1][f[j - 1][i]]);
        }
    }
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &position[i].x, &position[i].y);
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        link(u, v, w);
    }

    scanf("%d", &q);
    
    for (int i = 1; i <= q; i++) {
        scanf("%lf%lf%lf%lf",
              &qu[i].pos.x, &qu[i].pos.y,
              &qv[i].pos.x, &qv[i].pos.y);
    }
}

int main() {
    // freopen("planar.in", "r", stdin);
    initialize();
    decompose();
    scanline();
    build_dual_graph();

    for (int i = 1; i <= q; i++) {
        printf("%d\n", query(qu[i].dual_id, qv[i].dual_id));
    }

    return 0;
}
