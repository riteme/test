#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define LOGN 21

#define SEED (233)
static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

static int n;
static int f[NMAX + 10][LOGN + 1];

struct Node {
    Node(int _key) : key(_key), weight(randint()), left(NULL), right(NULL) {}

    int key;
    int weight;

    Node *left, *right;
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

    if (key < x->key) {
        x->left = insert(x->left, key);

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else {
        x->right = insert(x->right, key);

        if (x->right->weight < x->weight)
            return right_rotate(x);
    }

    return x;
}

static Node *remove(Node *x) {
    if (x->left != NULL && x->right != NULL) {
        Node *h;
        if (x->left->weight > x->right->weight) {
            h = right_rotate(x);
            h->left = remove(x);
        } else {
            h = left_rotate(x);
            h->right = remove(x);
        }

        return h;
    } else {
        if (x->left)
            return x->left;
        else
            return x->right;
    }
}

static Node *remove(Node *x, int key) {
    if (!x)
        return NULL;

    if (key < x->key)
        x->left = remove(x->left, key);
    else if (key > x->key)
        x->right = remove(x->right, key);
    else
        return remove(x);

    return x;
}

typedef pair<int, int> IntPair;

static void near(Node *x, int key, IntPair &result) {
    if (!x)
        return;

    if (key < x->key) {
        result.second = x->key;
        near(x->left, key, result);
    } else {
        result.first = x->key;
        near(x->right, key, result);
    }
}

static int out[NMAX + 10];
static int depth[NMAX + 10];

static int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int dist = depth[u] - depth[v];
    for (int i = LOGN; i >= 0; i--) {
        if (dist & (1 << i))
            u = f[u][i];
    }  // for

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }  // for

    return f[u][0];
}

inline void compute(int x, int father) {
    f[x][0] = father;

    for (int i = 1; i <= LOGN; i++)
        f[x][i] = f[f[x][i - 1]][i - 1];
}

int main() {
    scanf("%d", &n);

    Node *tree = NULL;
    for (int i = 0; i < n; i++) {
        int u, k;
        scanf("%d%d", &u, &k);

        IntPair result;
        near(tree, u, result);

        int father;
        if (result.first == 0 && result.second == 0)
            father = 0;
        else if (result.first == 0)
            father = result.second;
        else if (result.second == 0)
            father = result.first;
        else {
            if (u < lca(result.first, result.second))
                father = result.first;
            else
                father = result.second;
        }

        out[father]++;
        depth[u] = depth[father] + 1;
        compute(u, father);

        if (out[father] == 2)
            tree = remove(tree, father);
        tree = insert(tree, u);

        int dist = depth[u] - k;
        for (int j = LOGN; j >= 0; j--) {
            if (dist & (1 << j))
                u = f[u][j];
        }  // for

        printf("%d\n", u);
    }  // for

    return 0;
}  // function main
