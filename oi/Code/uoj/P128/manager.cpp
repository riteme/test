/**
 * Accepted
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At #%d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#define DEBUG(message, ...) printf(message, __VA_ARGS__);
#define SAY(message) printf(message);
#else
#define TRACE
#define DEBUG
#define SAY
#endif  // IFNDEF NDEBUG

#define NMAX 100000

#define WHITE 1
#define BLACK 2

struct Node {
    Node(int _left, int _right)
            : left(_left)
            , right(_right)
            , count(0)
            , mark(0)
            , leftchild(NULL)
            , rightchild(NULL) {}

    int left, right;
    int count;
    char mark;
    Node *leftchild, *rightchild;
};  // struct Node

inline void pushdown(Node *x) {
    assert(x);

    if (x->mark) {
        if (x->mark == WHITE) {
            x->count = 0;

            if (x->leftchild)
                x->leftchild->mark = x->rightchild->mark = WHITE;
        } else {
            x->count = x->right - x->left + 1;

            if (x->leftchild)
                x->leftchild->mark = x->rightchild->mark = BLACK;
        }

        x->mark = 0;
    }
}

inline int count_of(Node *x) {
    assert(x);

    if (x->mark)
        return x->mark == BLACK ? (x->right - x->left + 1) : 0;
    else
        return x->count;
}

inline void update(Node *x) {
    assert(x);
    assert(x->mark == 0);

    if (x->leftchild)
        x->count = count_of(x->leftchild) + count_of(x->rightchild);
}

static Node *build(int left, int right) {
    assert(left <= right);

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

static void modify(Node *x, int left, int right, char color) {
    assert(x);

    // DEBUG("Enter [%d, %d] ([%d, %d])\n", x->left, x->right, left, right);

    if (left <= x->left && x->right <= right) {
        // TRACE
        x->mark = color;
        return;
    }

    pushdown(x);
    int mid = (x->left + x->right) / 2;
    if (right <= mid)
        modify(x->leftchild, left, right, color);
    else if (left > mid)
        modify(x->rightchild, left, right, color);
    else {
        modify(x->leftchild, left, right, color);
        modify(x->rightchild, left, right, color);
    }

    update(x);

    // DEBUG("Exit [%d, %d] ([%d, %d])\n", x->left, x->right, left, right);
}

static int query(Node *x, int left, int right) {
    assert(x);

    if (left <= x->left && x->right <= right)
        return count_of(x);

    pushdown(x);
    int mid = (x->left + x->right) / 2;
    if (right <= mid)
        return query(x->leftchild, left, right);
    else if (left > mid)
        return query(x->rightchild, left, right);
    else
        return query(x->leftchild, left, right) +
               query(x->rightchild, left, right);
}

static int n, q;
static vector<int> G[NMAX + 10];
static int father[NMAX + 10];
static int nxt[NMAX + 10];
static int size[NMAX + 10];
static int top[NMAX + 10];
static int location[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];
static Node *tree;

static void dfs(int x) {
    size[x] = 1;
    int maxnode = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        dfs(v);
        size[x] += size[v];

        if (maxnode == 0 || size[v] > size[maxnode])
            maxnode = v;
    }  // for

    nxt[x] = maxnode;
}

static int cnt = 0;
static int timestamp = 0;

static void decompose(int x) {
    in[x] = ++timestamp;

    if (nxt[x] > 0) {
        top[nxt[x]] = top[x];
        location[nxt[x]] = ++cnt;
        decompose(nxt[x]);
    }

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v != nxt[x]) {
            top[v] = v;
            location[v] = ++cnt;
            decompose(v);
        }
    }  // for

    out[x] = timestamp;
}

static void initialize() {
    scanf("%d", &n);

    father[0] = -1;
    for (int i = 1; i <= n - 1; i++) {
        int fa;
        scanf("%d", &fa);
        father[i] = fa;
        G[fa].push_back(i);
    }  // for

    dfs(0);
    top[0] = 0;
    location[0] = ++cnt;
    decompose(0);

    tree = build(1, n);
}

int main() {
    initialize();

    // for (int i = 0; i <= n - 1; i++) {
    //     printf(
    //         "in[%d] = %d, out[%d] = %d, top[%d] = %d, loc[%d] = %d, nxt[%d] =
    //         "
    //         "%d\n",
    //         i, in[i], i, out[i], i, top[i], i, location[i], i, nxt[i]);
    // }  // for

    char buffer[16];
    int x;
    scanf("%d", &q);
    while (q > 0) {
        scanf("%s%d", buffer, &x);

        int answer = 0;
        if (buffer[0] == 'i') {  // install
            while (x >= 0) {
                int t = top[x];

                // DEBUG("x = %d, t = %d\n", x, t);

                answer += location[x] - location[t] + 1 -
                          query(tree, location[t], location[x]);
                modify(tree, location[t], location[x], BLACK);

                // DEBUG("query: %d\n", query(tree, location[t], location[x]));

                x = father[t];
            }     // while
        } else {  // uninstall
            answer = query(tree, in[x], out[x]);
            modify(tree, in[x], out[x], WHITE);
        }

        printf("%d\n", answer);

        q--;
    }  // while

    return 0;
}  // function main
