/**
 * 平衡树启发式合并
 * 考虑经过根节点p的路径中如何求出最大的
 * 已知两个子树x, y
 * a \in x, b \in y, 设k(x)为x到子树根路径上黑点个数
 * 即最大化 d = distance(a, p) + distance(b, p)
 * 同时满足 k(a) + k(b) <= k
 * 维护一棵平衡树来进行区间查询即可
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

#define INFTY 0x3f3f3f3f

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, m, k;
static vector<Edge *> G[NMAX + 10];
static bool black[NMAX + 10];

inline void add_edge(int u, int v, int w) {
    Edge *e = new Edge(u, v, w);

    G[u].push_back(e);
    G[v].push_back(e);
}

static void initialize() {
    scanf("%d%d%d", &n, &k, &m);

    for (int i = 0; i < m; i++) {
        int v;
        scanf("%d", &v);

        black[v] = true;
    }  // for

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        add_edge(u, v, w);
    }  // for
}

static bool marked[NMAX + 10];
static int w[NMAX + 10];
static vector<int> children[NMAX + 10];

static void set_root(int x) {
    marked[x] = true;

    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (not marked[v]) {
            w[v] = e->w;
            children[x].push_back(v);
            set_root(v);
        }
    }  // for
}

#define SEED (233)
static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

// Treap
struct Node {
    Node(int _blackcnt, int _distance)
            : blackcnt(_blackcnt)
            , distance(_distance)
            , max_distance(_distance)
            , size(1)
            , weight(randint())
            , left(NULL)
            , right(NULL) {}

    int blackcnt;  // key
    int distance;
    int max_distance;

    struct Mark {
        Mark() : black(0), dist(0) {}

        int black;
        int dist;
    } mark;

    int size;
    int weight;
    Node *left;
    Node *right;
};  // struct Node

inline int size(Node *x) {
    if (x) {
        return x->size;
    } else {
        return 0;
    }
}

inline int max_distance(Node *x) {
    if (x) {
        return x->max_distance + x->mark.dist;
    } else {
        return -INFTY;
    }
}

inline void update(Node *x) {
    x->max_distance =
        max(x->distance, max(max_distance(x->left), max_distance(x->right)));
    x->size = size(x->left) + size(x->right) + 1;
}

inline void pushdown(Node *x) {
    if (x->mark.black != 0) {
        x->blackcnt += x->mark.black;

        if (x->left) {
            x->left->mark.black += x->mark.black;
        }
        if (x->right) {
            x->right->mark.black += x->mark.black;
        }

        x->mark.black = 0;
    }

    if (x->mark.dist != 0) {
        x->distance += x->mark.dist;
        x->max_distance += x->mark.dist;

        if (x->left) {
            x->left->mark.dist += x->mark.dist;
        }
        if (x->right) {
            x->right->mark.dist += x->mark.dist;
        }

        x->mark.dist = 0;
    }
}

inline Node *left_rotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;

    update(x);
    update(y);
    return y;
}

inline Node *right_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;

    update(x);
    update(y);
    return y;
}

static Node *insert(Node *x, Node *y) {
    if (!x) {
        return y;
    }

    pushdown(x);
    if (y->blackcnt < x->blackcnt) {
        x->left = insert(x->left, y);

        if (x->left->weight < x->weight) {
            return left_rotate(x);
        }
    } else {
        x->right = insert(x->right, y);

        if (x->right->weight < x->weight) {
            return right_rotate(x);
        }
    }

    update(x);
    return x;
}

typedef pair<Node *, Node *> NodePair;
static NodePair split(Node *x, int key) {
    if (!x) {
        return NodePair(NULL, NULL);
    }

    pushdown(x);
    NodePair result;
    if (key < x->blackcnt) {
        result = split(x->left, key);
        x->left = result.second;
        result.second = x;
        update(x);
    } else {
        result = split(x->right, key);
        x->right = result.first;
        result.first = x;
        update(x);
    }

    return result;
}

static Node *quick_merge(Node *x, Node *y) {
    if (!x) {
        return y;
    }

    if (!y) {
        return x;
    }

    if (x->weight < y->weight) {
        pushdown(x);
        x->right = quick_merge(x->right, y);
        update(x);

        return x;
    } else {
        pushdown(y);
        y->left = quick_merge(x, y->left);
        update(y);

        return y;
    }
}

static Node *merge(Node *x, Node *y) {
    if (!y) {
        return x;
    }

    pushdown(y);
    Node *lc = y->left;
    Node *rc = y->right;
    y->left = y->right = NULL;
    update(y);
    x = insert(x, y);

    x = merge(x, lc);
    x = merge(x, rc);

    return x;
}

static Node *root[NMAX + 10];

static int process(Node *x, Node *y, int nk) {
    if (!y) {
        return -INFTY;
    }

    pushdown(y);
    if (y->blackcnt <= nk) {
        NodePair result = split(x, nk - y->blackcnt);
        int md = max_distance(result.first) + y->distance;
        x = quick_merge(result.first, result.second);

        return max(md, max(process(x, y->left, nk), process(x, y->right, nk)));
    } else {
        return max(process(x, y->left, nk), process(x, y->right, nk));
    }
}

static int dfs(int x) {
    int answer = -INFTY;
    Node *subtree = NULL;
    int selected = 0;
    int blackcnt = black[x] ? 1 : 0;
    for (unsigned i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        answer = max(answer, dfs(v));
        root[v]->mark.black += blackcnt;
        root[v]->mark.dist += w[v];
        if (size(root[v]) > size(subtree)) {
            subtree = root[v];
            selected = v;
        }
    }  // for

    for (unsigned i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        if (v != selected) {
            answer = max(answer, process(subtree, root[v], k + blackcnt));
            subtree = merge(subtree, root[v]);
        }
    }  // for

    Node *myself = new Node(blackcnt, 0);
    answer = max(answer, process(subtree, myself, k + blackcnt));
    root[x] = insert(subtree, myself);

    return answer;
}

static void release(Node *x) {
    if (!x) {
        return;
    }

    release(x->left);
    release(x->right);
    delete x;
}

int main() {
    freopen("freetourII.in", "r", stdin);
    freopen("freetourII.out", "w", stdout);
    initialize();

    set_root(1);

    printf("%d\n", max(0, dfs(1)));

    // release(root[1]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
