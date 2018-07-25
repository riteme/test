/**
 * 平衡树启发式合并
 * 为每个叶节点建立一棵平衡树
 * 每次合并答案时，选取大小最大的为自己的平衡树，同时合并其它的平衡树
 * 合并前先更新答案，查询第k大的做法
 * 最后将自己查询并插入即可
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define SEED 233
struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
};  // struct MyRandom

static MyRandom randint;

#define NMAX 10000

static int weight[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];
static int value[NMAX + 10];
static int size[NMAX + 10];
static int mark[NMAX + 10];
static int tree[NMAX + 10];

static void initialize_splay() {
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(value, 0, sizeof(value));
    memset(mark, 0, sizeof(mark));

    for (unsigned i = 1; i <= NMAX; i++) {
        size[i] = 1;
        tree[i] = i;
    }  // for
    size[0] = 0;
    tree[0] = 0;
}

inline void update(int x) {
    size[x] = size[left[x]] + size[right[x]] + 1;
}

inline void pushdown(int x) {
    if (mark[x] != 0) {
        value[x] += mark[x];
        mark[left[x]] += mark[x];
        mark[right[x]] += mark[x];
        mark[x] = 0;
    }
}

inline int left_rotate(int x) {
    assert(left[x]);

    int y = left[x];
    left[x] = right[y];
    right[y] = x;

    update(x);
    update(y);
    return y;
}

inline int right_rotate(int x) {
    assert(right[x]);

    int y = right[x];
    right[x] = left[y];
    left[y] = x;

    update(x);
    update(y);
    return y;
}

static int insert(int x, int y) {
    if (!x) {
        return y;
    }

    pushdown(x);
    if (value[y] < value[x]) {
        left[x] = insert(left[x], y);

        if (weight[left[x]] < weight[x]) {
            x = left_rotate(x);
        }
    } else {
        right[x] = insert(right[x], y);

        if (weight[right[x]] < weight[x]) {
            x = right_rotate(x);
        }
    }

    update(x);
    return x;
}

static int query(int x, int v) {
    if (!x) {
        return 0;
    }

    pushdown(x);
    if (v < value[x]) {
        return query(left[x], v);
    } else {
        return size[left[x]] + 1 + query(right[x], v);
    }
}

struct Edge {
    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int edgecnt;
static Edge memory[NMAX + 10];
inline Edge *allocate() {
    return memory + (edgecnt++);
}

inline void refresh_memory() {
    edgecnt = 0;
}

static int n, k;
static vector<Edge *> G[NMAX + 10];
static vector<int> children[NMAX + 10];
static bool marked[NMAX + 10];

inline void add_edge(int u, int v, int w) {
    Edge *e = allocate();

    e->u = u;
    e->v = v;
    e->w = w;

    G[u].push_back(e);
    G[v].push_back(e);
}

static void clear_graph() {
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        children[i].clear();
    }  // for
}

static void initialize() {
    refresh_memory();
    clear_graph();
    initialize_splay();
    memset(marked, false, sizeof(marked));

    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        add_edge(u, v, c);
    }  // for
}

static int process(int x, int y) {
    if (!y) {
        return 0;
    }

    pushdown(y);
    if (k >= value[y]) {
        return query(x, k - value[y]) + process(x, left[y]) +
               process(x, right[y]);
    } else {
        return process(x, left[y]) + process(x, right[y]);
    }
}

static int merge(int x, int y) {
    if (!y) {
        return x;
    }

    pushdown(y);
    int lc = left[y], rc = right[y];
    left[y] = right[y] = 0;
    size[y] = 1;
    x = insert(x, y);

    x = merge(x, lc);
    x = merge(x, rc);

    return x;
}

static int dfs(int x) {
    marked[x] = true;

    int mx = 0;
    int answer = 0;
    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (not marked[v]) {
            answer += dfs(v);
            children[x].push_back(v);
            mark[tree[v]] += e->w;

            if (size[tree[v]] > size[tree[mx]]) {
                mx = v;
            }
        }
    }  // for

    tree[x] = tree[mx];

    for (unsigned i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        if (v != mx) {
            answer += process(tree[x], tree[v]);
            tree[x] = merge(tree[x], tree[v]);
        }
    }  // for

    answer += query(tree[x], k);
    tree[x] = insert(tree[x], x);

    return answer;
}

int main() {
    weight[0] = INT_MAX;
    for (unsigned i = 1; i <= NMAX; i++) {
        weight[i] = randint();
    }  // for

    while (scanf("%d%d", &n, &k)) {
        if (n == 0 && k == 0) {
            break;
        }

        initialize();
        printf("%d\n", dfs(1));
    }  // while

    return 0;
}  // function main
