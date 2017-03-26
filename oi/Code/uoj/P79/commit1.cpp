#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 500

static int n, m, k;
static vector<int> G[NMAX + 10];

static int s, len;
static int match[NMAX + 10];
static int set[NMAX + 10];
static bool marked[NMAX + 10];
static bool exist[NMAX + 10];
static bool even[NMAX + 10];
static int depth[NMAX + 10];
static int father[NMAX + 10];
static int link[NMAX + 10];
static int seq[NMAX + 10];
static queue<int> q;
static stack<int> path;

inline int id(int x) {
    return set[x] ? set[x] = id(set[x]) : x;
}

inline void union_set(int x, int y) {
    x = id(x);
    y = id(y);

    if (x != y)
        set[x] = y;
}


// inline int evaluate_lca(int u, int v) {
//     u = id(u);
//     v = id(v);
//     if (depth[u] < depth[v])
//         swap(u, v);
// 
//     while (depth[u] > depth[v]) {
//         u = id(father[u]);
//     }
// 
//     while (u != v) {
//         u = id(father[u]);
//         v = id(father[v]);
//     }
// 
//     return u;
// }

inline int evaluate_lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    while (depth[u] > depth[v]) {
        u = father[u];
    }

    while (u != v) {
        u = father[u];
        v = father[v];
    }

    return u;
}

void process(int u, int p) {
    int last = u;
    int x = u;
    while (id(x) != id(p)) {
        if (!link[x])
            link[x] = last;

        union_set(x, p);
        if (!even[id(x)] && !exist[x]) {
            exist[x] = true;
            q.push(x);
        }

        last = x;
        x = father[x];
    }
}

int bfs() {
    marked[s] = even[s] = exist[s] = true;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        exist[u] = false;

        for (int v : G[u]) {
            if (!marked[v]) {
                marked[v] = true;
                father[v] = u;
                // depth[v] = depth[id(u)] + 1;
                depth[v] = depth[u] + 1;

                if (match[v]) {
                    int p = match[v];

#ifndef NDEBUG
                    if (marked[p])
                        printf("v = %d, match[v] = %d, match[p] = %d\n",
                               v, match[v], match[p]);
                    assert(!marked[p]);
#endif

                    marked[p] = even[p] = true;
                    father[p] = v;
                    depth[p] = depth[v] + 1;

                    if (!exist[p]) {
                        exist[p] = true;
                        q.push(p);
                    }
                } else
                    return v;
            } else if (even[id(v)] && id(u) != id(v)) {
                int lca = evaluate_lca(u, v);
                assert(lca);

                if (!link[u])
                    link[u] = v;
                if (!link[v])
                    link[v] = u;

                process(u, lca);
                process(v, lca);
            }
        }
    }

    return 0;
}

void find_path(int u) {
    bool state = false;
    while (u != s) {
        path.push(u);

        if ((state && match[u] == father[u]) ||
            (!state && match[u] != father[u]))
            u = father[u];
        else
            u = link[u];

        state = !state;
    }
}

bool argument(int x) {
    s = x;
    memset(set, 0, sizeof(set));
    memset(marked, 0, sizeof(marked));
    memset(exist, 0, sizeof(exist));
    memset(even, 0, sizeof(even));
    memset(depth, 0, sizeof(depth));
    memset(father, 0, sizeof(father));
    memset(link, 0, sizeof(link));
    q = queue<int>();

    int endpoint = bfs();

    if (!endpoint)
        return false;

    find_path(endpoint);
    len = 1;
    seq[0] = s;
    while (!path.empty()) {
        int u = path.top();
        path.pop();
        seq[len++] = u;
    }

#ifndef NDEBUG
    printf("len = %d\n", len);
    printf("seq    = ");
    for (int i = 0; i < len; i++) {
        printf("%3d ", seq[i]);
    }
    printf("\n");

    printf("match  = ");
    for (int i = 0; i < len; i++) {
        printf("%3d ", match[seq[i]]);
    }
    printf("\n");

    printf("father = ");
    for (int i = 0; i < len; i++) {
        printf("%3d ", father[seq[i]]);
    }
    printf("\n");

    printf("link   = ");
    for (int i = 0; i < len; i++) {
        printf("%3d ", link[seq[i]]);
    }
    printf("\n");

    memset(marked, 0, sizeof(marked));
    for (int i = 0; i < len; i++) {
        assert(!marked[seq[i]]);
        marked[seq[i]] = true;
    }
#endif

    for (int i = 0; i < len; i += 2) {
        match[seq[i]] = seq[i + 1];
        match[seq[i + 1]] = seq[i];
    }

    return true;
}

int blossom_algorithm() {
    int ret = 0;
    for (int u = 1; u <= n; u++) {
        if (!match[u] && argument(u))
            ret++;
    }

    return ret;
}

void initialize() {
    scanf("%d%d", &n, &m);
    // scanf("%d", &k);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // for (int i = 0; i < k; i++) {
    //     int u, v;
    //     scanf("%d%d", &u, &v);
    //     match[u] = v;
    //     match[v] = u;
    // }
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();
    printf("%d\n", blossom_algorithm());
    for (int u = 1; u <= n; u++) {
        printf("%d ", match[u]);
    }
    printf("\n");

    return 0;
}
