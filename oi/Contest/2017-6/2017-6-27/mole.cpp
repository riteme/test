/**
 * The best rand is data random?
 */

#define NDEBUG

#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

struct Node {
    Node(int _key)
        : /*weight(rand()),*/
          key(_key), cnt(1), size(1), sum(_key),
          left(NULL), right(NULL) {}

    int /*weight,*/ key, cnt, size;
    i64 sum;
    Node *left, *right;

    // Node *left_rotate() {
    //     Node *y = left;
    //     left = y->right;
    //     y->right = this;

    //     update();
    //     y->update();
    //     return y;
    // }

    // Node *right_rotate() {
    //     Node *y = right;
    //     right = y->left;
    //     y->left = this;

    //     update();
    //     y->update();
    //     return y;
    // }

    void update() {
        size = cnt + (left ? left->size : 0) + (right ? right->size : 0);
        sum = (i64) key * cnt + (left ? left->sum : 0)
                              + (right ? right->sum : 0);
    }
};

Node *insert(Node *x, int key) {
    if (!x)
        return new Node(key);

    x = new Node(*x);
    if (key > x->key) {
        x->left = insert(x->left, key);

        // if (x->left->weight < x->weight)
        //     return x->left_rotate();
    } else if (key < x->key) {
        x->right = insert(x->right, key);

        // if (x->right->weight < x->weight)
        //     return x->right_rotate();
    } else
        x->cnt++;

    x->update();
    return x;
}

int kth(Node *x, int k) {
    if (!x)
        return 0;

    int lsize = (x->left ? x->left->size : 0);

    if (k <= lsize)
        return kth(x->left, k);
    else if (k <= lsize + x->cnt)
        return x->key;
    return kth(x->right, k - lsize - x->cnt);
}

i64 query(Node *x, int k) {
    if (!x)
        return 0;

    int lsize = (x->left ? x->left->size : 0);
    if (k <= lsize)
        return query(x->left, k);

    i64 lsum = (x->left ? x->left->sum : 0);
    if (k <= lsize + x->cnt)
        return (i64) x->key * (k - lsize) + lsum;
    return query(x->right, k - lsize - x->cnt)
           + lsum + (i64) x->key * x->cnt;
}

static int n;
static Node *pre[NMAX + 10];
static Node *suf[NMAX + 10];
static struct Person {
    int a, b, c;

    bool operator<(const Person &b) const {
        return a - c > b.a - b.c;
    }
} seq[NMAX + 10];
static i64 bsum;

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        Person &p = seq[i];
        scanf("%d%d%d", &p.a, &p.b, &p.c);
        p.a -= p.b;
        p.c -= p.b;
        bsum += p.b;
    }

    sort(seq + 1, seq + n + 1);

    for (int i = 1; i <= n; i++) {
        pre[i] = insert(pre[i - 1], seq[i].a);
    }

    for (int i = n; i >= 1; i--) {
        suf[i] = insert(suf[i + 1], seq[i].c);
    }
}

int main() {
    initialize();

    i64 ans = LLONG_MIN;
    for (int i = 1; i <= n; i++) {
        int l = 1, r = min(i, n - i + 1);
        while (l < r) {
            int m = (l + r) / 2 + 1;
            // CAUTION: int + int overflows!!!
            i64 slope = (i64) kth(pre[i], m) + kth(suf[i + 1], m - 1);

            if (slope < 0)
                r = m - 1;
            else
                l = m;
        }

        ans = max(ans, bsum + query(pre[i], l) + query(suf[i + 1], l - 1));
    }

    printf("%lld\n", ans);

    return 0;
}
