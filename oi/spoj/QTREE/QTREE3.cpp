#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define WHITE false
#define BLACK true

struct TreeNode;

struct RankNode {
    TreeNode *target;
    int size;
    RankNode *left;
    RankNode *right;
    RankNode *father;
};  // struct RankNode

struct TreeNode {
    int key;
    int size;
    int depth;
    bool color;
    TreeNode *father;
    TreeNode *top;
    TreeNode *next;
    vector<TreeNode *> children;
    RankNode *enitiy;
    RankNode *ranktree;
};  // struct TreeNode

#define NMAX 100000

static int n, q;
static vector<int> G[NMAX + 10];
static TreeNode nodes[NMAX + 10];
static bool marked[NMAX + 10];

static void read_graph() {
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for
}

static void set_root(TreeNode *u) {
    u->size = 1;
    u->next = NULL;

    for (unsigned i = 0; i < G[u->key].size(); i++) {
        int c = G[u->key][i];
        TreeNode *v = &nodes[c];

        if (!marked[c]) {
            marked[c] = true;

            v->father = u;
            v->depth = u->depth + 1;

            set_root(v);

            u->size += v->size;

            if (!u->next || v->size > u->next->size) {
                u->next = v;
            }

            u->children.push_back(v);
        }
    }  // for
}

static TreeNode *buffer[NMAX + 10];

static RankNode *build_tree(int left, int right) {
    if (right < left) {
        return NULL;
    }

    int mid = (left + right) / 2;
    RankNode *x = new RankNode;
    TreeNode *target = buffer[mid];
    target->enitiy = x;
    x->target = target;
    x->size = 0;

    x->left = build_tree(left, mid - 1);
    x->right = build_tree(mid + 1, right);
    if (x->left) {
        x->left->father = x;
    }
    if (x->right) {
        x->right->father = x;
    }

    return x;
}

static void make_tree(TreeNode *x) {
    int i = 0;
    TreeNode *top = x->top;
    while (x && x->top == top) {
        buffer[++i] = x;
        x = x->next;
    }  // while

    RankNode *t = build_tree(1, i);
    t->father = NULL;

    for (int j = 1; j <= i; j++) {
        buffer[j]->ranktree = t;
    }  // for
}

static void split(TreeNode *u) {
    if (u->next) {
        u->next->top = u->top;
        split(u->next);
    }

    for (unsigned i = 0; i < u->children.size(); i++) {
        TreeNode *v = u->children[i];

        if (v != u->next) {
            v->top = v;
            split(v);
        }
    }  // for

    if (u->top == u) {
        make_tree(u);
    }
}

static RankNode *first(RankNode *x) {
    if (!x) {
        return NULL;
    }

    RankNode *result = NULL;
    if (x->left && x->left->size > 0) {
        result = first(x->left);

        if (result) {
            return result;
        } else if (x->target->color) {
            return x;
        }
    } else {
        if (x->target->color) {
            return x;
        } else {
            return first(x->right);
        }
    }

    return NULL;
}

static void flip(RankNode *x) {
    x->target->color = !x->target->color;
    int d;
    if (x->target->color == WHITE) {
        d = -1;
    } else {
        d = 1;
    }

    while (x) {
        x->size += d;

        x = x->father;
    }  // while
}

static void initialize() {
    scanf("%d%d", &n, &q);

    read_graph();

    for (int i = 1; i <= n; i++) {
        nodes[i].key = i;
        nodes[i].color = WHITE;
    }  // for

    memset(marked, false, sizeof(marked));
    marked[1] = true;
    nodes[1].depth = 1;
    nodes[1].father = NULL;
    set_root(&nodes[1]);

    nodes[1].top = &nodes[1];
    split(&nodes[1]);
}

int main() {
    initialize();

    for (int cnt = 0; cnt < q; cnt++) {
        int t, v;
        scanf("%d%d", &t, &v);

        switch (t) {
            case 0: flip(nodes[v].enitiy); break;
            case 1:
                TreeNode *x = &nodes[v];
                TreeNode *answer = NULL;

                while (x) {
                    RankNode *p = first(x->ranktree);

                    if ((p && p->target->depth <= x->depth) &&
                        ((!answer && p) ||
                         (p && p->target->depth < answer->depth))) {
                        answer = p->target;
                    }

                    x = x->top->father;
                }  // while

                if (answer) {
                    printf("%d\n", answer->key);
                } else {
                    puts("-1");
                }

                break;
        }  // switch to t
    }      // for

    return 0;
}  // function main
