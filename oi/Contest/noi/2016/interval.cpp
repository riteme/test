#define NDEBUG
#pragma GCC optimize(3)

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At #%d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#define DEBUG(message, ...) printf(message, __VA_ARGS__);
#else
#define TRACE
#define DEBUG
#endif

typedef long long int64;
typedef long double float128;

#define BUFFERSIZE 25565
static size_t _pos = BUFFERSIZE;
static char _buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

struct Interval {
    int left, right;
    int length;

    bool operator<(const Interval &b) const {
        return length < b.length;
    }
};  // struct Interval

struct Node {
    Node()
            : left(0)
            , right(0)
            , value(0)
            , mark(0)
            , leftchild(NULL)
            , rightchild(NULL) {}

    int left;
    int right;
    int value;
    int mark;
    Node *leftchild, *rightchild;
};  // struct Node

#define MEMSIZE 2000000
static Node memory[MEMSIZE];
static size_t memcnt = 0;

inline Node *allocate() {
    return &memory[memcnt++];
}

#define NMAX 500000
#define MMAX 200000

static int n, m;
static Interval interval[NMAX + 10];
static int maxlength;
static int pcnt;
static int p[NMAX * 2 + 10];
static Node *tree;

inline int value_of(Node *x) {
    assert(x);
    return x->value + x->mark;
}

inline void pushdown(Node *x) {
    assert(x);

    if (x->mark != 0) {
        x->value += x->mark;

        if (x->leftchild) {
            x->leftchild->mark += x->mark;
            x->rightchild->mark += x->mark;
        }

        x->mark = 0;
    }
}

inline void update(Node *x) {
    assert(x);
    assert(x->mark == 0);

    if (x->leftchild)
        x->value = max(value_of(x->leftchild), value_of(x->rightchild));
}

static Node *build(int left, int right) {
    assert(left <= right);

    Node *x = allocate();
    x->left = left;
    x->right = right;
    if (left == right) {
        // return new Node(left, left);
        return x;
    } else {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
        return x;
    }
}

static void clear(Node *x) {
    if (!x)
        return;

    x->value = x->mark = 0;
    clear(x->leftchild);
    clear(x->rightchild);
}

static void modify(Node *x, int left, int right, int v) {
    assert(x);

    if (left <= x->left && x->right <= right)
        x->mark += v;
    else {
        pushdown(x);

        int mid = (x->left + x->right) / 2;
        if (right <= mid)
            modify(x->leftchild, left, right, v);
        else if (left > mid)
            modify(x->rightchild, left, right, v);
        else {
            modify(x->leftchild, left, right, v);
            modify(x->rightchild, left, right, v);
        }

        update(x);
    }
}

inline int hashing(int x) {
    return lower_bound(p, p + pcnt, x) - p;
}

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = readint();
    m = readint();

    for (int i = 1; i <= n; i++) {
        int x, y;
        // scanf("%d%d", &x, &y);
        x = readint();
        y = readint();

        interval[i].left = x;
        interval[i].right = y;
        interval[i].length = y - x;
        maxlength = max(maxlength, y - x);
        p[pcnt++] = x;
        p[pcnt++] = y;
    }  // for

    sort(interval + 1, interval + n + 1);
    sort(p, p + pcnt);
    pcnt = unique(p, p + pcnt) - p;

    for (int i = 1; i <= n; i++) {
        interval[i].left = hashing(interval[i].left);
        interval[i].right = hashing(interval[i].right);
    }  // for

    tree = build(0, pcnt - 1);
}

int main() {
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
    initialize();
    TRACE

    int answer = INT_MAX;
    for (int i = 1, j = 0; i <= n; i++) {
        while (j < n && value_of(tree) < m) {
            j++;
            modify(tree, interval[j].left, interval[j].right, 1);
        }  // while

        if (value_of(tree) >= m)
            answer = min(answer, interval[j].length - interval[i].length);

        modify(tree, interval[i].left, interval[i].right, -1);
    }  // for

    if (answer >= INT_MAX)
        puts("-1");
    else
        printf("%d\n", answer);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
