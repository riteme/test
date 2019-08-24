#include <cmath>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define LOGN 16
#define MMAX 100000

struct Query {
    int u, v;
    int a, b;
    int answer;
};

static int BLOCKSIZE;
static int n, m;
static int color[NMAX + 10];
static vector<int> G[NMAX + 10];
static int blockcnt, timestamp;
static int stktail;
static int stk[NMAX + 10];
static int id[NMAX + 10];
static int dfn[NMAX + 10];
static int depth[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];
static Query que[MMAX + 10];
static Query *ref[MMAX + 10];

static bool cmp(const Query *a, const Query *b) {
    return  id[a->u] <  id[b->u] ||
           (id[a->u] == id[b->u] && dfn[a->v] < dfn[b->v]);
}

inline int evaluate_lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int delta = depth[u] - depth[v];
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1)
            u = f[u][i];
    }

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }

    return f[u][0];
}

static void dfs(int x, int fa) {
    int head = stktail;
    dfn[x] = ++timestamp;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == fa)
            continue;

        depth[v] = depth[x] + 1;
        f[v][0] = x;

        dfs(v, x);

        if (stktail - head >= BLOCKSIZE) {
            blockcnt++;

            while (stktail > head) {
                id[stk[--stktail]] = blockcnt;
            }
        }
    }

    stk[stktail++] = x;
}

static void initialize() {
    scanf("%d%d", &n, &m);
    BLOCKSIZE = max(1, static_cast<int>(sqrt(n)));

    for (int i = 1; i <= n; i++) {
        scanf("%d", color + i);
    }

    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u != 0 && v != 0) {
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }

    dfs(1, 0);

    blockcnt++;
    while (stktail) {
        id[stk[--stktail]] = blockcnt;
    }

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &que[i].u, &que[i].v, &que[i].a, &que[i].b);
        ref[i] = que + i;

        if (que[i].u > que[i].v)
            swap(que[i].u, que[i].v);
    }

    sort(ref + 1, ref + m + 1, cmp);
}

static int answer;
static int cnt[NMAX + 10];
static bool marked[NMAX + 10];

inline void add_color(int c) {
    cnt[c]++;

    if (cnt[c] == 1)
        answer++;
}

inline void del_color(int c) {
    cnt[c]--;

    if (cnt[c] == 0)
        answer--;
}

inline void flip(int x) {
    if (marked[x]) 
        del_color(color[x]);
    else
        add_color(color[x]);

    marked[x] ^= true;
}

inline void flip(int u, int v) {
    int lca = evaluate_lca(u, v);

    for (; u != lca; u = f[u][0]) {
        flip(u);
    }

    for (; v != lca; v = f[v][0]) {
        flip(v);
    }
}

int main() {
    freopen("apple.in", "r", stdin);
    freopen("apple.out", "w", stdout);
    initialize();

    int lastu = 1, lastv = 1, lastlca = 1;
    flip(1);
    for (int i = 1; i <= m; i++) {
        Query *current = ref[i];
        int lca = evaluate_lca(current->u, current->v);

        flip(lastu, current->u);
        flip(lastv, current->v);
        flip(lastlca);
        flip(lca);

        int ans = answer;
        if (current->a != 0 && current->b != 0 &&
            cnt[current->a] && cnt[current->b])
            ans--;

        current->answer = ans;
        lastu = current->u;
        lastv = current->v;
        lastlca = lca;
    }

    for (int i = 1; i <= m; i++) {
        printf("%d\n", que[i].answer);
    }

    return 0;
}
