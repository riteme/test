#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000
#define MOD 998244353

typedef long long i64;

struct Item {
    int x;
    i64 cnt;
};

int n, p[NMAX + 10];
int in[NMAX + 10], tm;
int mu[NMAX + 10], d[NMAX + 10];
vector<int> dv[NMAX + 10];
vector<int> G[NMAX + 10];
vector<Item> stk[NMAX + 10];
int fa[NMAX + 10], lp[NMAX + 10];
i64 ans[NMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", p + i);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

void sieve() {
    for (int i = 1; i <= n; i++) {
        mu[i] = 1 - mu[i];
        dv[i].push_back(i);
        for (int j = 2 * i; j <= n; j += i) {
            mu[j] += mu[i];
            dv[j].push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        d[i] = 1 - d[i];
        for (int j = 2; i * j <= n; j++)
            d[i * j] += mu[j] * d[i];
    }
}

void dfs(int x, int f) {
    in[x] = ++tm;

    for (int v : G[x]) if (v != f) {
        dfs(v, x);
    }

    for (int v : dv[x]) {
        if (lp[v]) {
            int p = find(lp[v]);
            i64 sum = 0;
            while (!stk[v].empty() && in[stk[v].back().x] > in[p]) {
                auto _ = stk[v].back();
                int u = _.x;
                stk[v].pop_back();
                sum += _.cnt;
                ans[u] = (ans[u] + mu[v] * _.cnt * _.cnt) % MOD;
                int y = !stk[v].empty() && in[stk[v].back().x] > in[p] ? stk[v].back().x : p;
                ans[y] = (ans[y] - mu[v] * _.cnt * _.cnt) % MOD;
            }
            if (stk[v].empty() || in[stk[v].back().x] < in[p])
                stk[v].push_back({p, sum});
            else if (stk[v].back().x == p)
                stk[v].back().cnt += sum;
            lp[v] = x;
        }
        stk[v].push_back({x, d[x / v]});
    }
}

void dp(int x, int f) {
    for (int v : G[x]) if (v != f) {
        dp(v, x);
        ans[x] += ans[v];
    }
}

int main() {
    initialize();
    sieve();
    dfs(1, 0);
    dp(1, 0);

    for (int i = 1; i <= n; i++)
        printf("%lld ", ans[i]);
    puts("");
    return 0;
}