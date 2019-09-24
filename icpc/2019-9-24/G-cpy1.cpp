#include <cstdio>
#include <cctype>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static char buf[BUFFERSIZE];
static size_t pos = BUFFERSIZE;

inline void getc(char &c) {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buf, 1, BUFFERSIZE, stdin);
    }
    c = buf[pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c;
    do getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        getc(c);
    } while (isdigit(c));
}

#define NMAX 300000
#define MOD 1000000007

typedef long long i64;

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

static i64 fac[NMAX + 10], fi[NMAX + 10];

inline i64 C(int n, int m) {
    if (n < m) return 0;
    return fac[n] * fi[m] % MOD * fi[n - m] % MOD;
}

static int n, m, K;
static vector<int> G[NMAX + 10];
static int fa[NMAX + 10], top[NMAX + 10], dep[NMAX + 10];
static int as[NMAX + 10], bs[NMAX + 10];

void dfs(int x, int f) {
    top[x] = 1;
    for (int v : G[x]) if (v != f) {
        fa[v] = x;
        dep[v] = dep[x] + 1;
        dfs(v, x);
        top[x] += top[x];
    }
}

void decompose(int x, int f) {
    int u = 0;
    for (int v : G[x]) if (v != f && top[v] > top[u])
        u = v;
    if (u) {
        top[u] = top[x];
        decompose(u, x);
    }
    for (int v : G[x]) if (v != f && v != u) {
        top[v] = v;
        decompose(v, x);
    }
}

inline int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

void partial_sum(int x, int f) {
    for (int v : G[x]) if (v != f) {
        partial_sum(v, x);
        as[x] += as[v];
    }
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= NMAX; i++) fac[i] = fac[i - 1] * i % MOD;
    fi[NMAX] = inv(fac[NMAX]);
    for (int i = NMAX - 1; i >= 0; i--) fi[i] = fi[i + 1] * (i + 1) % MOD;

    int T;
    //scanf("%d", &T);
    read(T);
    while (T--) {
        //scanf("%d%d%d", &n, &m, &K);
        read(n); read(m); read(K);
        for (int i = 1; i <= n; i++) {
            G[i].clear();
            as[i] = bs[i] = 0;
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            //scanf("%d%d", &u, &v);
            read(u); read(v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, 0);
        top[1] = 1;
        decompose(1, 0);
        for (int i = 0; i < m; i++) {
            int u, v;
            //scanf("%d%d", &u, &v);
            read(u); read(v);
            int p = lca(u, v);
            bs[p]++;
            as[u]++;
            as[v]++;
            as[p] -= 2;
        }
        partial_sum(1, 0);
        i64 ans = 0;
        for (int u = 1; u <= n; u++) {
            int a = as[u], b = bs[u], c = a + b;
            if (c >= K) {
                ans = (ans + C(c, K) - C(a, K)) % MOD;
            }
        }
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
