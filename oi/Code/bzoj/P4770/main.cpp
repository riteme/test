// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>

#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

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
    void reset() {
        root = NULL;
        memset(version, 0, sizeof(version));
    }

    void insert(int key) {
        root = _insert(root, key);
    }

    void remove(int key) {
        root = _remove(root, key);
    }

    int query(int u, int key) {
        return _query(version[u], key);
    }

    void save_work(int u) {
        version[u] = root;
    }

 private:
    struct Node {
        Node(int _k)
            : weight(randint()),
              key(_k), count(1), size(1),
              left(NULL), right(NULL) {}

        int weight;
        int key;
        int count;
        int size;
        Node *left;
        Node *right;

        void update() {
            size = count + (left ? left->size : 0)
                         + (right ? right->size : 0);
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
    };

    Node *root;
    Node *version[NMAX + 10];

    Node *_insert(Node *x, int key) {
        if (!x)
            return new Node(key);

        x = new Node(*x);
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

        x->update()
        return x;
    }

    Node *_remove(Node *x, int key) {
        x = new Node(*x);
        if (key < x->key)
            x->left = _remove(x->left, key);
        else if (key > x->key)
            x->right = _remove(x->right, key);
        else
            x->count--;

        x->update();
        return x;
    }

    int _query(Node *x, int key) {
        if (!x)
            return 0;
        if (key < x->key)
            return _query(x->left, key);
        return _query(x->right, key) + (x->left ? x->left->size : 0)
                                     + x->count;
    }
};

static int n, m;
static int color[NMAX + 10];
static int col[NMAX + 10]; 
static vector<int> G[NMAX + 10];
static int timestamp;
static int depth[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];
static Treap tree;
static int seq[NMAX + 10];
static int qmid[NMAX + 10];
static int qleft[NMAX + 10];
static int qright[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", color + i);
    }

    for (int i = 2; i <= n; i++) {
        int f;
        scanf("%d", &f);
        G[f].push_back(i);
    }

    timestamp = 0;
    depth[1] = 1;
    dfs(1);

    tree.reset();
}

void dfs(int u) {
    in[u] = ++timestamp;
    col[in[u]] = color[u];

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        
        depth[v] = depth[u] + 1;
        dfs(v);
    }

    out[u] = timestamp;
}

bool cmp(const int a, const int b) {
    return in[a] > in[b];
}

void solve(int left, int right, int head, int tail) {
    if (tail < head || right < left)
        return;

    int mid = (left + right) / 2;
    int mcnt = 0, lcnt = 0, rcnt = 0;
    for (int i = head; i <= tail; i++) {
        int u = seq[i];
        if (out[u] < mid)
            qleft[++lcnt] = u;
        else if (in[u] > mid)
            qright[++rcnt] = u;
        else
            qmid[++mcnt] = u;
    }

    int pos = head;
    for (int i = 1; i <= lcnt; i++) {
        seq[pos++] = qleft[i];
    }
    for (int i = 1; i <= rcnt; i++) {
        seq[pos++] = qright[i];
    }

    solve(left, mid - 1, head, head + lcnt - 1);
    solve(mid + 1, right, head + lcnt, head + lcnt + rcnt - 1);

    sort(qmid + 1, qmid + mcnt + 1, cmp);
    map<int, int> lastpos;
    int lastx = mid + 1, lasty = mid;
    for (int i = 1; i <= mcnt; i++) {
        int u = qmid[i];

        while (in[x] < lastx) {
            lastx--;
            
        }
    }
}


int main() {
    int t;
    scanf("%d", &t);

    Solver *solver = new Solver;
    while (t--) {
        solver->initialize();
        solver->main();
    }
    
    return 0;
}
