// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define CMAX 2000000000

typedef long long i64;

class SegmentTree {
 public:
    SegmentTree() {
        ver[0] = new Node(-CMAX, CMAX);
    }

    void append(int p, int v) {
        ver[p] = _modify(ver[p - 1], v, -CMAX, CMAX);
    }

    i64 query(int l, int r, int k) {
        return _query(ver[l - 1], ver[r], k);
    }

 private:
    struct Node {
        Node(int l, int r)
            : left(l), right(r), cnt(0), sum(0),
              lch(NULL), rch(NULL) {}

        int left, right;
        int cnt;
        i64 sum;
        Node *lch, *rch;

        void update() {
            cnt = sum = 0;

            if (lch) {
                cnt += lch->cnt;
                sum += lch->cnt;
            }

            if (rch) {
                cnt += rch->cnt;
                sum += rch->sum;
            }
        }
    };

    Node *ver[NMAX + 10];

    Node *_modify(Node *x, int p, int l, int r) {
        x = x ? new Node(*x) : new Node(l, r);

        if (l == r) {
            x->cnt++;
            x->sum += p;
        } else {
            int m = l + ((i64)r - l) / 2;

            if (p <= m)
                x->lch = _modify(x->lch, p, l, m);
            else
                x->rch = _modify(x->rch, p, m + 1, r);

            x->update();
        }

        return x;
    }

    i64 _query(Node *x, Node *y, int k) {
        if (k == -1)
            return (y ? y->sum : 0) - (x ? x->sum : 0);
        if (k == 0 || (!x && !y))
            return 0;
        assert(y);
        if (y->left == y->right)
            return (i64) y->left * min(k, y->cnt);

        int lcnt = (y && y->lch ? y->lch->cnt : 0) - 
                   (x && x->lch ? x->lch->cnt : 0);
        if (k > lcnt)
            return _query(x ? x->lch : NULL, y->lch, -1) +
                   _query(x ? x->lch : NULL, y->rch, k - lcnt);
        else
            return _query(x ? x->lch : NULL, y->lch, k);
    }
};

static int n;
static struct Element {
    int a, b, c;
} seq[NMAX + 10];
static SegmentTree *treea, *treec;

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        Element &e = seq[i];
        scanf("%d%d%d", &e.a, &e.b, &e.c);
    }

    sort(seq + 1, seq + n + 1,
         [](const Element &a, const Element &b) {
             return a.a - a.c > b.a - b.c;
         });
    
    treea = new SegmentTree;
    treec = new SegmentTree;

    for (int i = 1; i <= n; i++) {
        treea->append(i, seq[i].a - seq[i].b);
        treec->append(i, seq[i].c - seq[i].b);
    }
}

inline i64 query(int p, int x) {
    return treea->query(1, p, x) + treec->query(p + 1, n, x - 1);
}

int main() {
    freopen("data.in", "r", stdin);
    initialize();

    i64 ans = -1e18;
    for (int i = 1; i <= n; i++) {
        int l = 1, r = min(i, n - i);
        while (l + 1 < r) {
            int m = (l + r) / 2;
            int slope = query(i, m + 1) - query(i, m);

            if (slope < 0)
                r = m;
            else
                l = m + 1;
        }

        ans = max(ans, query(i, l));
        ans = max(ans, query(i, l + 1));
    }

    printf("%lld\n", ans);

    return 0;
}
