#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

#define NMAX 1000000
// TODO: restore last line
//#define NMAX 16
#define MMAX 30000
#define INF 0x3f3f3f3f

typedef unsigned long long u64;

inline u64 mkpair(int x, int y) {
    return (static_cast<u64>(x) << 32) | y;
}

struct SegmentTree {
    struct Node {
        int l, r, v, acc;
        Node *lch, *rch;

        int gv() {
            return v + acc;
        }

        void push() {
            if (acc) {
                v += acc;
                if (l < r) {
                    lch->acc += acc;
                    rch->acc += acc;
                }
                acc = 0;
            }
        }

        void update() {
            v = min(lch->gv(), rch->gv());
        }
    };

    SegmentTree(int l, int r) {
        root = build(l, r);
    }

    Node *root;

    void reset(int *a) {
        reset(root, a);
    }

    static void reset(Node *x, int *a) {
        x->acc = 0;
        if (x->l == x->r) x->v = a[x->l] ? a[x->l] : INF;
        else {
            reset(x->lch, a);
            reset(x->rch, a);
            x->update();
        }
    }

    static Node* build(int l, int r) {
        Node *x = new Node{l, r, INF, 0, NULL, NULL};
        if (l < r) {
            int m = (l + r) >> 1;
            x->lch = build(l, m);
            x->rch = build(m + 1, r);
        }
        return x;
    }

    void modify(int l, int r, int v) {
        modify(root, l, r, v);
    }

    static void modify(Node *x, int l, int r, int v) {
        if (l <= x->l && x->r <= r) x->acc += v;
        else {
            x->push();
            int m = (x->l + x->r) >> 1;
            if (l <= m) modify(x->lch, l, r, v);
            if (r > m) modify(x->rch, l, r, v);
            x->update();
        }
    }

    template <typename T>
    void search(int l, int r, int v, const T &f) {
        search(root, l, r, v, f);
    }

    template <typename T>
    static void search(Node *x, int l, int r, int v, const T &f) {
        x->push();
        if (x->l == x->r) x->v = f(x->l);
        else {
            int m = (x->l + x->r) >> 1;
            if (l <= m && x->lch->gv() == v) search(x->lch, l, r, v, f);
            if (r > m && x->rch->gv() == v) search(x->rch, l, r, v, f);
            x->update();
        }
    }

    template <typename T>
    void search2(int l, int r, int v, const T &f) {
        search2(root, l, r, v, f);
    }

    template <typename T>
    static void search2(Node *x, int l, int r, int v, const T &f) {
        x->push();
        if (x->l == x->r) f(x->l);
        else {
            int m = (x->l + x->r) >> 1;
            if (l <= m && x->lch->gv() == v) search2(x->lch, l, r, v, f);
            if (r > m && x->rch->gv() == v) search2(x->rch, l, r, v, f);
        }
    }
};

static int n, m;
static int L[MMAX + 10], R[MMAX + 10];

struct IntervalTree {
    struct Node {
        Node(int i) : key(i), mil(L[i]), mxr(R[i]) {}

        int w = rand();
        int key, mil, mxr;
        Node *lch = NULL, *rch = NULL;

        void update() {
            mil = lch ? lch->mil : L[key];
            mxr = max(R[key], max(lch ? lch->mxr : 0, rch ? rch->mxr : 0));
        }
    };

    Node *root = NULL;

    static Node *lrot(Node *x) {
        Node *y = x->lch;
        x->lch = y->rch;
        y->rch = x;
        x->update();
        y->update();
        return y;
    }

