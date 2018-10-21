#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define LOGN 20
#define MOD 1000000007

struct Edge {
    int v, w;
};

static int n, m, L;
static vector<Edge *> G[NMAX + 10];
static bool mark[NMAX + 10];
static int cnt[NMAX + 10], out[NMAX + 10];
static int size[NMAX + 10], jmp[LOGN][NMAX + 10], ms;
static i64 dist[NMAX + 10], fac[NMAX + 10], fi[NMAX + 10];
static int seq[NMAX + 10], t;

i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

inline i64 c(int a, int b) {
    if (a < b) return 0;
    return fac[a] * fi[b] % MOD * fi[a - b] % MOD;
}

void dfs(int x, int f) {
    size[x] = 1;
    for (auto e : G[x]) {
        int v = e->v;
        if (v == f || mark[v]) continue;
        dfs(v, x);
        size[x] += size[v];
    }
}

void walk(int x, int f) {
    for (auto e : G[x]) {
        int v = e->v;
        if (v == f || mark[v]) continue;
        dist[v] = dist[x] + e->w;
        walk(v, x);
    }
}

void scan(int x, int f) {
    seq[++t] = x;
    for (auto e : G[x])
        if (e->v != f && !mark[e->v]) scan(e->v, x);
}

int center(int x, int f) {
    for (auto e : G[x]) {
        int v = e->v;
        if (v != f && !mark[v] && size[v] > ms) return center(v, x);
    }
    return x;
}

void eval(int x, int s) {
    t = 0;
    scan(x, 0);
    sort(seq + 1, seq + t + 1, [](int i, int j) { return dist[i] < dist[j]; });
    for (int i = 1, j = t; i <= t; i++) {
        while (j && dist[seq[i]] + dist[seq[j]] > L) j--;
        cnt[seq[i]] += s * j;
    }
}

void solve(int x) {
    dfs(x, 0);
    ms = size[x] >> 1;
    int p = center(x, 0);
    mark[p] = true;
    for (auto e : G[p]) {
        int v = e->v;
        if (!mark[v]) solve(v);
    }
    dist[p] = 0;
    walk(p, 0);
    eval(p, 1);
    for (auto e : G[p])
        if (!mark[e->v]) eval(e->v, -1);
    mark[p] = false;
}

void prepare(int x, int f) {
    for (auto e : G[x]) {
        int v = e->v;
        if (v == f) continue;
        dist[v] = dist[x] + e->w;
        jmp[0][v] = x;
        prepare(v, x);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &L);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(new Edge{v, w});
        G[v].push_back(new Edge{u, w});
    }

    solve(1);

    dist[1] = 0;
    jmp[0][1] = 1;
    prepare(1, 0);
    for (int j = 1; j < LOGN; j++) for (int i = 1; i <= n; i++)
        jmp[j][i] = jmp[j - 1][jmp[j - 1][i]];
    for (int i = 1; i <= n; i++) {
        int p = i;
        for (int j = LOGN - 1; j >= 0; j--)
            if (dist[i] - dist[jmp[j][p]] <= L) p = jmp[j][p];
        out[p]++;
    }

    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
    fi[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; i--) fi[i] = fi[i + 1] * (i + 1) % MOD;

    i64 ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans + c(cnt[i], m) - c(cnt[i] - out[i], m)) % MOD;
    ans = ans * fac[m] % MOD;
    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);

    return 0;
}
