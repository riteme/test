// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <map>
#include <algorithm>

using namespace std;

#define NMAX 500000
#define INF LLONG_MAX
#define A 65
#define B 100

#define mp make_pair

typedef unsigned long long u64;
typedef pair<int, int> IntPair;

class ScapegoatTree {
 public:
    ScapegoatTree() {
        root = new Node(0, INF, 1);
        id[1] = INF >> 1;
    }

    void insert(int key, int l, int r) {
        kl[key] = l;
        kr[key] = r;
        _insert(key);
    }

    u64 operator[](const int x) const {
        return id[x];
    }

 private:
    struct Node {
        Node(u64 _l, u64 _r, int _key)
            : l(_l), r(_r), key(_key), size(1),
              left(NULL), right(NULL) {}

        u64 l, r;
        int key, size;
        Node *left, *right;

        void update() {
            size = 1 + (left ? left->size : 0) +
                       (right ? right->size : 0);
        }

        bool required() {
            int lsize = left ? left->size : 0;
            return max(lsize, size - lsize - 1) * B > size * A;
        }
    };

    Node *root;
    int kl[NMAX + 10];
    int kr[NMAX + 10];
    u64 id[NMAX + 10];

    bool cmp(int a, int b) {
        if (b == 1)
            return false;

        u64 la = id[kl[a]];
        u64 ra = id[kr[a]];
        u64 lb = id[kl[b]];
        u64 rb = id[kr[b]];
        return la < lb || (la == lb && ra < rb);
    }

    int tail;
    int val[NMAX + 10];

    void _scan(Node *x) {
        if (!x)
            return;

        _scan(x->left);
        val[tail++] = x->key;
        _scan(x->right);
    }

    Node *_build(u64 l, u64 r, int head, int tail) {
        assert(l <= r);

        if (tail < head)
            return NULL;

        int mid = (head + tail) >> 1;
        u64 imid = id[val[mid]] = (l + r) >> 1;
        Node *x = new Node(l, r, val[mid]);
        x->left = _build(l, imid - 1, head, mid - 1);
        x->right = _build(imid + 1, r, mid + 1, tail);
        x->update();

        return x;
    }

    Node *stk[NMAX + 10];

    Node *_insert(Node *x, int key, u64 l, u64 r) {
        assert(l <= r);

        if (!x) {
            id[key] = (l + r) >> 1;
            return new Node(l, r, key);
        }

        stk[tail++] = x;
        if (cmp(key, x->key))
            x->left = _insert(x->left, key, l, id[x->key] - 1);
        else
            x->right = _insert(x->right, key, id[x->key] + 1, r);

        x->update();
        return x;
    }
    
    void _insert(int key) {
        tail = 0;
        root = _insert(root, key, 0, INF);

        for (int i = 0; i < tail; i++) {
            if (stk[i]->required()) {
                auto v = stk[i];

                tail = 0;
                _scan(v);

                if (i == 0)
                    root = _build(0, INF, 0, tail - 1);
                else {
                    Node *u = stk[i - 1];

                    if (v == u->left)
                        u->left = _build(u->l, id[u->key] - 1, 0, tail - 1);
                    else
                        u->right = _build(id[u->key] + 1, u->r, 0, tail - 1);
                }

                break;
            }
        }
    }
};

static int n, q;
static int a[NMAX + 10];
static ScapegoatTree id;

class SegmentTree {
 public:
    SegmentTree() {
        for (int i = 1; i <= n + 1; i++) {
            a[i] = 1;
        }

        root = _build(1, n);
    }

    void update(int pos) {
        _update(root, pos);
    }

    int query(int l, int r) {
        return _query(root, l, r);
    }

 private:
    struct Node {
        Node(int _l, int _r)
            : l(_l), r(_r), val(l), left(NULL), right(NULL) {}

        int l, r;
        int val;
        Node *left, *right;

        void update() {
            assert(l < r);

            val = -max(mp(id[a[left->val]], -left->val),
                       mp(id[a[right->val]], -right->val)).second;
        }
    };

    Node *root;

    Node *_build(int l, int r) {
        Node *x = new Node(l, r);

        if (l < r) {
            int mid = (l + r) >> 1;
            x->left = _build(l, mid);
            x->right = _build(mid + 1, r);
        }

        return x;
    }

    void _update(Node *x, int pos) {
        if (x->l == x->r)
            return;

        int mid = (x->l + x->r) >> 1;
        if (pos <= mid)
            _update(x->left, pos);
        else
            _update(x->right, pos);

        x->update();
    }

    int _query(Node *x, int l, int r) {
        if (l <= x->l && x->r <= r)
            return x->val;

        int mid = (x->l + x->r) >> 1;
        int lans = n + 1, rans = n + 1;

        if (l <= mid)
            lans = _query(x->left, l, r);
        if (r > mid)
            rans = _query(x->right, l, r);

        return -max(mp(id[a[lans]], -lans), mp(id[a[rans]], -rans)).second;
    }
};

static SegmentTree *seg;
static int cnt;
static map<IntPair, int> ver;

inline char get_op() {
    char c;
    for (c = getchar(); !isalpha(c); c = getchar());
    return c;
}

void initialize() {
    scanf("%d%d", &n, &q);
    seg = new SegmentTree;
    cnt = 1;
}

int main() {
#ifdef USE_FILE_IO
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
#endif
    initialize();

    int l, r, k;
    while (q--) {
        char op = get_op();

        switch (op) {
            case 'C': {
                scanf("%d%d%d", &l, &r, &k);

                auto key = mp(a[l], a[r]);
                if (!ver.count(key)) {
                    ver[key] = ++cnt;
                    id.insert(cnt, a[l], a[r]);
                }

                a[k] = ver[key];
                seg->update(k);
            } break;
            
            case 'Q': {
                scanf("%d%d", &l, &r);
                printf("%d\n", seg->query(l, r));
            } break;
        }
    }

    return 0;
}
