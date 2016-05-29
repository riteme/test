/**
 * POJ真是个卡指针狂魔
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 2048
static char _buffer[BUFFERSIZE + 10];
static unsigned _pos = BUFFERSIZE;
inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        fread(_buffer, 1, BUFFERSIZE, stdin);
        _pos = 0;
    }

    return _buffer[_pos++];
}

inline int readint() {
    int x = 0, f = 1;
    char c = _getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;
        c = _getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = _getchar();
    }
    return x * f;
}

#define NMAX 100000

static int n, m;
static int num[NMAX + 10];

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = readint();
    m = readint();
    for (int i = 1; i <= n; i++) {
        // scanf("%d", num + i);
        num[i] = readint();
    }  // for
}

static int sorted[NMAX + 10];
static int id[NMAX + 10];

static bool cmp(int a, int b) {
    return num[a] < num[b];
}

static void hashing() {
    for (int i = 1; i <= n; i++) {
        sorted[i] = i;
    }  // for
    sort(sorted + 1, sorted + n + 1, cmp);

    for (int i = 1; i <= n; i++) {
        id[sorted[i]] = i;
    }  // for
}

struct Node {
    int left, right;
    int size;

    Node *leftchild, *rightchild;
};  // struct Node

static int memcnt;
static Node nodes[8000000];

inline Node *allocate() {
    return &nodes[memcnt++];
}

static Node *history[NMAX + 10];

inline void update(Node *x) {
    x->size = x->leftchild->size + x->rightchild->size;
}

static Node *build(int left, int right) {
    Node *x = allocate();

    x->size = 0;
    if (left == right) {
        x->left = x->right = left;
        x->leftchild = x->rightchild = NULL;
    } else {
        int mid = (left + right) / 2;
        x->left = left;
        x->right = right;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
    }

    return x;
}

static Node *modify(Node *x, int u, int v) {
    Node *y = allocate();
    *y = *x;
    x = y;

    if (x->left == x->right && x->left == u) {
        x->size += v;
    } else {
        int mid = (x->left + x->right) / 2;

        if (u <= mid) {
            x->leftchild = modify(x->leftchild, u, v);
        } else {
            x->rightchild = modify(x->rightchild, u, v);
        }

        update(x);
    }

    return x;
}

static int kth(Node *i, Node *j, int k) {
    if (i->left == i->right) {
        return num[sorted[i->left]];
    }

    int leftsize = j->leftchild->size - i->leftchild->size;
    if (k <= leftsize) {
        return kth(i->leftchild, j->leftchild, k);
    } else {
        return kth(i->rightchild, j->rightchild, k - leftsize);
    }
}

int main() {
    initialize();
    hashing();
    history[0] = build(1, n);

    for (int i = 1; i <= n; i++) {
        history[i] = modify(history[i - 1], id[i], 1);
    }  // for

    for (int cnt = 0; cnt < m; cnt++) {
        int i, j, k;
        // scanf("%d%d%d", &i, &j, &k);
        i = readint();
        j = readint();
        k = readint();

        printf("%d\n", kth(history[i - 1], history[j], k));
    }  // for

    return 0;
}  // function main
