/**
 * 讲道理这个题没法做因为没有说以谁为根
 * O(q log^2 n) memory usage failed.
 * Maybe 1GB memory (even more) is required.
 */

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 100000
#define LOGN 17

struct Node {
    Node(int k) : key(k), count(0), size(0), left(nullptr), right(nullptr) {}

    int key;
    int count;
    int size;
    Node *left;
    Node *right;

    void update() {
        size = count + (left ? left->size : 0) + (right ? right->size : 0);
    }
};  // struct Node

Node *build(int left, int right) {
    if (right < left)
        return nullptr;

    int mid = (left + right) / 2;
    Node *x = new Node(mid);

    if (left < right) {
        x->left = build(left, mid - 1);
        x->right = build(mid + 1, right);
    }

    return x;
}

Node *modify(Node *x, int key, int delta) {
    x = new Node(*x);

    if (key < x->key)
        x->left = modify(x->left, key, delta);
    else if (key > x->key)
        x->right = modify(x->right, key, delta);
    else
        x->count += delta;

    x->update();
    return x;
}

static int n, m;

static vector<int> G[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];

static int type[NMAX + 10];
static int X[NMAX + 10];
static int K[NMAX + 10];

static int cnt;
static int values[NMAX + 10];

static Node *version[NMAX + 10];
static int tail;
static Node *q[LOGN + 10];

inline int hashing(int x) {
    return lower_bound(values, values + cnt, x) - values;
}

void dfs(int x) {
    static bool marked[NMAX + 10];
    marked[x] = true;
    in[x] = ++timestamp;

    for (int v : G[x]) {
        if (!marked[v])
            dfs(v);
    }  // foreach in G[x]

    out[x] = timestamp;
}

void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    dfs(1);

    scanf("%d", &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d", type + i);

        if (type[i] == 1) {
            scanf("%d%d", X + i, K + i);
            values[cnt++] = K[i];
        } else if (type[i] == 2)
            scanf("%d", X + i);
        else
            scanf("%d%d", X + i, K + i);
    }  // for

    sort(values, values + cnt);
    cnt = unique(values, values + cnt) - values;

    for (int i = 1; i <= m; i++) {
        if (type[i] == 1)
            K[i] = hashing(K[i]);
    }  // for

    version[0] = build(0, cnt - 1);
    for (int i = 1; i <= n; i++) {
        version[i] = version[0];
    }  // for
}

void modify(int r, int key, int delta) {
    for (; r; r -= r & (-r)) {
        version[r] = modify(version[r], key, delta);
    }  // for
}

void modify(int left, int right, int key, int delta) {
    modify(right, key, delta);
    modify(left - 1, key, -delta);
}

int query(int k) {
    int left = 0, len = 0;
    for (int i = 0; i < tail; i++) {
        left += q[i]->left ? q[i]->left->size : 0;
        len += q[i]->count;
    }  // for

    if (left < k && k <= left + len)
        return q[0]->key;
    else if (k <= left) {
        for (int i = 0; i < tail; i++) {
            q[i] = q[i]->left;
        }  // for
    } else {
        for (int i = 0; i < tail; i++) {
            q[i] = q[i]->right;
        }  // for

        k -= left + len;
    }

    return query(k);
}

int main() {
    initialize();

    for (int i = 1; i <= m; i++) {
        switch (type[i]) {
            case 1: {
                int u = X[i];
                int w = K[i];
                modify(in[u], out[u], w, 1);
            } break;

            case 2: {
                int u = X[X[i]];
                int w = K[X[i]];
                modify(in[u], out[u], w, -1);
            } break;

            case 3: {
                tail = 0;
                int u = X[i];
                int k = K[i];

                if (k == 0) {
                    puts("-1");
                    break;
                }

                for (int i = in [u]; i <= n; i += i & (-i)) {
                    q[tail++] = version[i];
                }  // for

                printf("%d\n", values[query(k)]);
            } break;
        }  // switch to type[i]
    }      // for

    return 0;
}  // function main
