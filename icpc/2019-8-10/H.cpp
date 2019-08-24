#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2500
#define QMAX 5000
#define TMAX 42
#define SIGMA 26
#define MOD 998244353

typedef long long i64;

struct Node {
    Node() : mark(false), id(0), fail(NULL) {
        memset(ch, 0, sizeof(ch));
    }

    bool mark;
    int id;
    Node *fail;
    Node *ch[SIGMA];
};

inline void narrow(char *s, int &len) {
    for (len = 0; s[len]; len++) s[len] -= 'a';
}

inline void insert(Node *x, const char *s, int len) {
    for (int i = 0; i < len; i++) {
        if (!x->ch[s[i]]) x->ch[s[i]] = new Node;
        x = x->ch[s[i]];
    }
    x->mark = true;
}

inline void setup_fail(Node *x) {
    queue<Node*> q;
    for (char c = 0; c < SIGMA; c++) if (x->ch[c]) {
        x->ch[c]->fail = x;
        q.push(x->ch[c]);
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (char c = 0; c < SIGMA; c++) if (u->ch[c]) {
            auto y = u->ch[c], z = u->fail;
            while (z != x && !z->ch[c]) z = z->fail;
            if (z->ch[c]) z = z->ch[c];
            y->fail = z;
            y->mark |= z->mark;
            q.push(y);
        }
    }
}

inline void add(i64 &a, i64 b) {
    static constexpr i64 MAGIC = 8226880248558387098;
    a += b;
    if (a >= MAGIC) a -= MAGIC;
}

static int cnt;
struct Matrix {
    Matrix() {
        memset(m, 0, sizeof(m));
    }

    void set_identity() {
        for (int i = 0; i <= cnt; i++) m[i][i] = 1;
    }

    void mul(i64 *vec) const {
        i64 tmp[TMAX];
        memset(tmp, 0, sizeof(tmp));
        for (int i = 0; i <= cnt; i++) {
            int j = 0;
            for ( ; j + 7 <= cnt; j += 8) {
                tmp[i] += m[i][j] * vec[j];
                tmp[i] += m[i][j + 1] * vec[j + 1];
                tmp[i] += m[i][j + 2] * vec[j + 2];
                tmp[i] += m[i][j + 3] * vec[j + 3];
                tmp[i] += m[i][j + 4] * vec[j + 4];
                tmp[i] += m[i][j + 5] * vec[j + 5];
                tmp[i] += m[i][j + 6] * vec[j + 6];
                tmp[i] += m[i][j + 7] * vec[j + 7];
                tmp[i] %= MOD;
            }
            for ( ; j <= cnt; j++)
                tmp[i] += m[i][j] * vec[j];
            tmp[i] %= MOD;
        }
        memcpy(vec, tmp, sizeof(tmp));
    }

    i64 m[TMAX][TMAX];

    auto operator*(const Matrix &z) const {
        Matrix r;
        for (int i = 0; i <= cnt; i++)
        for (int k = 0; k <= cnt; k++)
        for (int j = 0; j <= cnt; j++)
            add(r.m[i][j], m[i][k] * z.m[k][j]);
        for (int i = 0; i <= cnt; i++)
        for (int j = 0; j <= cnt; j++)
            r.m[i][j] %= MOD;
        return r;
    }

    i64 &operator()(int i, int j) {
        return m[i][j];
    }

    __attribute__((used)) void print() const {
        puts("Matrix(");
        for (int i = 0; i <= cnt; i++) {
            putchar(i ? ' ' : '[');
            putchar('[');
            for (int j = 0; j <= cnt; j++)
                printf(j == cnt ? "%2lld]" : "%2lld, ", m[i][j]);
            puts(i < cnt ? "," : "]");
        }
        puts(")");
    }
};

static int trans[TMAX][SIGMA];

inline auto advance(Node *x, char c) {
    while (x->fail && !x->ch[c]) x = x->fail;
    if (x->ch[c]) x = x->ch[c];
    return x;
}

inline void setup_trans(Node *x) {
    queue<Node*> q;
    q.push(x);
    x->id = ++cnt;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (u->mark) continue;
        for (char c = 0; c < SIGMA; c++) {
            auto v = advance(u, c);
            if (!v->mark && !v->id) v->id = ++cnt;
            trans[u->id][c] = v->id;
        }
        for (char c = 0; c < SIGMA; c++) {
            auto v = u->ch[c];
            if (v && !v->mark) q.push(v);
        }
    }
}

struct Edge {
    int u, v, size;
    char s[SIGMA + 1];
    Matrix T;

