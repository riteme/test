#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, m, q, cnt;
static int w[NMAX + 10];
static vector<int> G[NMAX + 10], T[NMAX + 10];

void bcc(int u, int f = 0) {
    struct Edge {
        int u, v;
    };
    static stack<Edge> stk;
    static bool marked[NMAX + 10];
    static int in[NMAX + 10], low[NMAX + 10], cur;
    in[u] = low[u] = ++cur;
    for (int v : G[u]) {
        if (v == f) f = 0;
        else if (in[v]) low[u] = min(low[u], in[v]);
        else {
            stk.push({u, v});
            bcc(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > in[u]) {
                T[u].push_back(v);
                T[v].push_back(u);
                stk.pop();
            } else if (low[v] >= in[u]) {
                cnt++;
                int linked = 0, p = n + cnt;
                auto add = [p, &linked](int x) {
                    if (!marked[x]) {
                        marked[x] = true;
                        T[p].push_back(x);
                        T[x].push_back(p);
                        linked++;
                }};
                while (!stk.empty()) {
                    auto x = stk.top();
                    stk.pop();
                    add(x.u);
                    add(x.v);
                    if (x.u == u && x.v == v)
                        break;
                }
                for (int v : T[p])
                    marked[v] = false;
                if (linked == 0)
                    cnt--;
            }
        }
    }
}

static int fa[NMAX + 10], dep[NMAX + 10];
static int top[NMAX + 10];
static int id[NMAX + 10], rev[NMAX + 10];

void dfs(int x, int f) {
    top[x] = 1;
    for (int v : T[x]) if (v != f) {
        fa[v] = x;
        dep[v] = dep[x] + 1;
        dfs(v, x);
        top[x] += top[v];
    }
}

void decompose(int x, int f) {
    static int cur;
    id[x] = ++cur;
    rev[id[x]] = x;
    int u = 0;
    for (int v : T[x])
        if (v != f && top[v] > top[u]) u = v;
    if (u) {
        top[u] = top[x];
        decompose(u, x);
    }
    for (int v : T[x]) if (v != f && v != u) {
        top[v] = v;
        decompose(v, x);
    }
}

struct Segment {
    Segment(int _l, int _r) :
        l(_l), r(_r),
        lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Segment(l, m);
            rch = new Segment(m + 1, r);
            update();
        } else w = ::w[rev[l]];
    }

    int l, r, w;
    Segment *lch, *rch;

    void update() {
        w = min(lch->w, rch->w);
    }

    void modify(int x, int v) {
        if (l == r) w = v;
        else {
            int m = (l + r) / 2;
            if (x <= m)
                lch->modify(x, v);
            else
                rch->modify(x, v);
            update();
        }
    }

    int query(int L, int R) {
        if (L <= l && r <= R)
            return w;
        int m = (l + r) / 2;
        int ret = INT_MAX;
        if (L <= m)
            ret = min(ret, lch->query(L, R));
        if (R > m)
            ret = min(ret, rch->query(L, R));
        return ret;
    }
};

static multiset<int> S[NMAX + 10];
static Segment *tr;

void initialize() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bcc(1);
    dfs(1, 0);
    top[1] = 1;
    decompose(1, 0);

    for (int u = n + 1; u <= n + cnt; u++) {
        for (int v : T[u]) if (v != fa[u])
            S[u].insert(w[v]);
        w[u] = *S[u].begin();
    }
    tr = new Segment(1, n + cnt);
}

void rm(multiset<int> &s, int v) {
    auto it = s.find(v);
    s.erase(it);
}

void modify(int u, int v) {
    int p = fa[u];
    if (p > n) rm(S[p], w[u]);
    w[u] = v;
    tr->modify(id[u], v);
    if (p > n) {
        S[p].insert(v);
        tr->modify(id[p], *S[p].begin());
    }
}

int query(int u, int v) {
    int ret = INT_MAX;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret = min(ret, tr->query(id[top[u]], id[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    ret = min(ret, tr->query(id[u], id[v]));
    if (u > n && fa[u])
        ret = min(ret, w[fa[u]]);
    return ret;
}

int main() {
    initialize();

    while (q--) {
        char op[16];
        int u, v;
        scanf("%s%d%d", op, &u, &v);
        if (op[0] == 'C')
            modify(u, v);
        else
            printf("%d\n", query(u, v));
    }

    return 0;
}
