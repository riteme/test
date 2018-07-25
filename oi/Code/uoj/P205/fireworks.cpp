// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define NMAX 600000
#define CMAX 1000000000

typedef long long i64;

class BinaryHeap {
 public:
    BinaryHeap() : root(nullptr) {}

    void push(i64 key) {
        root = _merge(root, new Node(key));
    }

    void pop() {
        root = _merge(root->left, root->right);
    }

    void eat(BinaryHeap &b) {
        root = _merge(root, b.root);
    }

    i64 top() {
        return root->key;
    }

    bool empty() {
        return root == nullptr;
    }

 private:
    struct Node {
        Node(i64 _key) : key(_key), rank(0), left(nullptr), right(nullptr) {}

        void update() {
            rank = max(_rank(left) + 1, _rank(right) + 1);
        }

        i64 key;
        int rank;
        Node *left;
        Node *right;
    };  // struct Node

    Node *root;

    static int _rank(Node *x) {
        return x ? x->rank : 0;
    }

    Node *_merge(Node *x, Node *y) {
        if (!x)
            return y;
        if (!y)
            return x;
        if (x->key < y->key)
            swap(x, y);
        if (_rank(x->left) < _rank(x->right))
            swap(x->left, x->right);
        x->right = _merge(x->right, y);
        x->update();
        return x;
    }
};  // class BinaryHeap

class ConvexHull {
 public:
    ConvexHull() : right(1) {
        q.push(0);
        q.push(0);
    }

    void move_y(i64 w) {
        i64 L, R;
        for (int i = 0; i < right; i++) {
            if (i == right - 1)
                R = q.top();
            q.pop();
        }  // for
        L = q.top();
        q.pop();
        q.push(L + w);
        q.push(R + w);
        right = 1;
    }

    friend ConvexHull *merge_hull(ConvexHull *a, ConvexHull *b);
    friend i64 minimize(ConvexHull *h);

 private:
    i64 right;
    BinaryHeap q;
};  // class ConvexHull

ConvexHull *merge_hull(ConvexHull *a, ConvexHull *b) {
    if (!a)
        return b;
    if (!b)
        return a;
    a->right += b->right;
    a->q.eat(b->q);
    return a;
}

static int n;
static vector<int> G[NMAX + 10];
static i64 dist[NMAX + 10];
static ConvexHull *convex[NMAX + 10];
static vector<i64> seq;

i64 minimize(ConvexHull *h) {
    i64 sum = 0;
    for (int i = 2; i <= n; i++) {
        sum += dist[i];
    }  // for

    for (int i = 0; i < h->right; i++) {
        h->q.pop();
    }  // for

    while (!h->q.empty()) {
        seq.push_back(h->q.top());
        h->q.pop();
    }  // while

    i64 lastx = 0;
    for (i64 k = seq.size() - 1; k >= 0; k--) {
        sum -= (k + 1) * (seq[k] - lastx);
        lastx = seq[k];
    }  // for

    return sum;
}

void initialize() {
    int a, b;
    scanf("%d%d", &a, &b);
    n = a + b;

    for (int i = 2; i <= n; i++) {
        int father;
        i64 w;
        scanf("%d%lld", &father, &w);

        G[father].push_back(i);
        dist[i] = w;
    }  // for
}

void dfs(int x) {
    bool has_child = false;
    for (int v : G[x]) {
        has_child = true;
        dfs(v);
        convex[v]->move_y(dist[v]);
        convex[x] = merge_hull(convex[x], convex[v]);
    }  // foreach in G[x]

    if (!has_child)
        convex[x] = new ConvexHull;
}

int main() {
    initialize();
    dfs(1);
    printf("%lld\n", minimize(convex[1]));

    return 0;
}  // function main
