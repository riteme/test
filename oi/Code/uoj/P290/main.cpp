#define NDEBUG

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 500000
#define MOD 998244353LL

typedef long long i64;

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

static int n, m, cnt[NMAX + 10], in[NMAX + 10], now;
static i64 ans, f[NMAX + 10], fac[NMAX * 2 + 10], fi[NMAX * 2 + 10], ti[NMAX + 10];
static vector<int> G[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);
    memset(cnt + 1, 0, sizeof(int) * n);
    memset(in + 1, 0, sizeof(int) * n);
    memset(f + 1, 0, sizeof(i64) * n);
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    now = 0;
    ans = 1;
}

void dfs(int x, int fa = 0) {
#ifndef NDEBUG
    fprintf(stderr, "%d ", x);
#endif
    in[x] = ++now;
    int p = 0;
    i64 pr = 1;
    for (int v : G[x]) {
        if (v != fa && in[v] && in[v] < in[x]) {
            cnt[x]++;
            cnt[v]--;
        } else if (!in[v]) {
            dfs(v, x);
            cnt[x] += cnt[v];
            if (!cnt[v]) {
                p++;
                pr = pr * f[v] % MOD;
            }
        }
    }
    if (cnt[x] > 1) ans = 0;
    else if (!fa || cnt[x]) {
        for (int i = 0; i <= p; i += 2)
            add(f[x], fac[p] * fi[p - i] % MOD * fi[i >> 1] % MOD * ti[i >> 1] % MOD);
        ans = ans * f[x] % MOD * pr % MOD;
    } else {
        i64 s = 0;
        for (int i = 0; i < p; i += 2)
            add(s, fac[p] * fi[p - i] % MOD * fi[i >> 1] % MOD * ti[i >> 1] % MOD);
        for (int i = 0; i < p; i += 2)
            add(f[x], fac[p] * fi[p - i] % MOD * fi[i >> 1] % MOD * ti[i >> 1] % MOD * (p - i) % MOD);
        add(f[x], (s + (p & 1 ? 0 : fac[p] * fi[p >> 1] % MOD * ti[p >> 1] % MOD)) % MOD);
        f[x] = f[x] * pr % MOD;
    }
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= NMAX * 2; i++) fac[i] = fac[i - 1] * i % MOD;
    fi[NMAX * 2] = inv(fac[NMAX * 2]);
    for (int i = NMAX * 2; i >= 1; i--) fi[i - 1] = fi[i] * i % MOD;
    ti[0] = 1;
    ti[1] = inv(2);
    for (int i = 2; i <= NMAX; i++) ti[i] = ti[i - 1] * ti[1] % MOD;
    int T;
    scanf("%d", &T);
    while (T--) {
        initialize();
        dfs(1);
#ifndef NDEBUG
        fputc('\n', stderr);
        for (int i = 1; i <= n; i++)
            fprintf(stderr, "%d: %2lld    [cnt = %d]\n", i, f[i], cnt[i]);
#endif
        printf("%lld\n", ans);
    }
    return 0;
}
