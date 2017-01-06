#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t pos = BUFFERSIZE;
static char buffer[BUFFERSIZE];

inline char _getchar() {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buffer, 1, BUFFERSIZE, stdin);
    }

    return buffer[pos++];
}

template <typename T>
inline T read() {
    T x = 0;
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 20000
#define MMAX 50000
#define QMAX 50000
#define LCTSIZE (NMAX + MMAX)

typedef long long int64;

struct Edge {
    int id;
    int u, v;
    int64 w;
    int depth;
};

class LCT {
 public:
    class Splays {
     public:
        Splays() {
            memset(father, 0, sizeof(father));
            memset(left, 0, sizeof(left));
            memset(right, 0, sizeof(right));
            memset(value, 0, sizeof(value));
            memset(edge, 0, sizeof(edge));
            memset(maxvalue, 0, sizeof(maxvalue));
            memset(maxedge, 0, sizeof(maxedge));
            memset(reversed, 0, sizeof(reversed));
        }

        int father[LCTSIZE + 10];
        int left[LCTSIZE + 10];
        int right[LCTSIZE + 10];
        int value[LCTSIZE + 10];
        Edge *edge[LCTSIZE + 10];
        int maxvalue[LCTSIZE + 10];
        Edge *maxedge[LCTSIZE + 10];
        bool reversed[LCTSIZE + 10];

        void update(int x) {
            maxvalue[x] = value[x];
            maxedge[x] = edge[x];

            if (left[x] && maxvalue[left[x]] > maxvalue[x]) {
                maxvalue[x] = maxvalue[left[x]];
                maxedge[x] = maxedge[left[x]];
            }
            
            if (right[x] && maxvalue[right[x]] > maxvalue[x]) {
                maxvalue[x] = maxvalue[right[x]];
                maxedge[x] = maxedge[right[x]];
            }
        }

        void pushdown(int x) {
            if (reversed[x]) {
                swap(left[x], right[x]);
                reversed[x] = false;
                reversed[left[x]] ^= true;
                reversed[right[x]] ^= true;
            }
        }

        void clear(int x) {
            if (x > 0) {
                clear(father[x]);
                pushdown(x);
            }
        }

        void left_rotate(int x) {
            assert(left[x]);

            int y = left[x];
            left[x] = right[y];
            father[right[y]] = x;
            right[y] = x;

            if (father[x] > 0) {
                if (x == left[father[x]])
                    left[father[x]] = y;
                else
                    right[father[x]] = y;
            }
            father[y] = father[x];
            father[x] = y;

            update(x);
            update(y);
        }

        void right_rotate(int x) {
            assert(right[x]);

            int y = right[x];
            right[x] = left[y];
            father[left[y]] = x;
            left[y] = x;

            if (father[x] > 0) {
                if (x == left[father[x]])
                    left[father[x]] = y;
                else
                    right[father[x]] = y;
            }
            father[y] = father[x];
            father[x] = y;

            update(x);
            update(y);
        }

        void splay(int x) {
            // Simple splay
            clear(x);

            while (father[x] > 0) {
                if (x == left[father[x]])
                    left_rotate(father[x]);
                else
                    right_rotate(father[x]);
            }
        }
    } sp;

    int access(int x) {
        sp.splay(x);
        sp.father[sp.right[x]] = -x;
        sp.right[x] = 0;
        sp.update(x);

        while (sp.father[x] != 0) {
            int top = -sp.father[x];
            assert(top > 0);
            
            sp.splay(top);
            sp.father[sp.right[top]] = -top;
            sp.right[top] = x;
            sp.father[x] = top;
            sp.update(top);
            x = top;
        }

        return x;
    }

    int find_root(int x) {
        x = access(x);

        while (sp.left[x]) {
            x = sp.left[x];
            sp.pushdown(x);
        }

        return x;
    }

    void make_root(int x) {
        x = access(x);
        sp.reversed[x] ^= true;
    }

    void link(int x, int y) {
        make_root(y);
        sp.splay(y);
        sp.father[y] = -x;
        access(y);
    }

    void cut(int x, int y) {
        access(y);
        sp.splay(x);
        sp.father[x] = 0;
    }
};

struct Node {
    Node (int l, int r)
        : left(l), right(r),
          leftchild(NULL),
          rightchild(NULL) {}

    int left;
    int right;
    vector<Edge *> edges;
    Node *leftchild;
    Node *rightchild;
};

static Node *build(int left, int right) {
    Node *x = new Node(left, right);

    if (left < right) {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
    }

    return x;
}

static void modify(Node *x, int left, int right, Edge *e) {
    if (e->u == e->v)
        return;

    if (left <= x->left && x->right <= right)
        x->edges.push_back(e);
    else {
        int mid = (x->left + x->right) / 2;

        if (right <= mid)
            modify(x->leftchild, left, right, e);
        else if (left > mid)
            modify(x->rightchild, left, right, e);
        else {
            modify(x->leftchild, left, right, e);
            modify(x->rightchild, left, right, e);
        }
    }
}

static int n, m, mcnt, q;
static Node *tree;
static LCT lct;
static int start[MMAX + 10];
static Edge *last[MMAX + 10];
static int64 answer[QMAX + 10];

static size_t mempos = 0;
static Edge memory[MMAX + QMAX + 10];

inline Edge *allocate() {
    return &memory[mempos++];
}

static void initialize() {
    // scanf("%d%d%d", &n, &m, &q);
    n = read<int>();
    m = read<int>();
    q = read<int>();
    mcnt = m;
    tree = build(0, q);

    for (int i = 1; i <= m; i++) {
        // Edge *e = new Edge;
        Edge *e = allocate();
        // scanf("%d%d%lld", &e->u, &e->v, &e->w);
        e->u = read<int>();
        e->v = read<int>();
        e->w = read<int64>();
        e->id = i;
        start[i] = 0;
        last[i] = e;
    }

    for (int i = 1; i <= q; i++) {
        int k;
        int64 d;
        // scanf("%d%lld", &k, &d);
        k = read<int>();
        d = read<int64>();

        Edge *e = last[k];
        // Edge *ne = new Edge;
        Edge *ne = allocate();
        *ne = *e;
        ne->w = d;
        modify(tree, start[k], i - 1, e);
        start[k] = i;
        last[k] = ne;
    }

    for (int i = 1; i <= m; i++) {
        modify(tree, start[i], q, last[i]);
    }
}

inline void cut_edge(Edge *e) {
    if (lct.find_root(e->u) == lct.find_root(n + e->id)) {
        lct.make_root(n + e->id);
        lct.cut(e->u, n + e->id);
        lct.cut(e->v, n + e->id);
    }
}

inline void add_edge(Edge *e) {
    assert(lct.find_root(e->u) != lct.find_root(e->v));

    lct.sp.value[n + e->id] = lct.sp.maxvalue[n + e->id] = e->w;
    lct.sp.edge[n + e->id] = lct.sp.maxedge[n + e->id] = e;
    lct.link(n + e->id, e->u);
    lct.link(n + e->id, e->v);
}

static void dfs(Node *x, int64 sum = 0, int depth = 0) {
    vector<Edge *> removed;
    vector<Edge *> added;

    for (size_t i = 0; i < x->edges.size(); i++) {
        Edge *e = x->edges[i];

        if (lct.find_root(e->u) == lct.find_root(e->v)) {
            lct.make_root(e->u);
            int top = lct.access(e->v);
            Edge *maxe = lct.sp.maxedge[top];
            assert(maxe);

            if (maxe->w <= e->w)
                continue;

            cut_edge(maxe);
            sum -= maxe->w;

            if (maxe->depth != depth)
                removed.push_back(maxe);
        }

        e->depth = depth;
        add_edge(e);
        sum += e->w;
        added.push_back(e);
    }

    if (x->left < x->right) {
        dfs(x->leftchild, sum, depth + 1);
        dfs(x->rightchild, sum, depth + 1);
    } else
        answer[x->left] = sum;

    if (depth > 0) {
        for (size_t i = 0; i < added.size(); i++) {
            Edge *e = added[i];
            cut_edge(e);
        }

        for (size_t i = 0; i < removed.size(); i++) {
            Edge *e = removed[i];
            add_edge(e);
        }
    }
}

int main() {
    // freopen("hnoi2010_city.in", "r", stdin);
    // freopen("hnoi2010_city.out", "w", stdout);
    initialize();

    for (int i = 1; i <= LCTSIZE; i++) {
        lct.sp.value[i] = -1;
        lct.sp.maxvalue[i] = -1;
    }

    dfs(tree);

    for (int i = 1; i <= q; i++) {
        printf("%lld\n", answer[i]);
    }

    return 0;
}
