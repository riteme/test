#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000
#define SIGMA 26
#define mxv (3 * NMAX)
#define mxc SIGMA

typedef pair<int, int> pii;

static struct SAM {
    SAM() { clear(); }
    int e[mxv][mxc], f[mxv], len[mxv], sz;
    int NEW(int tlen) {
        ++sz, f[sz] = 0, len[sz] = tlen;
        memset(e[sz], 0, sizeof e[sz]);
        return sz;
    }
    void clear() {
        sz = -1;
        NEW(-1);
        NEW(0);
        fill(e[0], e[0] + mxc, 1);
    }
    int add(int x, char c) {
        int y = e[x][c] ? 0 : NEW(len[x] + 1);
        while (x && !e[x][c]) e[x][c] = y, x = f[x];
        if (!x) f[y] = 1;
        else {
            int a = e[x][c];
            if (len[x] + 1 == len[a]) f[y] = a;
            else {
                int b = NEW(len[x] + 1);
                copy(e[a], e[a] + mxc, e[b]);
                f[b] = f[a], f[a] = f[y] = b;
                while (x && e[x][c] == a) e[x][c] = b, x = f[x];
        }}
        return y ? y : f[y];
    }
    pii to(int x, int l, char c) {
        while (!e[x][c]) l = len[x = f[x]];
        return {e[x][c], l + 1};
    }
} sam;

static int n, q;
static char ch[NMAX + 10];
static vector<int> G[NMAX + 10];
static int dep[NMAX + 10];
static int rev[NMAX + 10];
static int ans[NMAX + 10];

struct Query {
    int *ans;
    int L;
};

static vector<int> T[mxv];
static int sum[mxv];
static vector<int> ri[mxv];
static vector<Query> op[mxv];

struct Trie {
    int rev;
    Trie *ch[SIGMA];
};

Trie *meld(Trie *x, Trie *y) {
    if (!x) return y;
    if (!y) return x;
    for (int c = 0; c < SIGMA; c++)
        x->ch[c] = meld(x->ch[c], y->ch[c]);
    return x;
}

Trie *build_trie(int x) {
    Trie *buc[SIGMA];
    memset(buc, 0, sizeof(buc));
    for (int v : G[x]) {
        Trie *tr = build_trie(v);
        buc[ch[v]] = meld(buc[ch[v]], tr);
    }
    Trie *u = new Trie;
    memcpy(u->ch, buc, sizeof(buc));
    return u;
}

void build_sam(Trie *_u) {
    struct State {
        int x;
        Trie *u;
    };
    queue<State> Q;
    Q.push({1, _u});
    while (!Q.empty()) {
        auto p = Q.front();
        Q.pop();
        p.u->rev = p.x;
        for (int c = 0; c < SIGMA; c++) if (p.u->ch[c]) {
            int nx = sam.add(p.x, c);
            Q.push({nx, p.u->ch[c]});
        }
    }
}

void relabel(int x, Trie *u) {
    rev[x] = u->rev;
    ri[rev[x]].push_back(dep[x]);
    for (int v : G[x]) {
        dep[v] = dep[x] + 1;
        relabel(v, u->ch[ch[v]]);
    }
}

void initialize() {
    scanf("%d%d%s", &n, &q, ch + 1);
    for (int i = 1; i <= n; i++) ch[i] -= 'A';
    for (int v = 2; v <= n; v++) {
        int u;
        scanf("%d", &u);
        G[u].push_back(v);
    }
    G[0].push_back(1);
    Trie *tr = build_trie(0);
    build_sam(tr);
    relabel(0, tr);
    for (int i = 1; i <= q; i++) {
        int x, L;
        scanf("%d%d", &x, &L);
        op[rev[x]].push_back({ans + i, L});
    }
    for (int v = 1; v <= sam.sz; v++)
        T[sam.f[v]].push_back(v);
}

static int stk[mxv], t;

void sumup(int x) {
    for (int v : T[x]) {
        sumup(v);
        sum[x] += ri[v].size() + sum[v];
    }
}

void dfs(int x) {
    stk[t++] = x;
    for (int v : T[x])
        dfs(v);

    sort(ri[x].begin(), ri[x].end());
    for (auto &e : op[x]) {
        int l = 0, r = t - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (sam.len[stk[m]] >= e.L) r = m;
            else l = m + 1;
        }
        int p = stk[l];
        *e.ans = sum[p] + (ri[p].end() - lower_bound(ri[p].begin(), ri[p].end(), e.L));
    }

    t--;
}

int main() {
    initialize();

    sumup(1);
    dfs(1);

    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);

    return 0;
}
