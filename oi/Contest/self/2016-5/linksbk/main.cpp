#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

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
    Node() : weight(randint()) {}

    int key;
    int value;
    Node *tree;
    int weight;
    int size;

    Node *left, *right;
};  // struct Node

static unsigned memcnt;
static Node memory[NMAX + 10];

inline void refresh_memory() {
    memcnt = 0;
}

inline Node *allocate(const Node *from = NULL) {
    memcnt++;
    if (!from)
        memory[memcnt] = *from;
    return memory + memcnt;
}

#define SIZE_OF(x) (x ? x->size : 0)

typedef pair<Node *, Node *> NodePair;

inline void update(Node *x) {
    x->size = SIZE_OF(x->left) + SIZE_OF(x->right) + 1;
}

inline Node *left_rotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;

    update(x);
    update(y);

    return y;
}

inline Node *right_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;

    update(x);
    update(y);

    return y;
}

static int rank_key(Node *x, int key) {
    if (!x)
        return 1;
    if (key < x->key)
        return rank_key(x->left, key);
    else
        return rank_key(x->right, key) + SIZE_OF(x->left) + 1;
}

static bool contain(Node *x, int key) {
    if (!x)
        return false;

    if (key < x->key)
        return contain(x->left, key);
    else if (key > x->key)
        return contain(x->right, key);
    else
        return true;
}

static Node *insert(Node *x, int key, int delta) {
    if (!x) {
        x = allocate();
        x->key = key;
        x->value = delta;
        x->size = 1;
        x->left = x->right = NULL;

        return x;
    }

    if (key < x->key) {
        x->left = insert(x->left, key, delta);

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else if (key > x->key) {
        x->right = insert(x->right, key, delta);

        if (x->right->weight < x->weight)
            return right_rotate(x);
    } else
        x->value += delta;

    update(x);
    return x;
}

static Node *insert_tree(Node *x, int key, Node *tree) {
    if (!x) {
        x = allocate();
        x->key = key;
        x->tree = tree;
        x->left = x->right = NULL;

        return x;
    }

    if (key < x->key) {
        x->left = insert(x->left, key, delta);

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else if (key > x->key) {
        x->right = insert(x->right, key, delta);

        if (x->right->weight < x->weight)
            return right_rotate(x);
    } else
        x->tree += tree;

    return x;
}

static NodePair split(Node *x, int k) {
    if (!x)
        return NodePair(NULL, NULL);

    NodePair result;
    if (k <= SIZE_OF(x->left) + 1) {
        result = split(x->left);
        x->left = result.second;
        result.second = x;
    } else {
        result = split(x->right);
        x->right = result.first;
        result.first = x;
    }

    update(x);
    return result;
}

static Node *merge(Node *x, Node *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    if (x->weight < y->weight) {
        x->right = merge(x->right, y);

        update(x);
        return x;
    } else {
        y->left = merge(x, y->left);

        update(y);
        return y;
    }
}

static Node *persistent_merge(Node *x, Node *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    if (x->weight < y->weight) {
        x = allocate(y);
        x->right = merge(x->right, y);

        update(x);
        return x;
    } else {
        y = allocate(x);
        y->left = merge(x, y->left);

        update(y);
        return y;
    }
}

enum CommandType { COMM_MODIFY = 1, COMM_QUERY = 2 };  // enum CommandType

struct Command {
    CommandType type;
    int x, v;
    int id;
};  // struct Command

static int n, q;
static int vector<int> G[NMAX + 10];
static int color[NMAX + 10];
static int ansid;
static int answer[NMAX + 10];
static Command ops[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static bool marked[NMAX + 10];

static void dfs(int x) {
    marked[x] = true;
    in[x] = ++timestamp;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            dfs(v);
        }
    }

    out[x] = timestamp;
}

static int querycnt;
static Command *query[NMAX + 10];
static vector<Command *> mod[NMAX + 10];
static Command *queue[NMAX + 10];
static Command *q1[NMAX + 10], *q2[NMAX + 10];
static void solve(int head, int tail, int left, int right) {
    if (tail > head)
        return;

    int mid = (left + right) / 2;
    int cnt = 0, c1 = 0, c2 = 0;
    for (int i = head; i <= tail; i++) {
        if (in[query[i]->x] <= mid && mid <= out[query[i]->x])
            queue[++cnt] = query[i];
        else if (out[query[i]->x] < mid)
            q1[++c1] = query[i];
        else
            q2[++c2] = query[i];
    }

    refresh_memory();
    int left = mid, right = mid;
    Node *version;

    version = insert_tree(version, 0, NULL);
    for (int i = 1; i <= cnt; i++) {
        int l = in[queue[i]->x], r = out[queue[i]->x];

        for (int j = l; j < left; j++) {
        }

        for (int j = right + 1; j <= r; j++) {
        }
    }
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", color + i);
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int command;
        scanf("%d", &command);

        if (command == 0) {
            int x, v;
            scanf("%d%d", &x, &v);

            ops[i].type = COMM_MODIFY;
            ops[i].x = x;
            ops[i].v = v;
            mod[x].push_back(ops + i);
        } else {
            int x;
            scanf("%d", &x);

            ops[i].type = COMM_QUERY;
            ops[i].x = x;
            ops[i].id = ansid++;
            query[++querycnt] = ops + i;
        }
    }

    dfs(1);
}

int main() {
    initialize();

    solve(1, q, 1, n);

    for (int i = 0; i < ansid; i++) {
        printf("%d\n", answer[i]);
    }

    return 0;
}  // function main
