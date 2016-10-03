#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <set>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 17

typedef long long int64;

#define A 0
#define B 1

static int n;
static int64 h[NMAX + 10];

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
            , mark(false)
            , left(NULL)
            , right(NULL)
            , next(NULL)
            , prev(NULL) {}

    int weight;
    int key;
    bool mark;
    Node *left;
    Node *right;
    Node *next;
    Node *prev;
};  // struct Node

inline Node *left_rotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;

    return y;
}

inline Node *right_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;

    return y;
}

static Node *insert(Node *x, int key) {
    if (!x)
        return new Node(key);

    if (h[key] < h[x->key]) {
        x->left = insert(x->left, key);

        if (!x->left->next) {
            x->left->next = x;
            if (x->prev) {
                x->prev->next = x->left;
                x->left->prev = x->prev;
            }
            x->prev = x->left;
        }

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else {
        x->right = insert(x->right, key);

        if (!x->right->next) {
            x->right->prev = x;
            if (x->next) {
                x->next->prev = x->right;
                x->right->next = x->next;
            }
            x->next = x->right;
        }

        if (x->right->weight < x->weight)
            return right_rotate(x);
    }

    return x;
}

inline void query_range(Node *x, int key, Node *&lower, Node *&upper) {
    while (x) {
        if (h[key] < h[x->key]) {
            if (x->mark)
                upper = x->next;
            else
                upper = x;

            x = x->left;
        } else {
            if (x->mark)
                lower = x->prev;
            else
                lower = x;

            x = x->right;
        }
    }  // while
}

inline Node *choose_min(Node *tree, int x) {
    Node *lower = NULL, *upper = NULL;
    query_range(tree, x, lower, upper);

    assert(lower != NULL || upper != NULL);

    if (lower == NULL)
        return upper;
    else if (upper == NULL)
        return lower;
    else if (abs(h[lower->key] - h[x]) <= abs(h[upper->key] - h[x]))
        return lower;
    else
        return upper;
}

static int anext[NMAX + 10];
static int bnext[NMAX + 10];

static void evaluate_graph() {
    Node *tree = NULL;
    tree = insert(tree, n);

    for (int i = n - 1; i >= 1; i--) {
        Node *m = choose_min(tree, i);
        bnext[i] = m->key;

        if (i < n - 1) {
            m->mark = true;
            anext[i] = choose_min(tree, i)->key;
            m->mark = false;
        }

        tree = insert(tree, i);
    }  // for
}

static int f[NMAX + 10][LOGN + 1][2];
static int64 sum[NMAX + 10][LOGN + 1][2];
static int64 asum[NMAX + 10][LOGN + 1][2];
static int64 bsum[NMAX + 10][LOGN + 1][2];

static void evaluate_doubling() {
    for (int i = 1; i <= n; i++) {
        f[i][0][A] = anext[i];
        f[i][0][B] = bnext[i];

        if (anext[i])
            asum[i][0][A] = sum[i][0][A] = abs(h[anext[i]] - h[i]);

        if (bnext[i])
            bsum[i][0][B] = sum[i][0][B] = abs(h[bnext[i]] - h[i]);
    }  // for

    for (int i = n; i >= 1; i--) {
        f[i][1][A] = f[anext[i]][0][B];
        f[i][1][B] = f[bnext[i]][0][A];
        sum[i][1][A] = sum[i][0][A] + sum[anext[i]][0][B];
        sum[i][1][B] = sum[i][0][B] + sum[bnext[i]][0][A];
        asum[i][1][A] = asum[i][0][A];
        asum[i][1][B] = asum[bnext[i]][0][A];
        bsum[i][1][A] = bsum[anext[i]][0][B];
        bsum[i][1][B] = bsum[i][0][B];

        for (int j = 2; j <= LOGN; j++) {
            f[i][j][A] = f[f[i][j - 1][A]][j - 1][A];
            f[i][j][B] = f[f[i][j - 1][B]][j - 1][B];
            sum[i][j][A] = sum[i][j - 1][A] + sum[f[i][j - 1][A]][j - 1][A];
            sum[i][j][B] = sum[i][j - 1][B] + sum[f[i][j - 1][B]][j - 1][B];
            asum[i][j][A] = asum[i][j - 1][A] + asum[f[i][j - 1][A]][j - 1][A];
            asum[i][j][B] = asum[i][j - 1][B] + asum[f[i][j - 1][B]][j - 1][B];
            bsum[i][j][A] = bsum[i][j - 1][A] + bsum[f[i][j - 1][A]][j - 1][A];
            bsum[i][j][B] = bsum[i][j - 1][B] + bsum[f[i][j - 1][B]][j - 1][B];
        }  // for
    }      // for
}

typedef pair<int64, int64> Int64Pair;

static Int64Pair query(int s, int64 maxdist) {
    int64 adist = 0;
    int64 bdist = 0;

    for (int i = LOGN; i >= 0; i--) {
        if (f[s][i][A] && sum[s][i][A] <= maxdist) {
            adist += asum[s][i][A];
            bdist += bsum[s][i][A];
            maxdist -= sum[s][i][A];
            s = f[s][i][A];
        }
    }  // for

    return Int64Pair(adist, bdist);
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", h + i);
    }  // for

    evaluate_graph();
    evaluate_doubling();
}

#define EPSILON 0.0000001

template <typename TFloat>
inline bool almost_equal(const TFloat &a, const TFloat &b) {
    return fabs(a - b) < EPSILON;
}

int main() {
    freopen("drive.in", "r", stdin);
    freopen("drive.out", "w", stdout);

    initialize();

    int64 x0;
    scanf("%lld", &x0);

    int64 maxadist = 0;
    int64 maxbdist = 0;
    int maxpos = 0;
    for (int i = 1; i <= n; i++) {
        Int64Pair ab = query(i, x0);

        double mrate = (double)maxadist / (double)maxbdist;
        double crate = (double)ab.first / (double)ab.second;
        if (maxpos == 0 || ((almost_equal(mrate, crate) && h[maxpos] < h[i]) ||
                            mrate > crate)) {
            maxadist = ab.first;
            maxbdist = ab.second;
            maxpos = i;
        }
    }  // for

    printf("%d\n", maxpos);

    int m;
    scanf("%d", &m);

    while (m--) {
        int s;
        scanf("%d%lld", &s, &x0);

        Int64Pair result = query(s, x0);
        printf("%lld %lld\n", result.first, result.second);
    }  // while

    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", anext[i]);
    // }  // for
    // printf("\n");

    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", bnext[i]);
    // }  // for
    // printf("\n");

    return 0;
}  // function main