    int nxt(int x) const {
        return u == x ? v : u;
    }
};

inline void setup_edge(Edge *e) {
    for (int s = 0; s <= cnt; s++) for (int i = 0; i < e->size; i++)
        e->T(trans[s][e->s[i]], s)++;
}

static int n, m, q;
static vector<Edge*> G[NMAX + 10];
static Edge *E[NMAX + 10];
static int size[NMAX + 10], fa[NMAX + 10];
static int dfn[NMAX + 10], top[NMAX + 10], rev[NMAX + 10], cur;
static Matrix up[NMAX + 10], dw[NMAX + 10];

struct Segment {
    Segment(int _l, int _r) : l(_l), r(_r), lch(NULL), rch(NULL) {}

    int l, r;
    Matrix Mlr, Mrl;
    Segment *lch, *rch;
};
static Segment *tr;

auto build(int l, int r) -> Segment* {
    auto x = new Segment(l, r);
    if (l < r) {
        int m = (l + r) >> 1;
        x->lch = build(l, m);
        x->rch = build(m + 1, r);
        x->Mlr = x->lch->Mlr * x->rch->Mlr;
        x->Mrl = x->rch->Mrl * x->lch->Mrl;
    } else x->Mrl = x->Mlr = E[rev[l]]->T;
    return x;
}

void querylr(Segment *x, int l, int r, i64 *vec) {
    if (l <= x->l && x->r <= r) x->Mlr.mul(vec);
    else {
        int m = (x->l + x->r) >> 1;
        if (r > m) querylr(x->rch, l, r, vec);
        if (l <= m) querylr(x->lch, l, r, vec);
    }
}

void queryrl(Segment *x, int l, int r, i64 *vec) {
    if (l <= x->l && x->r <= r) x->Mrl.mul(vec);
    else {
        int m = (x->l + x->r) >> 1;
        if (l <= m) queryrl(x->lch, l, r, vec);
        if (r > m) queryrl(x->rch, l, r, vec);
    }
}

void dfs(int x) {
    size[x] = 1;
    for (auto e : G[x]) {
        int v = e->nxt(x);
        if (v == fa[x]) continue;
        fa[v] = x;
        E[v] = e;
        dfs(v);
        size[x] += size[v];
    }
}

void decompose(int x) {
    dfn[x] = ++cur;
    rev[cur] = x;
    int u = 0;
    for (auto e : G[x]) {
        int v = e->nxt(x);
        if (v != fa[x] && size[v] > size[u]) u = v;
    }
    if (u) {
        top[u] = top[x];
        up[u] = up[x] * E[u]->T;
        dw[u] = E[u]->T * dw[x];
        decompose(u);
    }
    for (auto e : G[x]) {
        int v = e->nxt(x);
        if (v == fa[x] || v == u) continue;
        top[v] = v;
        up[v].set_identity();
        dw[v].set_identity();
        decompose(v);
    }
}

inline void initialize() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i < n; i++) {
        Edge *e = new Edge;
        scanf("%d%d%s", &e->u, &e->v, e->s);
        narrow(e->s, e->size);
        G[e->u].push_back(e);
        G[e->v].push_back(e);
    }
    auto trie = new Node;
    for (int i = 0; i < m; i++) {
        char buf[128];
        scanf("%s", buf);
        int len;
        narrow(buf, len);
        insert(trie, buf, len);
    }
    setup_fail(trie);
    setup_trans(trie);
    for (int u = 1; u <= n; u++) for (auto e : G[u])
        if (u == e->u) setup_edge(e);
    dfs(1);
    top[1] = 1;
    up[1].set_identity();
    dw[1].set_identity();
    decompose(1);
    tr = build(2, n);
}

static i64 vec[TMAX];
static int stk[NMAX + 10], tail;

int main() {
    initialize();
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        memset(vec, 0, sizeof(vec));
        vec[1] = 1;
        while (top[u] != top[v]) {
            if (dfn[u] > dfn[v]) {
                up[u].mul(vec);
                E[top[u]]->T.mul(vec);
                u = fa[top[u]];
            } else {
                stk[tail++] = v;
                v = fa[top[v]];
            }
        }
        if (dfn[u] > dfn[v]) querylr(tr, dfn[v] + 1, dfn[u], vec);
        else if (dfn[u] < dfn[v]) queryrl(tr, dfn[u] + 1, dfn[v], vec);
        while (tail) {
            v = stk[--tail];
            E[top[v]]->T.mul(vec);
            dw[v].mul(vec);
        }
        printf("%lld\n", vec[0]);
    }
    return 0;
}
