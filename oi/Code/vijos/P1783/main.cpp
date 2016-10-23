#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define LOGN 16

typedef long long int64;

struct Node {
    Node() : value(0), mark(0), leftchild(NULL), rightchild(NULL) {}

    int left, right;
    int value;
    int mark;

    Node *leftchild, *rightchild;
};  // struct Node

#define MEMORYMAX 2000000

static size_t _pos = 0;
static Node memory[MEMORYMAX];

inline Node *allocate() {
    return &memory[_pos++];
}

inline void pushdown(Node *x) {
    if (x->mark) {
        x->value += x->mark;

        if (x->leftchild) {
            x->leftchild->mark += x->mark;
            x->rightchild->mark += x->mark;
        }

        x->mark = 0;
    }
}

inline int value_of(Node *x) {
    return x->value + x->mark;
}

inline void update(Node *x) {
    if (x->leftchild) {
        x->value = min(value_of(x->leftchild), value_of(x->rightchild));
    }
}

static Node *build_segment_tree(int left, int right) {
    Node *x = allocate();
    x->left = left;
    x->right = right;

    if (left == right)
        return x;

    int mid = (left + right) / 2;
    x->leftchild = build_segment_tree(left, mid);
    x->rightchild = build_segment_tree(mid + 1, right);

    return x;
}

static void clean(Node *x) {
    if (!x)
        return;

    x->value = x->mark = 0;
    clean(x->leftchild);
    clean(x->rightchild);
}

static void modify(Node *x, int left, int right, int value) {
    if (left <= x->left && x->right <= right)
        x->mark += value;
    else {
        pushdown(x);

        int mid = (x->left + x->right) >> 1;

        if (right <= mid)
            modify(x->leftchild, left, right, value);
        else if (left > mid)
            modify(x->rightchild, left, right, value);
        else {
            modify(x->leftchild, left, right, value);
            modify(x->rightchild, left, right, value);
        }

        update(x);
    }
}

static int query(Node *x, int left, int right) {
    if (left <= x->left && x->right <= right)
        return value_of(x);

    pushdown(x);
    int mid = (x->left + x->right) >> 1;

    if (right <= mid)
        return query(x->leftchild, left, right);
    else if (left > mid)
        return query(x->rightchild, left, right);
    else
        return min(query(x->leftchild, left, right),
                   query(x->rightchild, left, right));
}

struct Edge {
    Edge(int _u, int _v, int64 _w) : u(_u), v(_v), w(_w) {}

    int u, v;
    int64 w;

    int either(int x) const {
        return x == u ? v : u;
    }
};  // struct Edge

static int n, m;
static vector<Edge *> G[NMAX + 10];
static int army[NMAX + 10];

static bool marked[NMAX + 10];

static int father[NMAX + 10];
static int64 length[NMAX + 10];
static int64 dist[NMAX + 10];
static bool leaf[NMAX + 10];
static vector<int> children[NMAX + 10];

static void build(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (marked[v])
            continue;

        father[v] = x;
        length[v] = e->w;
        dist[v] = dist[x] + e->w;
        children[x].push_back(v);

        build(v);
    }  // for

    if (children[x].empty())
        leaf[x] = true;
}

static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static Node *tree;

static void dfs(int x) {
    if (leaf[x]) {
        in[x] = out[x] = ++timestamp;
    } else {
        in[x] = INT_MAX;

        for (size_t i = 0; i < children[x].size(); i++) {
            dfs(children[x][i]);
            in[x] = min(in[x], in[children[x][i]]);
        }  // for

        out[x] = timestamp;
    }
}

static int f[NMAX + 10][LOGN + 1];
static int64 sum[NMAX + 10][LOGN + 1];
static int num_target;
static int target[NMAX + 10];
static int num_source;
static int source[NMAX + 10];
static int from[NMAX + 10];
static bool wait[NMAX + 10];

inline int jump(int x, int64 maxdist) {
    for (int i = LOGN; i >= 0; i--) {
        if (f[x][i] && sum[x][i] <= maxdist) {
            maxdist -= sum[x][i];
            x = f[x][i];
        }
    }  // for

    return x;
}

static bool cmp_target(const int &a, const int &b) {
    return length[a] < length[b];
}

static bool cmp_source(const int &a, const int &b) {
    return dist[a] > dist[b];
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        int64 w;
        scanf("%d%d%lld", &u, &v, &w);

        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }  // for

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        army[x]++;
    }  // for

    build(1);
    dfs(1);
    tree = build_segment_tree(1, timestamp);

    for (int i = 1; i <= n; i++) {
        f[i][0] = father[i];
        sum[i][0] = length[i];
    }  // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
            sum[i][j] = sum[i][j - 1] + sum[f[i][j - 1]][j - 1];
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        if (army[i])
            source[++num_source] = i;
    }  // for

    num_target = children[1].size();
    for (size_t i = 0; i < children[1].size(); i++) {
        target[i + 1] = children[1][i];
    }  // for

    sort(target + 1, target + num_target + 1, cmp_target);
    sort(source + 1, source + num_source + 1, cmp_source);

    for (int i = 1; i <= num_source; i++) {
        from[i] = jump(source[i], dist[source[i]] - 1);
    }  // for
}

static bool test(int64 w) {
    clean(tree);
    memset(wait, 0, sizeof(wait));

    for (int i = 1; i <= num_source; i++) {
        int u = source[i];

        if (w >= dist[u]) {
            wait[i] = true;
        } else {
            int v = jump(u, w);

            modify(tree, in[v], out[v], 1);
        }
    }  // for

    if (query(tree, 1, timestamp) > 0)
        return true;

    int i = 1, j = 1;
    int cnt = 0;
    while (i <= num_target && j <= num_source) {
        while (i <= num_target &&
               query(tree, in[target[i]], out[target[i]]) > 0)
            i++;

        while (j <= num_source && !wait[j])
            j++;

        if (i > num_target || j > num_source)
            break;

        if (query(tree, in[from[j]], out[from[j]]) == 0)
            modify(tree, in[from[j]], out[from[j]], 1);
        else if (w - dist[source[j]] >= length[target[i]]) {
            modify(tree, in[target[i]], out[target[i]], 1);
            i++;
        }

        cnt++;
        if (cnt >= army[source[j]]) {
            j++;
            cnt = 0;
        }
    }

    return query(tree, 1, timestamp) > 0;
}

int main() {
    initialize();

    int64 lensum = 0;
    for (int i = 1; i <= n; i++) {
        lensum += length[i];
    }  // for

    int64 left = 0, right = lensum + 1;
    while (left + 1 < right) {
        int64 mid = (left + right) / 2;

        if (test(mid))
            right = mid;
        else
            left = mid;
    }  // while

    if (left != right && !test(left))
        left = right;

    if (left > lensum)
        puts("-1");
    else
        printf("%lld\n", left);

    return 0;
}  // function main
