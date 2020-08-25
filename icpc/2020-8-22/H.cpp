#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LMAX 30

struct BIT {
    BIT() : n(0) {}

    int n;
    vector<int> a;

    void resize(int _n) {
        n = _n;
        a.clear();
        a.resize(n + 1);
    }

    void add(int x, int v) {
        if (x < 1)
            return;
        for ( ; x <= n; x += x & -x) {
            a[x] += v;
        }
    }

    int query(int x) {
        if (x < 1)
            return 0;
        x = min(x, n);
        int r = 0;
        for ( ; x; x -= x & -x) {
            r += a[x];
        }
        return r;
    }
};

int n, q;
int w0[NMAX + 10];
vector<int> G[NMAX + 10];

bool mark[NMAX + 10];
int sz[NMAX + 10];

void get_size(int x, int p) {
    sz[x] = 1;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (mark[v] || v == p)
            continue;
        get_size(v, x);
        sz[x] += sz[v];
    }
}

int center(int x, int p, int maxs) {
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (mark[v] || v == p)
            continue;
        if (sz[v] * 2 > maxs)
            return center(v, x, maxs);
    }
    return x;
}

int dfs(int x, int p, int c, int *idx, int *dep) {
    idx[x] = c;
    int rax = dep[x];
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (mark[v] || v == p)
            continue;
        dep[v] = dep[x] + 1;
        int ret = dfs(v, x, c, idx, dep);
        rax = max(rax, ret);
    }
    return rax;
}

void scan(int x, int p, int *dep, BIT &bit) {
    if (dep[x])
        bit.add(dep[x], w0[x]);
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (mark[v] || v == p)
            continue;
        scan(v, x, dep, bit);
    }
}

int top[LMAX][NMAX + 10];
int idx[LMAX][NMAX + 10];
int dep[LMAX][NMAX + 10];
vector<BIT> bit[NMAX + 10];

void build(int x, int l) {
    get_size(x, 0);
    int p = center(x, 0, sz[x]);
    mark[p] = true;

    bit[p].reserve(G[p].size() + 1);
    bit[p].resize(1);
    dep[l][p] = 0;
    int d = dfs(p, 0, p, top[l], dep[l]);
    bit[p][0].resize(d);
    scan(p, 0, dep[l], bit[p][0]);

    int cnt = 0;
    for (int i = 0; i < G[p].size(); i++) {
        int v = G[p][i];
        if (!mark[v])
            cnt++;
        else
            continue;

        bit[p].resize(cnt + 1);
        dep[l][v] = 1;
        d = dfs(v, p, cnt, idx[l], dep[l]);
        bit[p][cnt].resize(d);
        scan(v, p, dep[l], bit[p][cnt]);
    }

    for (int i = 0; i < G[p].size(); i++) {
        int v = G[p][i];
        if (mark[v])
            continue;
        build(v, l + 1);
    }
}

int query(int x, int d) {
    int rax = w0[x];
    for (int l = 0; top[l][x] != x; l++) {
        int p = top[l][x], u = idx[l][x];

        if (dep[l][x] <= d) {
            int s = d - dep[l][x];
            rax += w0[p];
            rax += bit[p][0].query(s);
            rax -= bit[p][u].query(s);
        }
    }
    rax += bit[x][0].query(d);
    return rax;
}

void modify(int x, int v) {
    v = v - w0[x];
    w0[x] += v;
    for (int l = 0; top[l][x] != x; l++) {
        int p = top[l][x], u = idx[l][x];
        bit[p][0].add(dep[l][x], v);
        bit[p][u].add(dep[l][x], v);
    }
}

void reset() {
    memset(mark + 1, 0, n);
    for (int i = 0; i < LMAX; i++) {
        memset(top[i] + 1, 0, sizeof(int) * n);
        memset(idx[i] + 1, 0, sizeof(int) * n);
        memset(dep[i] + 1, 0, sizeof(int) * n);
    }
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        bit[i].clear();
    }
}

void _main() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", w0 + i);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    build(1, 0);

    for (int i = 0; i < q; i++) {
        char op[4];
        int x, v;
        scanf("%s%d%d", op, &x, &v);
        if (op[0] == '?') {
            int ans = query(x, v);
            printf("%d\n", ans);
        } else {
            modify(x, v);
        }
    }

    reset();
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        _main();
    }
    return 0;
}