    static Node *rrot(Node *x) {
        Node *y = x->rch;
        x->rch = y->lch;
        y->lch = x;
        x->update();
        y->update();
        return y;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    static inline bool lt(int x, int y) {
        return L[x] < L[y] || (L[x] == L[y] && R[x] < R[y]);
    }

    static Node* insert(Node *x, int key) {
        if (!x) return new Node(key);
        if (lt(key, x->key)) {
            x->lch = insert(x->lch, key);
            if (x->lch->w < x->w) return lrot(x);
        } else {
            x->rch = insert(x->rch, key);
            if (x->rch->w < x->w) return rrot(x);
        }
        x->update();
        return x;
    }

    void remove(int key) {
        root = remove(root, key);
    }

    static Node* min(Node *x, Node *p = NULL) {
        if (!x->lch) {
            if (p) p->lch = x->rch;
            return x;
        }
        auto y = min(x->lch, x);
        x->update();
        return y;
    }

    static Node* _remove(Node *x) {
        if (!x->rch) return x->lch;
        Node *y = min(x->rch);
        if (y != x->rch) y->rch = x->rch;
        y->lch = x->lch;
        y->update();
        return y;
    }

    static Node* remove(Node *x, int key) {
        if (x->key == key) return _remove(x);
        if (lt(key, x->key)) x->lch = remove(x->lch, key);
        else x->rch = remove(x->rch, key);
        x->update();
        return x;
    }

    int locate(int p) {
        return locate(root, p);
    }

    static int locate(Node *x, int p) {
        if (L[x->key] <= p && p <= R[x->key]) return x->key;
        if (x->lch && x->lch->mil <= p && p <= x->lch->mxr) return locate(x->lch, p);
        return locate(x->rch, p);
    }
};

struct Heap {
    struct Node {
        int key, val;

        bool operator<(const Node &z) const {
            return val < z.val || (val == z.val && key < z.key);
        }

        bool operator==(const Node &z) const {
            return key == z.key && val == z.val;
        }
    };

    priority_queue<Node> Q, D;

    void clear() {
        //while (!Q.empty()) Q.pop();
        //while (!D.empty()) D.pop();
        Q = {};
        D = {};
    }

    void push(int key, int val) {
        Q.push({key, val});
    }

    void pop(int key, int val) {
        D.push({key, val});
    }

    Node pop() {
        while (!D.empty() && Q.top() == D.top()) {
            Q.pop();
            D.pop();
        }
        auto u = Q.top();
        Q.pop();
        return u;
    }
};

static int sum[NMAX + 10], cnt[NMAX + 10], re[MMAX + 10];

int main() {
    srand(time(NULL));
    int T;
    scanf("%d", &T);
    SegmentTree *seg = new SegmentTree(1, NMAX);
    IntervalTree *tr = new IntervalTree;
    Heap *q = new Heap;
    unordered_set<u64> mp;
    for (int t = 1; t <= T; t++) {
        scanf("%d%d", &n, &m);
        //fprintf(stderr, "m = %d\n", m);
        memset(sum, 0, sizeof(sum));
        mp.clear();
        bool valid = true;
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", L + i, R + i);
            auto p = mkpair(L[i], R[i]);
            if (mp.count(p)) valid = false;
            mp.insert(p);
            sum[L[i]]++;
            sum[R[i] + 1]--;
        }
        if (!valid) {
            printf("Case #%d: 0\n", t);
            continue;
        }

        q->clear();
        assert(tr->root == NULL);
        for (int i = 1; i <= n + 1; i++) {
            sum[i] += sum[i - 1];
            cnt[i] = cnt[i - 1] + (sum[i] == 1);
        }
        seg->reset(sum);
        for (int i = 1; i <= m; i++) {
            tr->insert(i);
            re[i] = cnt[R[i]] - cnt[L[i] - 1];
            //fprintf(stderr, "%d ", re[i]);
            q->push(i, re[i]);
        }
        //fputs("\n", stderr);

        int ans = INF;
        for (int i = 1; i <= m; i++) {
            auto u = q->pop();
            //fprintf(stderr, "%d: %d [i = %d, m = %d]\n", u.key, u.val, i, m);
            ans = min(ans, u.val);
            int l = L[u.key], r = R[u.key];
            tr->remove(u.key);
            seg->modify(l, r, -1);
            seg->search(l, r, 0, [](int) { return INF; });
            seg->search2(l, r, 1, [&](int p) {
                int x = tr->locate(p);
                q->pop(x, re[x]);
                re[x]++;
                q->push(x, re[x]);
            });
        }
        printf("Case #%d: %d\n", t, ans);
    }

    return 0;
}
