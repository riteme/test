/**
 * 分块大法好，块大小设为sqrt(n log n)之后的复杂度为O(m sqrt(n log n))
 * 具体做法是当前块内暴力，其它的块用平衡树维护方便查询
 * 根号大法跑得好慢......
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At #%d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#define DEBUG(message, ...) printf(message, __VA_ARGS__);
#else
#define TRACE
#define DEBUG
#endif  // IFNDEF NDEBUG

#define NMAX 100000
#define MMAX 50000
#define BLOCKSIZE 3000  // sqrt(n log n) per block

typedef long long int64;

static int n, m;
static int64 cnt;
static int seq[NMAX + 10];
static int pos[NMAX + 10];
static bool alive[NMAX + 10];

class FenwickArray {
 public:
    FenwickArray(const size_t size) : _size(size) {
        _s = new int64[size];
    }

    void modify(const size_t x, const int64 v) {
        _modify(x, v);
    }

    int64 query(const size_t left, const size_t right) const {
        return _query(right) - _query(left - 1);
    }

 private:
    void _modify(const size_t x, const int64 v) {
        assert(x > 0);

        for (size_t i = x; i <= _size; i += i & (-i))
            _s[i] += v;
    }

    int64 _query(const size_t r) const {
        if (r <= 0)
            return 0;

        int64 result = 0;

        for (size_t i = r; i; i -= i & (-i))
            result += _s[i];

        return result;
    }

    size_t _size;
    int64 *_s;
};  // class FenwickArray

#define SEED (233)
static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

struct Node {
    Node(int _key)
            : weight(randint())
            , key(_key)
            , size(1)
            , deleted(false)
            , left(NULL)
            , right(NULL) {}

    int weight;
    int key;
    int size;
    bool deleted;
    Node *left, *right;
};  // struct Node

inline void update(Node *x) {
    x->size = (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0) +
              (x->deleted ? 0 : 1);
}

inline Node *left_rotate(Node *x) {
    assert(x);
    assert(x->left);

    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

inline Node *right_rotate(Node *x) {
    assert(x);
    assert(x->right);

    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

static Node *insert(Node *x, int key) {
    if (!x)
        return new Node(key);

    if (key < x->key)
        x->left = insert(x->left, key);
    else
        x->right = insert(x->right, key);

    update(x);
    return x;
}

static void remove(Node *x, int key) {
    if (!x)
        return;

    if (key < x->key)
        remove(x->left, key);
    else if (key > x->key)
        remove(x->right, key);
    else
        x->deleted = true;

    update(x);
}

static int query_less(Node *x, int key) {
    if (!x)
        return 0;

    if (key < x->key)
        return query_less(x->left, key);
    else
        return query_less(x->right, key) + (x->left ? x->left->size : 0) +
               (x->deleted ? 0 : 1);
}

static int query_greater(Node *x, int key) {
    if (!x)
        return 0;

    if (key > x->key)
        return query_greater(x->right, key);
    else
        return query_greater(x->left, key) + (x->right ? x->right->size : 0) +
               (x->deleted ? 0 : 1);
}

static int blockcnt;
static int lbound[BLOCKSIZE * 2];
static int rbound[BLOCKSIZE * 2];
static Node *ds[BLOCKSIZE * 2];

static void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
        pos[seq[i]] = i;
    }

    FenwickArray fenwick(NMAX + 10);
    for (int i = 1; i <= n; i++) {
        cnt += fenwick.query(seq[i], n);
        fenwick.modify(seq[i], 1);
    }  // for

    for (int i = 0; BLOCKSIZE * i < n; i++) {
        blockcnt++;
        lbound[i] = BLOCKSIZE * i + 1;
        rbound[i] = min(lbound[i] + BLOCKSIZE - 1, n);

        for (int j = lbound[i]; j <= rbound[i]; j++)
            ds[i] = insert(ds[i], seq[j]);
    }  // for

    for (int i = 1; i <= n; i++) {
        alive[i] = true;
    }  // for
}

int main() {
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
    initialize();

    for (int _cnt = 0; _cnt < m; _cnt++) {
        printf("%lld\n", cnt);

        int x;
        scanf("%d", &x);
        int blockid =
            upper_bound(lbound, lbound + blockcnt, pos[x]) - lbound - 1;
        DEBUG("pos[x] = %d, id = %d\n", pos[x], blockid);

        remove(ds[blockid], x);
        alive[pos[x]] = false;
        for (int i = pos[x] + 1; i <= rbound[blockid]; i++) {
            if (alive[i] && x > seq[i])
                cnt--;
        }  // for

        for (int i = lbound[blockid]; i < pos[x]; i++) {
            if (alive[i] && seq[i] > x)
                cnt--;
        }  // for

        for (int i = blockid + 1; i < blockcnt; i++)
            cnt -= query_less(ds[i], x);
        for (int i = 0; i < blockid; i++)
            cnt -= query_greater(ds[i], x);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
