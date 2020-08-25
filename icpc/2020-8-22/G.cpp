#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long u64;
typedef long long i64;

#define NMAX 40
#define SMAX (1 << 21)
#define MOD 1000000007

int n, m;
u64 G[NMAX + 10];
int pa[NMAX + 10];

int find(int x) {
    return pa[x] ? pa[x] = find(pa[x]) : x;
}

void link(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y)
        pa[x] = y;
}

int f[SMAX];

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

vector<int> b[NMAX + 10];
i64 fac[NMAX + 10], fi[NMAX + 10];

i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

void _main() {
    for (int i = 1; i <= n; i++) {
        b[i].clear();
    }
    memset(pa + 1, 0, sizeof(int) * n);
    memset(G + 1, 0, sizeof(u64) * n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u] |= 1ull << v;
        link(u, v);
    }

    for (int i = 1; i <= n; i++) {
        b[find(i)].push_back(i);
    }

    i64 ans = fac[n];
    for (int i = 1; i <= n; i++)
    if (b[i].size()) {
        int smax = 1 << b[i].size();

        memset(f, 0, sizeof(int) * smax);
        f[0] = 1;

        for (int S = 0; S < smax; S++)
        if (f[S] > 0) {
            u64 P = 0;
            for (int j = 0; j < b[i].size(); j++)
            if ((S >> j) & 1) {
                P |= 1ull << b[i][j];
            }

            for (int j = 0; j < b[i].size(); j++) {
                int v = b[i][j];
                if (!((S >> j) & 1) && (G[v] & P) == G[v])
                    add(f[S | (1 << j)], f[S]);
            }
        }

        ans = ans * f[smax - 1] % MOD;
        ans = ans * fi[b[i].size()] % MOD;
    }

    ans %= MOD;
    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= NMAX + 5; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    fi[NMAX + 5] = inv(fac[NMAX + 5]);
    for (int i = NMAX + 4; i >= 0; i--) {
        fi[i] = fi[i + 1] * (i + 1) % MOD;
    }

    while (scanf("%d%d", &n, &m) != EOF) {
        _main();
    }
    return 0;
}
