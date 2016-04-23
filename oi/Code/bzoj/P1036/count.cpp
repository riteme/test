// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#pragma GCC optimize("O2")

#define NMAX 30000

struct Node {
    int key;
    Node *father;
    Node *next;
    Node *top;
    int id;
    int value;
    int depth;
    int size;
    vector<Node *> children;
};  // struct Node

static Node nodes[NMAX + 10];

static int n;
static vector<Node *> G[NMAX + 10];

static void read_graph() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(&nodes[v]);
        G[v].push_back(&nodes[u]);
    }  // for

    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodes[i].value);
        nodes[i].key = i;
    }  // for
}

// root = 1
static bool marked[NMAX + 10];

static void make_root(Node *u) {
    u->size = 0;
    u->next = NULL;

    for (unsigned i = 0; i < G[u->key].size(); i++) {
        Node *v = G[u->key][i];

        if (!marked[v->key]) {
            marked[v->key] = true;
            v->father = u;
            v->depth = u->depth + 1;

            make_root(v);

            u->size++;

            if (!u->next || v->size > u->next->size) {
                u->next = v;
            }

            u->children.push_back(v);
        }
    }  // for
}

static void make_root() {
    memset(marked, false, sizeof(marked));
    marked[1] = true;
    nodes[1].father = NULL;
    nodes[1].depth = 1;

    make_root(&nodes[1]);
}

static int id_count;

static void split_tree(Node *u) {
    if (u->next) {
        u->next->top = u->top;
        u->next->id = id_count++;

        split_tree(u->next);
    }

    for (unsigned i = 0; i < u->children.size(); i++) {
        Node *v = u->children[i];

        if (v != u->next) {
            v->top = v;
            v->id = id_count++;

            split_tree(v);
        }
    }  // for
}

static void split_tree() {
    id_count = 2;
    nodes[1].id = 1;
    nodes[1].top = &nodes[1];

    split_tree(&nodes[1]);
}

#define LOGN 15
static int f[NMAX + 10][LOGN + 10];

static void prepare_lca() {
    for (int i = 1; i <= n; i++) {
        f[i][0] = nodes[i].father ? nodes[i].father->key : 1;
    }  // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }  // for
    }      // for
}

static int lca(int u, int v) {
    if (nodes[u].depth < nodes[v].depth) {
        swap(u, v);
    }

    int dist = nodes[u].depth - nodes[v].depth;
    for (int i = LOGN; i >= 0; i--) {
        if (dist & (1 << i)) {
            u = f[u][i];
        }
    }  // for

    if (u == v) {
        return u;
    }

    for (int i = LOGN; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }  // for

    return nodes[u].father->key;
}

struct Segment {
    int s;
    int t;
    int sum;
    int max;

    Segment *left;
    Segment *right;
    Segment *father;
};  // struct Segment

static Segment *segtree;
static Segment *segments_hash[NMAX + 10];

static Segment *build_segtree(int lbound, int rbound) {
    Segment *seg = new Segment;

    if (lbound >= rbound) {
        seg->s = seg->t = lbound;
        seg->sum = seg->max = 0;
        seg->left = NULL;
        seg->right = NULL;

        segments_hash[lbound] = seg;
    } else {
        int mid = (lbound + rbound) >> 1;
        seg->s = lbound;
        seg->t = rbound;
        seg->left = build_segtree(lbound, mid);
        seg->right = build_segtree(mid + 1, rbound);
        seg->left->father = seg;
        seg->right->father = seg;
        seg->sum = seg->left->sum + seg->right->sum;
        seg->max = max(seg->left->max, seg->right->max);
    }

    return seg;
}

static void update_node(int u, int v) {
    Segment *x = segments_hash[u];
    int d = v - x->sum;
    x->sum = x->max = v;
    x = x->father;

    while (x && x->father) {
        x->sum += d;
        x->max = max(x->left->max, x->right->max);

        x = x->father;
    }  // while
}

static int query_sum(Segment *x, int left, int right) {
    if (!x || right < x->s || left > x->t) {
        return 0;
    }

    if (left <= x->s && x->t <= right) {
        return x->sum;
    } else {
        return query_sum(x->left, left, right) +
               query_sum(x->right, left, right);
    }
}

static int query_max(Segment *x, int left, int right) {
    if (!x || right < x->s || left > x->t) {
        return INT_MIN;
    }

    if (left <= x->s && x->t <= right) {
        return x->max;
    } else {
        return max(query_max(x->left, left, right),
                   query_max(x->right, left, right));
    }
}

static void initialize() {
    read_graph();
    // puts("Graph ready.");

    make_root();
    // puts("Decided tree root.");

    split_tree();
    // puts("Tree splited.");

    prepare_lca();
    // puts("LCA ready.");

    segtree = build_segtree(1, n);
    segtree->father = NULL;
    // puts("Segment tree built.");

    for (int i = 1; i <= n; i++) {
        update_node(nodes[i].id, nodes[i].value);
    }  // for
    // puts("Segment tree ready.");
}

static void CHANGE(int u, int t) {
    update_node(nodes[u].id, t);
    nodes[u].value = t;
}

static int get_max(int u, int v) {
    Node *x = &nodes[u];
    Node *y = &nodes[v];

    int result = INT_MIN;
    while (x->top != y->top) {
        if (x->top->depth > y->top->depth) {
            swap(x, y);
        }

        result = max(result, query_max(segtree, y->top->id, y->id));
        y = y->top->father;
    }  // while

    if (x->depth == y->depth) {
        return result;
    }

    if (x->depth > y->depth) {
        swap(x, y);
    }

    return max(result, query_max(segtree, x->next->id, y->id));
}

static int get_sum(int u, int v) {
    Node *x = &nodes[u];
    Node *y = &nodes[v];

    int result = 0;
    while (x->top != y->top) {
        if (x->top->depth > y->top->depth) {
            swap(x, y);
        }

        result += query_sum(segtree, y->top->id, y->id);
        y = y->top->father;
    }  // while

    if (x->depth == y->depth) {
        return result;
    }

    if (x->depth > y->depth) {
        swap(x, y);
    }

    return result + query_sum(segtree, x->next->id, y->id);
}

static void QMAX(int u, int v) {
    int q = lca(u, v);
    int answer = max(max(get_max(u, q), get_max(v, q)), nodes[q].value);

    printf("%d\n", answer);
}

static void QSUM(int u, int v) {
    int q = lca(u, v);
    int answer = get_sum(u, q) + get_sum(v, q) + nodes[q].value;

    printf("%d\n", answer);
}

static void answer() {
    char buffer[10];
    int a, b;
    scanf("%s%d%d", buffer, &a, &b);

    if (buffer[1] == 'H') {  // CHANGE
        CHANGE(a, b);
    } else if (buffer[1] == 'M') {  // MAX
        QMAX(a, b);
    } else {  // SUM
        QSUM(a, b);
    }
}

static void process() {
    int q;
    scanf("%d", &q);

    while (q > 0) {
        answer();

        q--;
    }  // while
}

int main() {
    initialize();
    process();

    return 0;
}  // function main
