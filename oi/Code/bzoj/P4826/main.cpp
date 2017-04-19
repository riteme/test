#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <stack>

using namespace std;

typedef long long i64;

#define NMAX 200000

class SegmentTree {
 public:
    SegmentTree(int n) : _n(n) {
        root = _build(1, n);
    }

    void reset() {
        _reset(root);
    }

    void modify(int left, int right, i64 val) {
        if (right < 1 || left > _n)
            return;
        _modify(root, left, right, val);
    }

    void modify(int pos, i64 val) {
        _modify(root, pos, pos, val);
    }

    i64 query(int left, int right) {
        return _query(root, left, right);
    }

 private:
    struct Node {
        Node(int l, int r)
            : left(l),
              right(r),
              value(0),
              mark(0),
              leftchild(NULL),
              rightchild(NULL) {}

        int left, right;
        i64 value, mark;
        Node *leftchild;
        Node *rightchild;

        int length() {
            return right - left + 1;
        }

        i64 get_value() {
            return value + length() * mark;
        }

        void pushdown() {
            if (mark) {
                value += length() * mark;
                leftchild->mark += mark;
                rightchild->mark += mark;
                mark = 0;
            }
        }

        void update() {
            value = leftchild->get_value() + rightchild->get_value();
        }
    };

    int _n;
    Node *root;

    Node *_build(int left, int right) {
        Node *x = new Node(left, right);

        if (left < right) {
            int mid = (left + right) / 2;
            x->leftchild = _build(left, mid);
            x->rightchild = _build(mid + 1, right);
        }

        return x;
    }

    void _reset(Node *x) {
        if (x) {
            _reset(x->leftchild);
            _reset(x->rightchild);
            x->value = x->mark = 0;
        }
    }

    void _modify(Node *x, int left, int right, i64 val) {
        if (left <= x->left && x->right <= right)
            x->mark += val;
        else {
            x->pushdown();
            int mid = (x->left + x->right) / 2;

            if (left <= mid)
                _modify(x->leftchild, left, right, val);
            if (right > mid)
                _modify(x->rightchild, left, right, val);

            x->update();
        }
    }

    i64 _query(Node *x, int left, int right) {
        if (left <= x->left && x->right <= right)
            return x->get_value();

        x->pushdown();
        int mid = (x->left + x->right) / 2;
        i64 ret = 0;

        if (left <= mid)
            ret += _query(x->leftchild, left, right);
        if (right > mid)
            ret += _query(x->rightchild, left, right);

        return ret;
    }
};  // class SegmentTree

struct Query {
    Query() : cnt1(0), cnt2(0) {}

    int left, right;
    i64 cnt1, cnt2;
};  // struct Query

struct Segment {
    int left, right;

    bool operator<(const Segment &b) const {
        return right < b.right;
    }
};  // struct Segment

static int n, q, t;
static i64 p1, p2;
static int P[NMAX + 10];
static Query que[NMAX + 10];
static Query *ref[NMAX + 10];
static Segment seg[NMAX * 2 + 10];
static SegmentTree *tree;

bool cmp1(const Query *a, const Query *b) {
    return a->right < b->right;
}

bool cmp2(const Query *a, const Query *b) {
    return a->left > b->left;
}

void initialize() {
    scanf("%d%d%lld%lld", &n, &q, &p1, &p2);
    tree = new SegmentTree(n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", P + i);
    }  // for

    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &que[i].left, &que[i].right);
        ref[i] = que + i;
    }  // for

    sort(ref + 1, ref + q + 1, cmp1);
}

static int left[NMAX + 10];
static int right[NMAX + 10];

inline void add_seg(int i, int j) {
    t++;
    seg[t].left = i;
    seg[t].right = j;
}

void solve1() {
    stack<int> stk;
    for (int i = 1; i <= n; i++) {
        int u = 0;
        while (!stk.empty() && P[stk.top()] < P[i]) {
            if (u)
                add_seg(stk.top(), u);

            u = stk.top();
            stk.pop();
            right[u] = i - 1;
            add_seg(u, i);
        }  // while

        if (!stk.empty()) {
            if (u)
                add_seg(stk.top(), u);
            left[i] = stk.top() + 1;
        } else
            left[i] = 1;

        stk.push(i);
    }  // for

    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();

        right[u] = n;
        if (!stk.empty())
            add_seg(stk.top(), u);
    }

    sort(seg + 1, seg + t + 1);

    int i = 1, j = 1;
    for (int c = 1; c <= n; c++) {
        for (; i <= t && seg[i].right == c; i++) {
            tree->modify(seg[i].left, 1);
        }  // for

        for (; j <= q && ref[j]->right == c; j++) {
            ref[j]->cnt1 = tree->query(ref[j]->left, n);
        }  // for
    }      // for
}

void solve2() {
    int j = 1;
    tree->reset();
    for (int i = 1; i <= n; i++) {
        tree->modify(left[i] - 1, i - 1, 1);

        for (; j <= q && ref[j]->right == i; j++) {
            ref[j]->cnt2 += tree->query(ref[j]->left, n);
        }  // for
    }      // for

    sort(ref + 1, ref + q + 1, cmp2);
    j = 1;
    tree->reset();
    for (int i = n; i >= 1; i--) {
        tree->modify(i + 1, right[i] + 1, 1);

        for (; j <= q && ref[j]->left == i; j++) {
            ref[j]->cnt2 += tree->query(1, ref[j]->right);
        }  // for
    }      // for
}

int main() {
    initialize();
    solve1();
    solve2();

    for (int i = 1; i <= q; i++) {
        printf("%lld\n",
               que[i].cnt1 * p1 + (que[i].cnt2 - 2 * que[i].cnt1) * p2);
    }  // for

    return 0;
}
