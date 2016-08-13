#define NDEBUG
#pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

#define NMAX 100000
// #define NMAX 100

struct Node {
    Node(int _left = 0, int _right = 0)
            : left(_left)
            , right(_right)
            , value(0)
            , leftchild(NULL)
            , rightchild(NULL) {}

    int left, right;
    int value;
    Node *leftchild, *rightchild;
};  // struct Node

static Node *build(int left, int right) {
    if (left == right)
        return new Node(left, left);
    else {
        int mid = (left + right) / 2;
        Node *x = new Node(left, right);
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);

        return x;
    }
}

static Node *persistant_modify(Node *x, int u) {
    Node *y = new Node;
    *y = *x;
    x = y;

    if (x->left == x->right)
        x->value++;
    else {
        int mid = (x->left + x->right) / 2;
        x->value++;

        if (u <= mid)
            x->leftchild = persistant_modify(x->leftchild, u);
        else
            x->rightchild = persistant_modify(x->rightchild, u);
    }

    return x;
}

static int query(Node *x, Node *y, int v) {
    if (x->left == x->right)
        return 0;

    int mid = (x->left + x->right) / 2;
    if (v <= mid)
        return query(x->leftchild, y->leftchild, v);
    else
        return query(x->rightchild, y->rightchild, v) +
               (y->leftchild->value - x->leftchild->value);
}

static int n, m;
static int w[NMAX + 10];
static int pos;
static int sorted[NMAX + 10];
static vector<int> G[NMAX + 10];
static int answer[NMAX + 10];
static Node *version[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static int seq[NMAX + 10];
static bool marked[NMAX + 10];

static void dfs(int x) {
    marked[x] = true;
    in[x] = ++timestamp;
    seq[timestamp] = x;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v])
            dfs(v);
    }  // for

    out[x] = timestamp;
}

static void evaluate(int x) {
    marked[x] = true;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            answer[v] = answer[x] -
                        query(version[in[v] - 1], version[out[v]], w[v]) -
                        query(version[in[v] - 1], version[out[v]], w[x]) +
                        query(version[in[1] - 1], version[out[1]], w[v]);
            evaluate(v);
        }
    }  // for
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", w + i);
        sorted[pos++] = w[i];
    }  // for

    sort(sorted, sorted + pos);
    pos = unique(sorted, sorted + pos) - sorted;
    for (int i = 1; i <= n; i++) {
        w[i] = (lower_bound(sorted, sorted + pos, w[i]) - sorted) + 1;
    }  // for

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    dfs(1);

    version[0] = build(1, pos);
    for (int i = 1; i <= n; i++) {
        version[i] = persistant_modify(version[i - 1], w[seq[i]]);
    }  // for

    for (int i = 1; i <= n; i++) {
        answer[1] += query(version[in[i] - 1], version[out[i]], w[i]);
    }  // for

    memset(marked, 0, sizeof(marked));
    evaluate(1);
}

int main() {
    // freopen("reverse.in", "r", stdin);
    // freopen("reverse.out", "w", stdout);
    initialize();

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);

        printf("%d\n", answer[x]);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
