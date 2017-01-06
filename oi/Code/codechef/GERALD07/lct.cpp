#pragma GCC optimize(3)

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define INPUT_BUFFERSIZE 65536
static size_t ipos = INPUT_BUFFERSIZE;
static char ibuffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (ipos == INPUT_BUFFERSIZE) {
        ipos = 0;
        fread(ibuffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return ibuffer[ipos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c)){
        c = _getchar();
    }

    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 200000
#define MMAX 200000
#define QMAX 200000

#define SEED (577777777)

static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

class Treap {
 public:

    struct Node {
        Node (int _key)
            : key(_key), size(1),
              left(nullptr), right(nullptr),
              weight(randint()) {}
        
        int key;
        int size;
        Node *left;
        Node *right;
        int weight;

        void update() {
            size = 1;

            if (left)
                size += left->size;
            if (right)
                size += right->size;
        }

        Node *left_rotate() {
            assert(left);
            
            Node *y = left;
            left = y->right;
            y->right = this;

            update();
            y->update();

            return y;
        }

        Node *right_rotate() {
            assert(right);

            Node *y = right;
            right = y->left;
            y->left = this;

            update();
            y->update();

            return y;
        }
    };

    void insert(int key) {
        root = _insert(root, key);
    }

    void remove(int key) {
        root = _remove(root, key);
    }

    int lower_bound(int key) {
        return _lower_bound(root, key);
    }

    void reset() {
       _reset(root);
       root = nullptr;
    }

 private:
    Node *root;

    Node *_insert(Node *x, int key) {
        if (!x)
            return new Node(key);

        assert(key != x->key);
        if (key < x->key) {
            x->left = _insert(x->left, key);

            if (x->left->weight < x->weight)
                return x->left_rotate();
        } else {
            x->right = _insert(x->right, key);

            if (x->right->weight < x->weight)
                return x->right_rotate();
        }

        x->update();
        return x;
    }

    Node *_remove(Node *x) {
        assert(x);

        if (x->left && x->right) {
            Node *y;

            if (x->left->weight < x->right->weight) {
                y = x->left_rotate();
                y->right = _remove(x);
            } else {
                y = x->right_rotate();
                y->left = _remove(x);
            }

            y->update();
            return y;
        } else {
            Node *next = x->left;

            if (x->right)
                next = x->right;

            delete x;
            return next;
        }
    }

    Node *_remove(Node *x, int key) {
        if (!x)
            return nullptr;

        if (key < x->key)
            x->left = _remove(x->left, key);
        else if (key > x->key)
            x->right = _remove(x->right, key);
        else
            return _remove(x);

        x->update();
        return x;
    }

    int _lower_bound(Node *x, int key) {
        if (!x)
            return 0;
        if (key <= x->key)
            return _lower_bound(x->left, key) +
                   1 + (x->right ? x->right->size : 0);
        else
            return _lower_bound(x->right, key);
    }

    void _reset(Node *x) {
        if (x) {
            _reset(x->left);
            _reset(x->right);
            delete x;
        }
    }
};

#define LCTSIZE (NMAX + MMAX)

class LCT {
 public:

    class Splays {
     public:
        void reset(int n) {
            memset(father, 0, sizeof(int) * (n + 1));
            memset(left, 0, sizeof(int) * (n + 1));
            memset(right, 0, sizeof(int) * (n + 1));
            memset(value, 0, sizeof(int) * (n + 1));
            memset(minvalue, 0, sizeof(int) * (n + 1));
            memset(reversed, 0, sizeof(bool) * (n + 1));
        }

        // father: positive means father in splay tree.
        //         negative means father in LCT.
        //         zero means no both father above.
        int father[LCTSIZE + 10];
        int left[LCTSIZE + 10];
        int right[LCTSIZE + 10];
        int value[LCTSIZE + 10];
        int minvalue[LCTSIZE + 10];
        bool reversed[LCTSIZE + 10];

        void pushdown(int x) {
            if (reversed[x]) {
                swap(left[x], right[x]);

                reversed[left[x]] ^= true;
                reversed[right[x]] ^= true;
                reversed[x] = false;
            }
        }

        void clear(int x) {
            if (x > 0) {
                clear(father[x]);
                pushdown(x);
            }
        }

        void update(int x) {
            minvalue[x] = value[x];

            if (left[x])
                minvalue[x] = min(minvalue[x], minvalue[left[x]]);
            if (right[x])
                minvalue[x] = min(minvalue[x], minvalue[right[x]]);
        }

        void left_rotate(int x) {
            assert(left[x]);

            int y = left[x];
            father[right[y]] = x;
            left[x] = right[y];
            right[y] = x;

            if (father[x] > 0) {
                if (x == left[father[x]])
                    left[father[x]] = y;
                else
                    right[father[x]] = y;
            }

            father[y] = father[x];
            father[x] = y;

            update(x);
            update(y);
        }

        void right_rotate(int x) {
            assert(right[x]);

            int y = right[x];
            father[left[y]] = x;
            right[x] = left[y];
            left[y] = x;

            if (father[x] > 0) {
                if (x == left[father[x]])
                    left[father[x]] = y;
                else
                    right[father[x]] = y;
            }

            father[y] = father[x];
            father[x] = y;

            update(x);
            update(y);
        }

        void splay(int x) {
            clear(x);

            while (father[x] > 0) {
                int f = father[x];
                int pf = father[f];

                if (pf > 0) {
                    if (f == left[pf] && x == left[f])
                        left_rotate(pf);
                    else if (f == right[pf] && x == right[f])
                        right_rotate(pf);
                }

                if (x == left[f])
                    left_rotate(f);
                else
                    right_rotate(f);
            }
        }
    };

    void reset(int n) {
        sp.reset(n);
    }

    Splays sp;

    void access(int x) {
        sp.splay(x);
        sp.father[sp.right[x]] = -x;
        sp.right[x] = 0;
        sp.update(x);

        while (sp.father[x] != 0) {
            assert(sp.father[x] < 0);
            int top = -sp.father[x];
            sp.splay(top);

            assert(!sp.reversed[top]);
            sp.father[sp.right[top]] = -top;
            sp.father[x] = top;
            sp.right[top] = x;
            sp.update(top);

            x = top;
        }
    }

    void make_root(int x) {
        access(x);
        sp.splay(x);

        assert(sp.father[x] == 0);
        sp.reversed[x] ^= true;
    }

    int father(int x) {
        sp.splay(x);

        if (sp.left[x])
            return sp.left[x];  // What?
        else
            return -sp.father[x];
    }

    int find_root(int x) {
        sp.splay(x);

        while (sp.father[x] != 0) {
            assert(sp.father[x] < 0);
            x = -sp.father[x];
            sp.splay(x);
        }

        while (sp.left[x]) {
            x = sp.left[x];
        }

        return x;
    }

    void cut(int x) {
        int f = father(x);

        if (f == 0)
            return;

        access(f);
        sp.splay(x);
        sp.father[x] = 0;
    }

    void link(int x, int y) {
        make_root(y);
        sp.father[y] = -x;
    }
};

static int n, m, q;
static int U[MMAX + 10], V[MMAX + 10];
static int L[QMAX + 10], R[QMAX + 10];
static int answer[QMAX + 10];
static vector<int> Q[NMAX + 10];
static LCT lct;
static Treap bst;

static void initialize() {
    // scanf("%d%d%d", &n, &m, &q);
    n = readint();
    m = readint();
    q = readint();

    lct.reset(n + m);
    bst.reset();

    for (int i = 1; i <= n; i++) {
        lct.sp.value[i] = lct.sp.minvalue[i] = INT_MAX;
    }

    for (int i = 1; i <= m; i++) {
        // scanf("%d%d", U + i, V + i);
        U[i] = readint();
        V[i] = readint();
        lct.sp.value[n + i] = lct.sp.minvalue[n + i] = i;
    }

    for (int i = 1; i <= q; i++) {
        // scanf("%d%d", L + i, R + i);
        L[i] = readint();
        R[i] = readint();
        Q[R[i]].push_back(i);
    }
}

static void cleanup() {
    for (int i = 1; i <= m; i++) {
        Q[i].clear();
    }
}

static void update(int e) {
    int u = U[e], v = V[e];

    if (u == v)
        return;

    if (lct.find_root(u) == lct.find_root(v)) {
        lct.make_root(u);
        lct.access(v);
        lct.sp.splay(v);
        
        int old = lct.sp.minvalue[v];
        lct.make_root(n + old);
        lct.cut(U[old]);
        lct.cut(V[old]);

        bst.remove(old);
    }

    lct.link(n + e, u);
    lct.link(n + e, v);

    bst.insert(e);
}

int main() {
    int t;
    // scanf("%d", &t);
    t = readint();

    while (t--) {
        initialize();

        for (int e = 1; e <= m; e++) {
            update(e);

            for (size_t i = 0; i < Q[e].size(); i++) {
                int query = Q[e][i];
                int cnt = bst.lower_bound(L[query]);
                answer[query] = n - cnt;
            }
        }

        for (int i = 1; i <= q; i++) {
            printf("%d\n", answer[i]);
        }

        cleanup();
    }

    return 0;
}

