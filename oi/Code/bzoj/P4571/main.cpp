// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define CMAX 524288
#define CPOS 18

class SegmentTree {
 public:
    SegmentTree() : last(0) {
        version[0] = _build(0, NMAX);
    }

    void append(int v) {
        version[last + 1] = _modify(version[last], v);
        last++;
    }

    int query(int l1, int r1, int l2, int r2) {
        if (r2 < 0 || l2 > NMAX)
            return 0;
        return _query(version[l1 - 1], version[r1], l2, r2);
    }

 private:
    struct Node {
        Node(int l, int r)
            : left(l), right(r), count(0),
              leftchild(NULL), rightchild(NULL) {}

        int left;
        int right;
        int count;
        Node *leftchild;
        Node *rightchild;
    };

    int last;
    Node *version[NMAX + 10];

    Node *_build(int left, int right) {
        Node *x = new Node(left, right);

        if (left < right) {
            int mid = (left + right) / 2;
            x->leftchild = _build(left, mid);
            x->rightchild = _build(mid + 1, right);
        }

        return x;
    }

    Node *_modify(Node *x, int pos) {
        x = new Node(*x);

        if (x->left == x->right)
            x->count++;
        else {
            int mid = (x->left + x->right) / 2;

            if (pos <= mid)
                x->leftchild = _modify(x->leftchild, pos);
            else
                x->rightchild = _modify(x->rightchild, pos);

            x->count++;
        }
        
        return x;
    }

    int _query(Node *x, Node *y, int left, int right) {
        if (left <= x->left && x->right <= right)
            return y->count - x->count;
        else {
            int mid = (x->left + x->right) / 2;
            int ret = 0;

            if (left <= mid)
                ret += _query(x->leftchild, y->leftchild, left, right);
            if (right > mid)
                ret += _query(x->rightchild, y->rightchild, left, right);

            return ret;
        }
    }
};

static int n, m;
static SegmentTree tree;

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        tree.append(v);
    }
}

int solve(int l1, int r1, int l2, int r2, int b, int x, int pos) {
    if (pos < 0)
        return 0;

    int mid = l2 + (1 << pos) - 1;
    int lc = tree.query(l1, r1, l2 - x, mid - x);
    int rc = tree.query(l1, r1, mid + 1 - x, r2 - x);
    if ((b >> pos) & 1) {
        if (lc)
            return (1 << pos) + solve(l1, r1, l2, mid, b, x, pos - 1);
        else if (rc)
            return solve(l1, r1, mid + 1, r2, b, x, pos - 1);
        else
            return 0;
    } else {
        if (rc)
            return (1 << pos) + solve(l1, r1, mid + 1, r2, b, x, pos - 1);
        else if (lc)
            return solve(l1, r1, l2, mid, b, x, pos - 1);
        else
            return 0;
    }
}

int main() {
    initialize();

    while (m--) {
        int b, x, l, r;
        scanf("%d%d%d%d", &b, &x, &l, &r);
        printf("%d\n", solve(l, r, 0, CMAX, b, x, CPOS));
    }

    return 0;
}
