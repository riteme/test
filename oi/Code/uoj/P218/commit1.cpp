#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <algorithm>

using namespace std;

#define INPUT_BUFFERSIZE 65536
static size_t _ipos = INPUT_BUFFERSIZE;
static char _ibuffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (_ipos == INPUT_BUFFERSIZE) {
        _ipos = 0;
        fread(_ibuffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return _ibuffer[_ipos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define OUTPUT_BUFFERSIZE 10000000
static size_t _opos = 0;
static char _obuffer[OUTPUT_BUFFERSIZE];

inline void put_int(const int v) {
    _opos += sprintf(_obuffer + _opos, "%d\n", v);
}

inline void flush_to_stdout() {
    fwrite(_obuffer, 1, _opos, stdout);
}

#define SEED (577777777)

static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

#define NMAX 500000

struct Node {
    Node() {}
    Node(int _left, int _right)
        : left(_left), right(_right),
          sum(0), mark(0),
          leftchild(nullptr), rightchild(nullptr) {}

    int left;
    int right;
    int sum;
    int mark;
    Node *leftchild;
    Node *rightchild;

    int length() const {
        return right - left + 1;
    }

    int get_sum() const {
        if (mark)
            return mark * length();
        return sum;
    }

    void update() {
        if (left < right)
            sum = leftchild->get_sum() + rightchild->get_sum();
    }

    void pushdown() {
        if (mark) {
            sum = mark * length();

            if (left < right) {
                leftchild->mark = mark;
                rightchild->mark = mark;
            }

            mark = 0;
        }
    }

    void modify(int l, int r, int v) {
        if (l <= left && right <= r)
            mark = v;
        else {
            pushdown();
            
            int mid = (left + right) / 2;
            if (r <= mid)
                leftchild->modify(l, r, v);
            else if (l > mid)
                rightchild->modify(l, r, v);
            else {
                leftchild->modify(l, r, v);
                rightchild->modify(l, r, v);
            }

            update();
        }
    }
    
    int query(int l, int r) {
        if (l <= left && right <= r)
            return get_sum();
        else {
            pushdown();

            int mid = (left + right) / 2;
            if (r <= mid)
                return leftchild->query(l, r);
            else if (l > mid)
                return rightchild->query(l, r);
            else
                return leftchild->query(l, r) + rightchild->query(l, r);
        }
    }

    Node *clone() const {
        Node *x = new Node;
        *x = *this;

        return x;
    }

    Node *persistent_modify(int l, int r, int v) {
        Node *x = clone();
        x->_persistent_modify(l, r, v);

        return x;
    }

    void _persistent_modify(int l, int r, int v) {
        if (l <= left && right <= r)
            mark += v;
        else {
            int mid = (left + right) / 2;
            if (r <= mid) {
                leftchild = leftchild->clone();
                leftchild->_persistent_modify(l, r, v);
            } else if (l > mid) {
                rightchild = rightchild->clone();
                rightchild->_persistent_modify(l, r, v);
            } else {
                leftchild = leftchild->clone();
                rightchild = rightchild->clone();
                leftchild->_persistent_modify(l, r, v);
                rightchild->_persistent_modify(l, r, v);
            }
        }
    }

    int persistent_query(int pos) {
        if (left == right)
            return sum + mark;
        else {
            int mid = (left + right) / 2;

            if (pos <= mid)
                return leftchild->persistent_query(pos) + mark;
            else
                return rightchild->persistent_query(pos) + mark;
        }
    }
};

static Node *require_node(int left, int right) {
    Node *x = new Node(left, right);

    if (left < right) {
        int mid = (left + right) / 2;
        x->leftchild = require_node(left, mid);
        x->rightchild = require_node(mid + 1, right);
    }

    return x;
}

struct Treap {
    Treap(int _key)
        : key(_key), size(1),
          left(nullptr), right(nullptr),
          weight(randint()) {}

    int key;
    int size;
    Treap *left;
    Treap *right;
    int weight;

    void update() {
        size = 1;

        if (left)
            size += left->size;
        if (right)
            size += right->size;
    }

    Treap *left_rotate() {
        Treap *y = left;
        left = y->right;
        y->right = this;

        update();
        y->update();

        return y;
    }

    Treap *right_rotate() {
        Treap *y = right;
        right = y->left;
        y->left = this;

        update();
        y->update();

        return y;
    }
};

static Treap *treap_insert(Treap *x, int key) {
    if (!x)
        return new Treap(key);

    if (key < x->key) {
        x->left = treap_insert(x->left, key);

        if (x->left->weight < x->weight)
            return x->left_rotate();
    } else {
        x->right = treap_insert(x->right, key);

        if (x->right->weight < x->weight)
            return x->right_rotate();
    }

    x->update();
    return x;
}

static int treap_query(Treap *x, int v) {
    if (!x)
        return 0;

    if (x->key <= v)
        return treap_query(x->right, v) +
               (x->left ? x->left->size : 0) + 1;
    else
        return treap_query(x->left, v);
}

static int n, m, ty;
static Node *answer;
static int cnt;
static int value[NMAX + 10];
static Node *version[NMAX + 10];
static Treap *removed[NMAX + 10];

static void initialize() {
    // scanf("%d%d%d", &n, &m, &ty);
    n = readint();
    m = readint();
    ty = readint();

    version[0] = require_node(1, n);
    answer = require_node(1, n);
}

inline int evaluate(int pos, int x) {
    return version[x]->persistent_query(pos) -
           treap_query(removed[pos], x);
}

inline int binary_search(int pos, int target) {
    int left = 0, right = cnt;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (evaluate(pos, mid) < target)
            left = mid + 1;
        else
            right = mid;
    }

    if (left != right && evaluate(pos, left) < target)
        left = right;

    return left;
}

int main() {
    // freopen("train.in", "r", stdin);

    initialize();

    int lastans = 0;
    while (m--) {
        int type;
        // scanf("%d", &type);
        type = readint();

        switch (type) {
            case 1: {
                int l, r;
                // scanf("%d%d", &l, &r);
                l = readint();
                r = readint();
                int l1 = (l + lastans * ty) % n + 1;
                int r1 = (r + lastans * ty) % n + 1;
                l = min(l1, r1);
                r = max(l1, r1);

                lastans = answer->query(l, r);
                // printf("%d\n", lastans);
                put_int(lastans);
            } break;

            case 2: {
                int l;
                // scanf("%d", &l);
                l = readint();
                l = (l + lastans * ty) % n + 1;

                int covered = evaluate(l, cnt);

                if (covered == 0)
                    break;

                int fucked = binary_search(l, covered);
                int replaced = binary_search(l, covered - 1);
                removed[l] = treap_insert(removed[l], fucked);
                answer->modify(l, l, value[replaced]);
            } break;

            case 3: {
                int l, r, x;
                // scanf("%d%d%d", &l, &r, &x);
                l = readint();
                r = readint();
                x = readint();
                int l1 = (l + lastans * ty) % n + 1;
                int r1 = (r + lastans * ty) % n + 1;
                l = min(l1, r1);
                r = max(l1, r1);

                cnt++;
                version[cnt] =
                    version[cnt - 1]->persistent_modify(l, r, 1);
                value[cnt] = x;

                answer->modify(l, r, x);
            } break;
        }
    }

    flush_to_stdout();

    return 0;
}
