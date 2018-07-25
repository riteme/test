/**
 * incomplete
 */

#include <cassert>
#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000
#define LOGN 19

static int n, q;
static vector<int> G[NMAX + 10];
static int timestamp;
static int dfn[NMAX + 10];
static int size[NMAX + 10];
static int depth[NMAX + 10];
static int f[LOGN + 1][NMAX + 10];
static int sum[LOGN + 1][NMAX + 10];

inline int evaluate_lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int delta = depth[u] - depthc[v];
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1)
            u = f[i][u];
    }

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (f[i][u] != f[i][v]) {
            u = f[i][u];
            v = f[i][v];
        }
    }

    return f[0][u];
}

inline int evaluate_sum(int u, int delta) {
    int answer = 0;
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1) {
            answer += sum[i][u];
            u = f[i][u];
        }
    }

    return answer;
}

struct Node {
    Node(int _key, int _dist, bool _marked)
        : key(_key), dist(_dist), marked(_marked) {}
    ~Node() {
        for (size_t i = 0; i < children.size(); i++) {
            delete children[i];
        }
    }

    int key;
    int dist;
    bool marked;
    vector<Node *> children;
}

static int m;
static int selected[NMAX + 10];
static bool marked[NMAX + 10];
static int answer[NMAX + 10];
static Node *tree;

static bool cmp(const int a, const int b) {
    return dfn[a] < dfn[b];
}

static Node *build_virtual_tree() {
    stack<Node *> stk;
    sort(selected + 1, selected + m + 1, cmp);

    for (int i = 1; i <= m; i++) {
        int x = selected[i];
        int lca = evaluate_lca(stk.top(), x);
        answer[x] = 0;
        marked[x] = true;
        
        int lastp = 0;
        while (dfn[lca] < dfn[stk.top()]) {
            if (lastp) {

            } else {
                answer
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        marked[selected[i]] = false;
    }
}

static void dfs(int x, int father = 0) {
    dfn[x] = ++timestamp;

    size[x] = 1;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == father)
            continue;

        f[0][v] = x;
        depth[v] = depth[x] + 1;

        dfs(v, x);

        size[x] += size[v];
    }

    sum[0][x] = size[x] - 1;
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

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
            sum[j][i] = sum[j - 1][i] + sum[j - 1][f[j - 1][i]];
        }
    }

    scanf("%d", &q);
}

int main() {
    // freopen("worldtree.in", "r", stdin);
    // freopen("worldtree.out", "w", stdout);
    initialize();

    while (q--) {
        scanf("%d", &m);

        for (int i = 1; i <= m; i++) {
            scanf("%d", selected + i);
        }

        tree = build_virtual_tree();

        delete tree;
    }

    return 0;
}
