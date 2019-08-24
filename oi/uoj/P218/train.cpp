/**
 * 线段树推标记时要先检查是否有标记！
 */

#include <cassert>
#include <cstdio>
#include <cstring>

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

#define NMAX 500000

class SegmentTree {
 public:
    struct Node {
        Node (int _left, int _right)
            : left(_left), right(_right),
              sum(0), mark(0),
              leftchild(nullptr),
              rightchild(nullptr) {}

        int left;
        int right;
        int sum;
        int mark;
        Node *leftchild;
        Node *rightchild;

        int width() const {
            return right - left + 1;
        }

        int get_sum() const {
            if (mark)
                return mark * width();
            return sum;
        }

        void update() {
            sum = leftchild->get_sum() + rightchild->get_sum();
        }

        void pushdown() {
            if (mark) {
                sum = mark * width();

                if (left < right) {
                    leftchild->mark = mark;
                    rightchild->mark = mark;
                }

                mark = 0;
            }
        }
    };

    SegmentTree(int left, int right) {
        root = build(left, right);
    }

    void modify(int left, int right, int v) {
        modify(root, left, right, v);
    }

    int query(int left, int right) {
        return query(root, left, right);
    }

 private:
    Node *build(int left, int right) {
        Node *x = new Node(left, right);

        if (left < right) {
            int mid = (left + right) / 2;
            x->leftchild = build(left, mid);
            x->rightchild = build(mid + 1, right);
        }

        return x;
    }

    void modify(Node *x, int left, int right, int v) {
        if (left <= x->left && x->right <= right)
            x->mark = v;
        else {
            x->pushdown();

            int mid = (x->left + x->right) / 2;
            if (right <= mid)
                modify(x->leftchild, left, right, v);
            else if (left > mid)
                modify(x->rightchild, left, right, v);
            else {
                modify(x->leftchild, left, right, v);
                modify(x->rightchild, left, right, v);
            }

            x->update();
        }
    }

    int query(Node *x, int left, int right) {
        if (left <= x->left && x->right <= right)
            return x->get_sum();
        else {
            x->pushdown();

            int mid = (x->left + x->right) / 2;
            if (right <= mid)
                return query(x->leftchild, left, right);
            else if (left > mid)
                return query(x->rightchild, left, right);

            return query(x->leftchild, left, right) +
                   query(x->rightchild, left, right);
        }
    }

    Node *root;
};

typedef pair<int, int> IntPair;

class PersistentSegmentTree {
 public:
    struct Node {
        Node (int _left, int _right)
            : left(_left), right(_right),
              value(0), ver(0),
              leftchild(nullptr),
              rightchild(nullptr) {}

        int left;
        int right;
        int value;
        int ver;
        Node *leftchild;
        Node *rightchild;

        Node *clone() const {
            return new Node(*this);
        }
    };

    PersistentSegmentTree(int left, int right) {
        memset(version, 0, sizeof(version));

        cnt = 0;
        version[0] = build(left, right);
    }

    void modify(int left, int right, int v, int t) {
        cnt++;
        version[cnt] = version[cnt - 1]->clone();
        modify(version[cnt], left, right, v, t);
    }

    IntPair query(int ver, int pos) {
        return query(version[ver], pos);
    }

    int latest() const {
        return cnt;
    }

 private:
    Node *build(int left, int right) {
        Node *x = new Node(left, right);

        if (left < right) {
            int mid = (left + right) / 2;
            x->leftchild = build(left, mid);
            x->rightchild = build(mid + 1, right);
        }

        return x;
    }

    void modify(Node *x, int left, int right, int v, int t) {
        if (left <= x->left && x->right <= right) {
            x->value = v;
            x->ver = t;
        } else {
            x->leftchild = x->leftchild->clone();
            x->rightchild = x->rightchild->clone();

            if (x->ver) {
                x->leftchild->value = x->rightchild->value = x->value;
                x->leftchild->ver = x->rightchild->ver = x->ver;
                x->value = x->ver = 0;
            }

            int mid = (x->left + x->right) / 2;
            if (right <= mid)
                modify(x->leftchild, left, right, v, t);
            else if (left > mid)
                modify(x->rightchild, left, right, v, t);
            else {
                modify(x->leftchild, left, right, v, t);
                modify(x->rightchild, left, right, v, t);
            }
        }
    }

    IntPair query(Node *x, int pos) {
        if (x->left == x->right)
            return IntPair(x->value, x->ver);
        else {
            if (x->ver)
                return IntPair(x->value, x->ver); 

            int mid = (x->left + x->right) / 2;
            if (pos <= mid)
                return query(x->leftchild, pos);
            return query(x->rightchild, pos);
        }
    }

    int cnt;
    Node *version[NMAX + 10];
};

static int n, m, ty;
static SegmentTree *answer;
static PersistentSegmentTree *cover;
static int cnt;
static int verid[NMAX + 10];

static void initialize() {
    // scanf("%d%d%d", &n, &m, &ty);
    n = readint();
    m = readint();
    ty = readint();

    answer = new SegmentTree(1, n);
    cover = new PersistentSegmentTree(1, n);
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

                IntPair current = cover->query(cover->latest(), l);

                if (current.second == 0)
                    break;

                IntPair prev = cover->query(verid[current.second] - 1, l);
                answer->modify(l, l, prev.first);
                cover->modify(l, l, prev.first, prev.second);
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

                cover->modify(l, r, x, ++cnt);
                verid[cnt] = cover->latest();
                answer->modify(l, r, x);
            } break;
        }
    }

    flush_to_stdout();

    return 0;
}
