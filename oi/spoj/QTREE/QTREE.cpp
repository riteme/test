#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// #ifndef __clang__
// #pragma GCC optimize("O2")
// #endif  // IFDEF GCC

typedef pair<int, int> IntPair;

struct Node {
    int key;
    int size;
    int depth;
    int id;
    Node *father;
    Node *next;
    Node *top;
    vector<Node *> children;
};  // struct Node

struct Edge {
    Node *u;
    Node *v;
    int w;
    int id;
};  // struct Edge

#define NMAX 10000
static int n = 0;
static Node nodes[NMAX + 10];
static Edge edges[NMAX + 10];
static vector<Node *> G[NMAX + 10];

static void prepare() {
    for (int i = 1; i <= NMAX; i++) {
        nodes[i].key = i;
    }  // for
}

static void cleanup() {
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        nodes[i].children.clear();
    }  // for
}

static void read_graph() {
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        edges[i].u = &nodes[u];
        edges[i].v = &nodes[v];
        edges[i].w = c;

        G[u].push_back(&nodes[v]);
        G[v].push_back(&nodes[u]);
    }  // for
}

static bool marked[NMAX + 10];
static void make_root(Node *u) {
    u->size = 1;
    u->next = NULL;

    // for (auto v : G[u->key]) {
    for (unsigned i = 0; i < G[u->key].size(); i++) {
        Node *v = G[u->key][i];

        if (!marked[v->key]) {
            marked[v->key] = true;
            v->father = u;
            v->depth = u->depth + 1;

            make_root(v);

            u->size += v->size;

            if (!u->next || v->size > u->next->size) {
                u->next = v;
            }

            u->children.push_back(v);
        }
    }  // foreach in G[u]
}

static void make_root(int root) {
    memset(marked, false, sizeof(marked));
    Node *u = &nodes[root];
    marked[root] = true;
    u->depth = 1;
    u->father = u;

    make_root(u);
}

struct Segment {
    int left;
    int right;
    int max;
    Segment *leftchild;
    Segment *rightchild;
    Segment *father;
};  // struct Segment

static Segment *segtree;
static Segment *seghash[NMAX + 10];
static Segment *build_segment_tree(int left, int right) {
    Segment *seg = new Segment;

    if (right <= left) {
        seg->left = seg->right = left;
        seg->max = INT_MIN;
        seg->leftchild = NULL;
        seg->rightchild = NULL;
        seghash[left] = seg;
    } else {
        seg->left = left;
        seg->right = right;
        seg->max = INT_MIN;

        int mid = (left + right) >> 1;
        seg->leftchild = build_segment_tree(left, mid);
        seg->rightchild = build_segment_tree(mid + 1, right);
        seg->leftchild->father = seg;
        seg->rightchild->father = seg;
        seg->max = INT_MIN;
    }

    return seg;
}

static void update_edge(int id, int v) {
    Segment *x = seghash[id];
    x->max = v;
    x = x->father;

    while (x && x->father) {
        x->max = max(x->leftchild->max, x->rightchild->max);

        x = x->father;
    }  // while
}

static int query(Segment *x, int left, int right) {
    if (!x || right < x->left || left > x->right) {
        return INT_MIN;
    }

    if (left <= x->left && x->right <= right) {
        return x->max;
    } else {
        return max(query(x->leftchild, left, right),
                   query(x->rightchild, left, right));
    }
}

static int id_count;
static void split_tree(Node *x) {
    if (x->next) {
        x->next->top = x->top;
        x->next->id = id_count++;

        split_tree(x->next);
    }

    // for (auto v : x->children) {
    for (unsigned i = 0; i < x->children.size(); i++) {
        Node *v = x->children[i];

        if (v != x->next) {
            v->top = v;
            v->id = id_count++;

            split_tree(v);
        }
    }  // foreach in x->children
}

static void split_tree(int root) {
    id_count = 1;
    Node *x = &nodes[root];
    x->top = x;
    x->id = 0;

    split_tree(x);
}

static void initialize() {
    read_graph();

    make_root(1);

    segtree = build_segment_tree(1, n);
    segtree->father = NULL;

    split_tree(1);

    for (int i = 1; i <= n - 1; i++) {
        Edge *e = &edges[i];

        if (e->u->father == e->v) {
            swap(e->u, e->v);
        }

        e->id = e->v->id;
        update_edge(e->id, e->w);
    }  // for
}

static void process() {
    char buffer[10];

    while (true) {
        scanf("%s", buffer);

        if (buffer[0] == 'Q') {
            int a, b;
            scanf("%d%d", &a, &b);

            Node *x = &nodes[a];
            Node *y = &nodes[b];

            int answer = INT_MIN;
            while (x->top != y->top) {
                if (x->top->depth < y->top->depth) {
                    swap(x, y);
                }

                answer = max(answer, query(segtree, x->top->id, x->id));
                x = x->top->father;
            }

            if (x != y) {
                if (x->depth > y->depth) {
                    swap(x, y);
                }

                answer = max(answer, query(segtree, x->next->id, y->id));
            }

            printf("%d\n", answer);
        } else if (buffer[0] == 'C') {
            int i, t;
            scanf("%d%d", &i, &t);

            update_edge(edges[i].id, t);
        } else {
            break;
        }
    }  // while
}

int main() {
    prepare();

    int t;
    scanf("%d", &t);
    while (t > 0) {
        cleanup();
        initialize();
        process();

        t--;
    }  // while

    return 0;
}  // function main
