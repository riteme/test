#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define INF (1LL << 61)

typedef long long i64;

static int n;
static i64 k;

struct Edge {
    Edge(int _v, i64 _w)
        : v(_v), r(_w), w(_w - k) {}

    int v;
    i64 r, w, a, b;
};

static vector<Edge> G[NMAX + 10];

void initialize() {
    scanf("%d%lld", &n, &k);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        i64 w;
        scanf("%d%d%lld", &u, &v, &w);
        G[u].push_back(Edge(v, w));
        G[v].push_back(Edge(u, w));
    }
}

#define L 0
#define R 1

static int fa[NMAX + 10];
static int ch[NMAX + 10][2];
static i64 w[NMAX + 10], dw[NMAX + 10];
static i64 a[NMAX + 10], da[NMAX + 10];
static i64 b[NMAX + 10], db[NMAX + 10];
static i64 mina[NMAX + 10], minb[NMAX + 10];

inline i64 rmina(int x) {
    return x ? mina[x] + da[x] : INF;
}

inline i64 rminb(int x) {
    return x ? minb[x] + db[x] : INF;
}

void pushdown(int x) {
#define PUSH(src, dst) \
    if (src[x]) { \
        dst[x] += src[x]; \
        src[ch[x][0]] += src[x]; \
        src[ch[x][1]] += src[x]; \
        src[x] = 0; \
    }
#define PUSH2(src, dst, dst2) \
    if (src[x]) { \
        dst[x] += src[x]; \
        dst2[x] += src[x]; \
        src[ch[x][0]] += src[x]; \
        src[ch[x][1]] += src[x]; \
        src[x] = 0; \
    }

    PUSH(dw, w);
    PUSH2(da, a, mina);
    PUSH2(db, b, minb);
}

void update(int x) {
    mina[x] = min(a[x], min(rmina(ch[x][0]), rmina(ch[x][1])));
    minb[x] = min(b[x], min(rminb(ch[x][0]), rminb(ch[x][1])));
}

void rotate(int x, int c) {
    int y = ch[x][c];
    ch[x][c] = ch[y][c ^ 1];
    ch[y][c ^ 1] = x;

    if (ch[x][c])
        fa[ch[x][c]] = x;

    fa[y] = fa[x];
    fa[x] = y;
    if (fa[y]) {
        if (x == ch[fa[y]][L])
            ch[fa[y]][L] = y;
        else
            ch[fa[y]][R] = y;
    }

    mina[y] = mina[x];
    minb[y] = minb[x];
    update(x);
}

void clear(int x) {
    if (fa[x])
        clear(fa[x]);
    pushdown(x);
}

void splay(int x) {
    if (!x) {
        fa[x] = 0;
        return;
    }

    clear(x);
    while (fa[x]) {
        int f = fa[x];
        if (fa[f]) {
            int p = fa[f];
            if (x == ch[f][L] && f == ch[p][L])
                rotate(p, L);
            else if (x == ch[f][R] && f == ch[p][R])
                rotate(p, R);
        }

        if (x == ch[f][L])
            rotate(f, L);
        else
            rotate(f, R);
    }
}

int query(int x, i64 key) {
    splay(x);
    int ret = 0, last = 0;
    while (x) {
        last = x;
        pushdown(x);

        if (w[x] <= key) {
            ret = x;
            x = ch[x][R];
        } else
            x = ch[x][L];
    }

    splay(last);
    return ret;
}

int insert(int x, int y) {
    int t = query(x, w[y]);

    if (t) {
        splay(t);

        if (w[t] == w[y]) {
            a[t] = min(a[t], a[y]);
            b[t] = min(b[t], b[y]);
            update(t);
            return t;
        } else {
            ch[y][R] = ch[t][R];
            ch[y][L] = t;
            ch[t][R] = 0;
            fa[ch[y][R]] = y;
            fa[t] = y;
            update(t);
        }
    } else {
        splay(x);
        ch[y][R] = x;
        fa[x] = y;
    }

    update(y);
    return y;
}

static i64 ans;

void upans(int x, int y) {
    int t = query(x, -w[y]);

    if (t) {
        splay(t);
        ans = min(ans, rminb(ch[t][L]) + b[y]);
        ans = min(ans, rmina(ch[t][R]) + a[y]);

        if (w[t] <= -w[y])
            ans = min(ans, b[t] + b[y]);
        if (w[t] >= -w[y])
            ans = min(ans, a[t] + a[y]);
    } else {
        splay(x);
        ans = min(ans, mina[x] + a[y]);
    }
}

int mergeans(int x, int y) {
    if (!y)
        return x;

    pushdown(y);
    x = mergeans(x, ch[y][L]);
    upans(x, y);
    return mergeans(x, ch[y][R]);
}

int merge(int x, int y) {
    if (!y)
        return x;

    int lc = ch[y][L], rc = ch[y][R];
    ch[y][L] = ch[y][R] = 0;
    fa[lc] = fa[rc] = 0;

    x = merge(x, lc);
    x = insert(x, y);
    return merge(x, rc);
}

static int size[NMAX + 10];

int dfs(int u, int f) {
    int tr = 0, sz = 0;
    size[u] = 1;
    for (auto &e : G[u]) {
        int v = e.v;
        if (v == f)
            continue;

        int vt = dfs(v, u);
        size[u] += size[v];

        dw[vt] += e.w;
        da[vt] += e.a;
        db[vt] += e.b;

        if (sz < size[v])
            swap(tr, vt);

        sz += size[v];
        tr = mergeans(tr, vt);
        tr = merge(tr, vt);
    }

    upans(tr, u);
    return insert(tr, u);
}

i64 solve() {
#define CLS(x) memset(x, 0, sizeof(x));
    CLS(fa) CLS(ch) CLS(w) CLS(a) CLS(b)
    CLS(dw) CLS(da) CLS(db)
    CLS(mina) CLS(minb) CLS(size)
    a[0] = b[0] = mina[0] = minb[0] = ans = INF;
    dfs(1, 0);
    return ans;
}

int main() {
    // freopen("ex_soda1.in", "r", stdin);
    initialize();

    i64 l = 0, r = 1e13;
    while (l < r) {
        i64 m = (l + r) / 2 + 1;

        for (int u = 1; u <= n; u++) {
            for (auto &e : G[u]) {
                e.a = e.r - m - k;
                e.b = k - m - e.r;
            }
        }

        if (solve() < 0)
            r = m - 1;
        else
            l = m;
    }

    printf("%lld\n", l);

    return 0;
}
