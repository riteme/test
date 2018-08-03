#include <cstdio>
#include <cstring>

#include <stack>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 500000

struct Node {
    Node(int _l, int _r)
        : l(_l), r(_r), size(0), lch(NULL), rch(NULL) {}

    int l, r, size;
    Node *lch, *rch;
};

inline int size_of(Node *x) {
    return x ? x->size : 0;
}

inline void update(Node *x) {
    x->size = size_of(x->lch) + size_of(x->rch);
}

Node *element(int p, int l, int r) {
    Node *x = new Node(l, r);
    x->size = 1;

    if (l != r) {
        int m = (l + r) >> 1;
        if (p <= m) x->lch = element(p, l, m);
        else x->rch = element(p, m + 1, r);
    }

    return x;
}

Node *meld(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;
    x->lch = meld(x->lch, y->lch);
    x->rch = meld(x->rch, y->rch);
    update(x);
    return x;
}

int kth(Node *x, int k) {
    if (x->l == x->r) return x->l;
    if (size_of(x->lch) >= k) return kth(x->lch, k);
    return kth(x->rch, k - size_of(x->lch));
}

int median(Node *x) {
    return kth(x,(x->size + 1) >> 1);
}

i64 eval(Node *x, int p) {
    if (!x) return 0;
    if (x->l == x->r) return abs(x->l - p);
    return eval(x->lch, p) + eval(x->rch, p);
}

static int n, x;
static int bit[NMAX + 10];

inline void modify(int x) {
    for (; x <= n; x += x & -x)
        bit[x]++;
}

inline int query(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += bit[x];
    return ret;
}

int main() {
    scanf("%d", &n);
    n >>= 1;
    i64 ans = 0;
    stack<Node *> stk;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        x >>= 1;
        modify(x);
        ans += i - query(x);

        Node *cur = element(x, 1, n);
        while (!stk.empty() && median(stk.top()) >= median(cur)) {
            cur = meld(cur, stk.top());
            stk.pop();
        }
        stk.push(cur);
    }

    while (!stk.empty()) {
        ans += eval(stk.top(), median(stk.top()));
        stk.pop();
    }

    printf("%lld\n", ans);

    return 0;
}
