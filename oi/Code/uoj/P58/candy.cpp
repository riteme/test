#include <cmath>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 17
#define MMAX 100000

typedef long long int64;

struct Query {
    int u, v;
    int t;
    int64 answer;
};

struct Modify {
    int u, id;
    int prev;
};

static int n, m, q;
static int64 V[MMAX + 10];
static int64 W[NMAX + 10];
static int candy[NMAX + 10];

static int qcnt, mcnt;
static Query que[MMAX + 10];
static Query *ptr[MMAX + 10];
static Modify mod[MMAX + 10];

static int BLOCKSIZE;
static vector<int> G[NMAX + 10];
static int depth[NMAX + 10];
static int f[LOGN + 1][NMAX + 10];
static int blockcnt;
static int id[NMAX + 10];
static int stktail;
static int stk[NMAX + 10];

inline int evaluate_lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int delta = depth[u] - depth[v];
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

static void dfs(int x, int father = 0) {
    int head = stktail;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == father)
            continue;

        f[0][v] = x;
        depth[v] = depth[x] + 1;

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

static bool cmp(const Query *a, const Query *b) {
    return id[a->u] > id[b->u] ||
           (id[a->u] == id[b->u] && id[a->v] > id[b->v]) ||
           (id[a->u] == id[b->u] && id[a->v] == id[b->v] &&
            a->t < b->t);
}

static void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= m; i++) {
        scanf("%lld", V + i);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%lld", W + i);
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", candy + i);
    }

    BLOCKSIZE = max(1, static_cast<int>(pow(n, 2.0 / 3.0)));
    dfs(1);
    blockcnt++;
    while (stktail) {
        id[stk[--stktail]] = blockcnt;
    }

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
        }
    }

    for (int i = 0; i < q; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);

        if (t == 0) {
            mcnt++;
            mod[mcnt].u = x;
            mod[mcnt].id = y;
            mod[mcnt].prev = 0;
        } else {
            if (x > y)
                swap(x, y);

            qcnt++;
            que[qcnt].u = x;
            que[qcnt].v = y;
            que[qcnt].t = mcnt;
            ptr[qcnt] = que + qcnt;
        }
    }

    sort(ptr + 1, ptr + qcnt + 1, cmp);
}

static int64 answer;
static int64 cnt[NMAX + 10];
static bool marked[NMAX + 10];

inline void add_candy(int c) {
    cnt[c]++;
    answer += V[c] * W[cnt[c]];
}

inline void del_candy(int c) {
    answer -= V[c] * W[cnt[c]];
    cnt[c]--;
}

inline void flip_node(int x) {
    if (marked[x])
        del_candy(candy[x]);
    else
        add_candy(candy[x]);

    marked[x] ^= true;
}

inline void change_candy(int x, int c) {
    if (marked[x]) {
        del_candy(candy[x]);
        add_candy(c);
    }

    candy[x] = c;
}

inline void perform(Modify &m) {
    m.prev = candy[m.u];
    change_candy(m.u, m.id);
}

inline void undo(Modify &m) {
    change_candy(m.u, m.prev);
}

inline void flip(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    while (u != v) {
        if (depth[u] > depth[v]) {
            flip_node(u);
            u = f[0][u];
        } else {
            flip_node(v);
            v = f[0][v];
        }
    }
}

int main() {
    initialize();

    int lastu = 1, lastv = 1, lastlca = 1;
    int lastt = 0;
    flip_node(1);
    for (int i = 1; i <= qcnt; i++) {
        Query *current = ptr[i];

        for (int p = lastt + 1; p <= current->t; p++) {
            perform(mod[p]);
        }

        for (int p = lastt; p > current->t; p--) {
            undo(mod[p]);
        }

        int lca = evaluate_lca(current->u, current->v);
        flip(lastu, current->u);
        flip(lastv, current->v);
        flip_node(lastlca);
        flip_node(lca);

        current->answer = answer;
        lastu = current->u;
        lastv = current->v;
        lastlca = lca;
        lastt = current->t;
    }

    for (int i = 1; i <= qcnt; i++) {
        printf("%lld\n", que[i].answer);
    }

    return 0;
}
