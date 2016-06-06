#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define QMAX 200000
// #define NMAX 30
// #define QMAX 30

typedef long long ntype;

static int cnt;
static int points[QMAX * 2 + 10];

static void hashing() {
    sort(points + 1, points + cnt + 1);
    cnt = unique(points + 1, points + cnt + 1) - points - 1;
}

struct Node {
    struct Sum {
        Sum() : xw(0), w(0) {}

        ntype xw, w;
    };  // struct Sum

    Node() : left(0), right(0), x(0), w(0), leftchild(NULL), rightchild(NULL) {}

    int left, right;
    int x;
    ntype w;
    Sum sum;

    Node *leftchild, *rightchild;
};  // struct Node

inline ntype sum_w(Node *x) {
    return x ? x->sum.w : 0;
}

inline ntype sum_xw(Node *x) {
    return x ? x->sum.xw : 0;
}

inline void update(Node *x) {
    x->sum.w = sum_w(x->leftchild) + sum_w(x->rightchild) + x->w;
    x->sum.xw = sum_xw(x->leftchild) + sum_xw(x->rightchild) + x->x * x->w;
}

static Node *build(int left, int right) {
    if (right < left)
        return NULL;

    int mid = (left + right) / 2;
    Node *x = new Node;
    x->x = points[mid];
    x->left = points[left];
    x->right = points[right];
    x->leftchild = build(left, mid - 1);
    x->rightchild = build(mid + 1, right);

    return x;
}

static void modify(Node *x, int key, int delta) {
    if (!x)
        return;

    if (key < x->x)
        modify(x->leftchild, key, delta);
    else if (key > x->x)
        modify(x->rightchild, key, delta);
    else
        x->w += delta;

    update(x);
}

static ntype query_xw(Node *x, int left) {
    if (!x)
        return 0;
    if (left <= x->left)
        return x->sum.xw;
    if (x->right < left)
        return 0;

    return query_xw(x->leftchild, left) + query_xw(x->rightchild, left) +
           (left <= x->x ? x->x * x->w : 0);
}

static ntype query_w(Node *x, int left) {
    if (!x)
        return 0;
    if (left <= x->left)
        return x->sum.w;
    if (x->right < left)
        return 0;

    return query_w(x->leftchild, left) + query_w(x->rightchild, left) +
           (left <= x->x ? x->w : 0);
}

static int n, q;
static Node *tree;
static ntype prefix[NMAX + 10];

enum CommandType { COMM_ADD = 1, COMM_QUERY = 2 };  // enum CommandType

struct Command {
    CommandType type;
    int a, b;
    ntype v;
};  // struct Command

static Command ops[QMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);

        prefix[i] = prefix[i - 1] + x;
    }  // for

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int command;
        scanf("%d", &command);

        if (command == 1) {
            int l, r;
            ntype v;
            scanf("%d%d%lld", &l, &r, &v);

            ops[i].type = COMM_ADD;
            ops[i].a = l;
            ops[i].b = r;
            ops[i].v = v;
            points[++cnt] = l - 1;
            points[++cnt] = r;
        } else {
            int l, r;
            scanf("%d%d", &l, &r);

            ops[i].type = COMM_QUERY;
            ops[i].a = l;
            ops[i].b = r;
        }
    }  // for

    hashing();
    tree = build(1, cnt);
}

inline ntype evaluate(Node *x, int left) {
    return query_xw(x, left) - (left - 1) * query_w(x, left);
}

int main() {
    initialize();

    for (int i = 1; i <= q; i++) {
        Command &op = ops[i];

        if (op.type == COMM_ADD) {
            modify(tree, op.a - 1, -op.v);
            modify(tree, op.b, op.v);
        } else {
            ntype answer = evaluate(tree, op.a) - evaluate(tree, op.b + 1);

            printf("%lld\n", answer + prefix[op.b] - prefix[op.a - 1]);
        }
    }  // for

    return 0;
}  // function main
