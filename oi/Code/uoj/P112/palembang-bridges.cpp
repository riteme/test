/**
 * 没有想到K = 1时答案就是坐标中位数
 * 没有想到区间中点来作为K = 2的取min的判定标准
 */

#define NDEBUG

#include <cassert>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int k, n;
static i64 L[NMAX + 10];
static i64 R[NMAX + 10];
static i64 contrib;
static struct {
    i64 val;
    int index;

    template <typename T>
    bool operator<(const T &b) const {
        return val < b.val;
    }
} P[NMAX * 2 + 10];

namespace Solver1 {

i64 main() {
    i64 sum = 0, p = (P[n].val + P[n + 1].val) / 2;
    for (int i = 1; i <= n; i++) {
        sum += abs(R[i] - p) + abs(L[i] - p);
    }  // for

    return sum;
}

}  // namespace Solver1
namespace Solver2 {

struct MyRandom {
    static constexpr int SEED = 577777777;

    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;  // struct MyRandom

class Treap {
 public:
    Treap() : root(nullptr) {}

    void reset() {
        root = nullptr;
    }

    void insert(i64 key) {
        root = _insert(root, key);
    }

    i64 count(i64 key) {
        return _count(root, key);
    }

    i64 kth(i64 k) {
        return _kth(root, k);
    }

    i64 size() {
        return root ? root->size : 0;
    }

 private:
    struct Node {
        Node(int _key)
            : weight(randint()),
              key(_key),
              count(1),
              size(1),
              left(nullptr),
              right(nullptr) {}

        int weight;
        i64 key;
        i64 count;
        i64 size;
        Node *left;
        Node *right;

        void update() {
            size = count + (left ? left->size : 0) + (right ? right->size : 0);
        }

        Node *left_rotate() {
            Node *y = left;
            left = y->right;
            y->right = this;

            update();
            y->update();

            return y;
        }

        Node *right_rotate() {
            Node *y = right;
            right = y->left;
            y->left = this;

            update();
            y->update();

            return y;
        }
    };  // struct Node

    Node *root;

    Node *_insert(Node *x, i64 key) {
        if (!x)
            return new Node(key);

        if (key < x->key) {
            x->left = _insert(x->left, key);

            if (x->left->weight < x->weight)
                return x->left_rotate();
        } else if (key > x->key) {
            x->right = _insert(x->right, key);

            if (x->right->weight < x->weight)
                return x->right_rotate();
        } else
            x->count++;

        x->update();
        return x;
    }

    i64 _count(Node *x, i64 key) {
        if (!x)
            return 0;

        if (key < x->key)
            return _count(x->left, key);
        i64 leftsize = x->left ? x->left->size : 0;
        if (key == x->key)
            return leftsize + x->count;
        else
            return _count(x->right, key) + leftsize + x->count;
    }

    i64 _kth(Node *x, i64 k) {
        if (!x)
            return 0;

        i64 leftsize = x->left ? x->left->size : 0;
        if (k <= leftsize)
            return _kth(x->left, k);
        else if (leftsize < k && k <= leftsize + x->count)
            return x->key;
        else
            return _kth(x->right, k - leftsize - x->count);
    }
};  // class Treap

static double M[NMAX + 10];
static int sorted[NMAX + 10];
static Treap tree;
static i64 pre[NMAX + 10];
static i64 suf[NMAX + 10];
static i64 mid, midv;

i64 push(i64 v) {
    i64 ret = 0;

    tree.insert(v);
    i64 np = tree.size() / 2;
    if (np < mid) {
        mid--;
        i64 to = tree.kth(mid);
        ret -= mid * (midv - to);
        ret += (tree.size() - mid) * (midv - to);
        midv = to;
    } else if (mid < np) {
        mid++;
        i64 to = tree.kth(mid);
        ret += (mid - 1) * (to - midv);
        ret -= (tree.size() - mid) * (to - midv);
        midv = to;
    }

    return ret + abs(midv - v);
}

i64 main() {
    i64 ans = LLONG_MAX;

    for (int i = 1; i <= n; i++) {
        sorted[i] = i;
        M[i] = (static_cast<double>(L[i]) + R[i]) / 2.0;
    }  // for

    sort(sorted + 1, sorted + n + 1,
         [](const int a, const int b) { return M[a] < M[b]; });

    pre[1] = R[sorted[1]] - L[sorted[1]];
    tree.insert(L[sorted[1]]);
    tree.insert(R[sorted[1]]);
    mid = 1, midv = L[sorted[1]];
    for (int i = 2; i <= n; i++) {
        pre[i] = pre[i - 1] + push(L[sorted[i]]) + push(R[sorted[i]]);
    }  // for

    tree.reset();
    suf[n] = R[sorted[n]] - L[sorted[n]];
    tree.insert(L[sorted[n]]);
    tree.insert(R[sorted[n]]);
    mid = 1, midv = L[sorted[n]];
    for (int i = n - 1; i >= 1; i--) {
        suf[i] = suf[i + 1] + push(L[sorted[i]]) + push(R[sorted[i]]);
    }  // for

    for (int i = 0; i <= n; i++) {
        ans = min(ans, pre[i] + suf[i + 1]);
    }  // for

    return ans;
}

}  // namespace Solver2

inline char get_valid_char() {
    char c = getchar();

    while (!isalpha(c)) {
        c = getchar();
    }  // while

    return c;
}

void initialize() {
    scanf("%d%d", &k, &n);

    for (int i = 1; i <= n; i++) {
        char ida, idb;
        i64 p1, p2;
        ida = get_valid_char();
        scanf("%lld", &p1);
        idb = get_valid_char();
        scanf("%lld", &p2);

        if (p1 > p2)
            swap(p1, p2);

        if (ida == idb) {
            contrib += p2 - p1;
            i--, n--;
        } else {
            L[i] = p1, R[i] = p2;
            P[2 * i - 1] = {p1, i};
            P[2 * i] = {p2, i};
        }
    }  // for

    sort(P + 1, P + 2 * n + 1);
}

int main() {
    initialize();

    if (n == 0)
        printf("%lld\n", contrib);
    else if (k == 1)
        printf("%lld\n", Solver1::main() + contrib + n);
    else
        printf("%lld\n", Solver2::main() + contrib + n);

    return 0;
}  // function main
