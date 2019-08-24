// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define PMAX 60
#define MOD 19961993

typedef long long i64;

inline i64 qpow(i64 a, i64 b) {
    i64 r = 1;

    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

inline i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

static int q;
static i64 prime[PMAX + 10];
static i64 pdiv[PMAX + 10];

inline i64 phi(i64 n, i64 mask) {
    for (int i = 0; i < PMAX; i++) {
        if ((mask >> i) & 1)
            n = n * pdiv[i] % MOD;
    }

    return n;
}

inline i64 factor(i64 n) {
    i64 mask = 0;

    for (int i = 0; i < PMAX; i++) {
        if (n % prime[i] == 0)
            mask |= 1LL << i;
    }

    return mask;
}

class SegmentTree {
 public:
    SegmentTree() {
        root = _build(1, NMAX);
    }

    void modify(int pos, i64 val) {
        _modify(root, pos, val);
    }

    i64 query(int l, int r) {
        i64 prod = 1, mask = 0;
        _query(root, l, r, prod, mask);
        return phi(prod, mask);
    }

 private:
    struct Node {
        Node(int l, int r)
            : left(l), right(r),
              prod(3), mask(2),
              lch(NULL), rch(NULL) {}

        int left, right;
        i64 prod, mask;
        Node *lch, *rch;

        void update() {
            assert(left < right);
            prod = lch->prod * rch->prod % MOD;
            mask = lch->mask | rch->mask;
        }
    };

    Node *root;

    Node *_build(int l, int r) {
        Node *x = new Node(l, r);

        if (l < r) {
            int mid = (l + r) / 2;
            x->lch = _build(l, mid);
            x->rch = _build(mid + 1, r);
            x->update();
        }

        return x;
    }

    void _modify(Node *x, int pos, i64 val) {
        if (x->left == x->right) {
            x->prod = val % MOD;
            x->mask = factor(val);
        } else {
            int mid = (x->left + x->right) / 2;

            if (pos <= mid)
                _modify(x->lch, pos, val);
            else
                _modify(x->rch, pos, val);

            x->update();
        }
    }

    void _query(Node *x, int l, int r, i64 &prod, i64 &mask) {
        if (l <= x->left && x->right <= r) {
            prod = prod * x->prod % MOD;
            mask |= x->mask;
        } else {
            int mid = (x->left + x->right) / 2;

            if (l <= mid)
                _query(x->lch, l, r, prod, mask);
            if (r > mid)
                _query(x->rch, l, r, prod, mask);
        }
    }
};

void initialize() {
    scanf("%d", &q);

    int cnt = 0;
    for (int i = 2; cnt < PMAX; i++) {
        bool flag = true;
        for (int j = 2; flag && j * j <= i; j++) {
            flag = i % j;
        }

        if (flag) {
            prime[cnt] = i;
            pdiv[cnt++] = (i - 1) * inv(i) % MOD;
        }
    }
}

int main() {
    initialize();

    SegmentTree *tree = new SegmentTree;
    while (q--) {
        i64 a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);

        if (a == 0)
            printf("%lld\n", tree->query(b, c));
        else
            tree->modify(b, c);
    }

    return 0;
}
