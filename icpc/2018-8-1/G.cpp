#include <ctime>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 30000
#define INF 3e10

struct Node {
    Node(i64 _key)
        : key(_key), mov(0), v(1), w(rand()), lch(NULL), rch(NULL) {}

    i64 key, mov;
    int v, w;
    Node *lch, *rch;
};

Node *lrotate(Node *x) {
    Node *y = x->lch;
    x->lch = y->rch;
    y->rch = x;
    y->v = x->v;
    x->v = (x->lch ? x->lch->v : 0) + (x->rch ? x->rch->v : 0) + 1;
    return y;
}

Node *rrotate(Node *x) {
    Node *y = x->rch;
    x->rch = y->lch;
    y->lch = x;
    y->v = x->v;
    x->v = (x->lch ? x->lch->v : 0) + (x->rch ? x->rch->v : 0) + 1;
    return y;
}

void pushdown(Node *x) {
    x->key += x->mov;
    if (x->lch) x->lch->mov += x->mov;
    if (x->rch) x->rch->mov += x->mov;
    x->mov = 0;
}

Node *insert(Node *x, i64 key) {
    if (!x) return new Node(key);
    x->v++;
    pushdown(x);
    if (key <= x->key) {
        x->lch = insert(x->lch, key);
        return x->lch->w < x->w ? lrotate(x) : x;
    }
    x->rch = insert(x->rch, key);
    return x->rch->w < x->w ? rrotate(x) : x;
}

Node *remove(Node *x, i64 key) {
    x->v--;
    pushdown(x);
    if (key == x->key) {
        if (!x->rch) return x->lch;
        Node *y = x->rch, *z = x;
        pushdown(y);
        while (y->lch) {
            z = y;
            z->v--;
            y = y->lch;
            pushdown(y);
        }
        if (z == x) z->rch = y->rch;
        else z->lch = y->rch;
        x->key = y->key;
    } else if (key < x->key) x->lch = remove(x->lch, key);
    else x->rch = remove(x->rch, key);
    return x;
}

int kth(Node *x, i64 key) {
    if (!x) return 0;
    pushdown(x);
    if (key < x->key) return kth(x->lch, key);
    return (x->lch ? x->lch->v : 0) + 1 + kth(x->rch, key);
}

static int n, r, K;
static i64 sum, seq[NMAX + 10], pre[NMAX + 10], A[NMAX + 10], B[NMAX + 10];

void initialize() {
    srand(time(NULL));
    scanf("%d%d%d", &n, &r, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
        sum += seq[i];
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        A[i] -= seq[i];
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", B + i);
        B[i] -= A[i] + seq[i];
    }

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + A[i] - (i > r ? A[i - r] : 0);
        seq[i] = seq[i - 1] + B[i] - (i > r ? B[i - r] : 0);
    }
}

int cnt(i64 m) {
    int ret = 0;
    Node *T1 = NULL, *T2 = NULL;
    T2 = insert(T2, seq[r]);
    for (int i = r + 1; i <= n; i++) {
        T2->mov += A[i - r] - B[i - r];
        if (i >= 2 * r) {
            T2 = remove(T2, pre[i - r]);
            T1 = insert(T1, pre[i - r]);
        }
        ret += kth(T1, m - pre[i]) + kth(T2, m - pre[i]);
        T2 = insert(T2, seq[i]);
    }

    return ret;
}

int main() {
    initialize();
    i64 l = 0, r = INF;
    while (l < r) {
        i64 m = (l + r) >> 1;
        if (cnt(m) < K) l = m + 1;
        else r = m;
    }

    printf("%lld\n", sum + l);

    return 0;
}
