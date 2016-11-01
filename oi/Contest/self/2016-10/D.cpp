#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <vector>
#include <algorithm>

using namespace std;

#define SEED (233)

static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

struct Treap {
    Treap(const int _key, const int _value)
        : key(_key), value(_value), sum(_value),
          weight(randint()),
          left(nullptr), right(nullptr) {}

    int key;
    int value;
    int sum;
    int weight;
    Treap *left;
    Treap *right;
};

inline void update(Treap *x) {
    x->sum = x->value + (x->left ? x->left->sum : 0) +
                        (x->right ? x->right->sum : 0);
}

inline Treap *left_rotate(Treap *x) {
    Treap *y = x->left;
    x->left = y->right;
    y->right = x;

    update(x);
    update(y);

    return y;
}

inline Treap *right_rotate(Treap *x) {
    Treap *y = x->right;
    x->right = y->left;
    y->left = x;

    update(x);
    update(y);

    return y;
}

static Treap *treap_insert(Treap *x, int key, int value) {
    if (!x)
        return new Treap(key, value);

    if (key < x->key) {
        x->left = treap_insert(x->left, key, value);

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else if (key > x->key) {
        x->right = treap_insert(x->right, key, value);

        if (x->right->weight < x->weight)
            return right_rotate(x);
    } else
        x->value += value;

    update(x);
    return x;
}

typedef pair<Treap *, Treap *> TreapPair;

static TreapPair split(Treap *x, int key) {
    if (!x)
        return TreapPair(nullptr, nullptr);

    TreapPair result;
    if (key <= x->key) {
        result = split(x->left, key);
        x->left = result.second;
        result.second = x;
    } else {
        result = split(x->right, key);
        x->right = result.first;
        result.first = x;
    }

    update(x);
    return result;
}

static Treap *quick_merge(Treap *x, Treap *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    if (x->weight < y->weight) {
        x->right = quick_merge(x->right, y);
        update(x);
        return x;
    } else {
        y->left = quick_merge(x, y->left);
        update(y);
        return y;
    }
}

static int query_less(Treap *&x, int v) {
    auto a = split(x, v);
    int result = a.first ? a.first->sum : 0;
    x = quick_merge(a.first, a.second);

    return result;
}

struct Node {
    Node(int _left, int _right)
        : left(_left), right(_right), tree(nullptr),
          leftchild(nullptr), rightchild(nullptr) {}

    int left;
    int right;
    Treap *tree;
    Node *leftchild;
    Node *rightchild;
};

static Node *build(int left, int right) {
    Node *x = new Node(left, right);

    if (left != right) {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
    }
    
    return x;
}

static void modify(Node *x, int left, int right, int pos, int v) {
    if (left <= x->left && x->right <= right)
        x->tree = treap_insert(x->tree, pos, v);
    else {
        int mid = (x->left + x->right) / 2;

        if (right <= mid)
            modify(x->leftchild, left, right, pos, v);
        else if (left > mid)
            modify(x->rightchild, left, right, pos, v);
        else {
            modify(x->leftchild, left, right, pos, v);
            modify(x->rightchild, left, right, pos, v);
        }
    }
}

static int query(Node *x, int pos, int v) {
    int result = query_less(x->tree, v);

    if (x->left != x->right) {
        int mid = (x->left + x->right) / 2;

        if (pos <= mid)
            result += query(x->leftchild, pos, v);
        else
            result += query(x->rightchild, pos, v);
    }

    return result;
}

#define NMAX 100000
#define WMAX 1000000000

static int n, q;
static vector<int> G[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static bool marked[NMAX + 10];
static Node *tree;
static int hisx[NMAX + 10];
static int hisw[NMAX + 10];

static void dfs(int x) {
    marked[x] = true;
    in[x] = ++timestamp;

    for (int v : G[x]) {
        if (marked[v])
            continue;

        dfs(v);
    }

    out[x] = timestamp;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1);
    tree = build(1, n);
}

int main() {
    // freopen("D.in", "r", stdin);

    initialize();
    scanf("%d", &q);

    for (int i = 1; i <= q; i++) {
        int type;
        scanf("%d", &type);

        switch (type) {
            case 1: {
                int x, w;
                scanf("%d%d", &x, &w);

                modify(tree, in[x], out[x], w, 1);
                hisx[i] = x;
                hisw[i] = w;
            } break;

            case 2: {
                int k;
                scanf("%d", &k);

                modify(tree, in[hisx[k]], out[hisx[k]], hisw[k], -1);
            } break;

            case 3: {
                int x, k;
                scanf("%d%d", &x, &k);

                if (k == 0)
                    puts("-1");
                else {
                    int left = 0, right = WMAX;
                    while (left + 1 < right) {
                        int mid = (left + right) / 2;

                        if (query(tree, in[x], mid) < k)
                            left = mid;
                        else
                            right = mid;
                    }

                    if (left != right && query(tree, in[x], right) < k)
                        left = right;

                    printf("%d\n", left);
                }
            } break;
        }
    }
}
