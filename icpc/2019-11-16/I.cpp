// WHY DOES std::sort NOT WORK???

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;
typedef __int128_t i8;

static int n, m, ecnt;
static struct Edge {
    int v, nxt;
} e[NMAX * 3 + 10];
static int G[NMAX + 10];
static int c[NMAX + 10];
static int id[NMAX + 10];
static i64 cnt[NMAX + 10], tm[NMAX + 10], num[NMAX + 10];
static i64 sum[NMAX + 10];

static int vis[NMAX + 10];
static int stk[2 * NMAX + 10], t;
static int pos[NMAX + 10];
int dfs(int x, int k) {
    vis[x] = k;
    stk[++t] = x;
    pos[x] = t;
    if (c[x] == x) return t;
    if (vis[c[x]])
        return vis[c[x]] != k ? t : pos[c[x]];
    return dfs(c[x], k);
}

int find(int x) {
    return c[x] == x ? x : c[x] = find(c[x]);
}

void add(int i, int d, int t) {
    sum[i] += cnt[i] * (t - tm[i]);
    tm[i] = t;
    cnt[i] += d;
}

void link(int u, int v) {
    ecnt++;
    e[ecnt].v = v;
    e[ecnt].nxt = G[u];
    G[u] = ecnt;
}

bool cmp(int i, int j) {
    if (!num[i]) return true;
    if (!num[j]) return false;
    return (double) sum[i] / num[i] < (double) sum[j] / num[j];
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++) {
            c[i] = i;
            G[i] = 0;
        }
        ecnt = 0;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            if (u == v) continue;
            link(u, v);
            link(v, u);
        }
        for (int u = 1; u <= n; u++) {
            for (int i = G[u]; i; i = e[i].nxt) {
                int v = e[i].v;
                c[v] = c[u];
            }
        }

        for (int i = 1; i <= n; i++) {
            sum[i] = cnt[i] = 0;
            tm[i] = 1;
        }

        memset(vis + 1, 0, sizeof(int) * n);
        memset(num + 1, 0, sizeof(i64) * n);
        for (int u = 1; u <= n; u++) if (!vis[u]) {
            t = 0;
            int p = dfs(u, u);
            if (p != t) {
                for (int i = p; i <= t; i++) {
                    c[stk[i]] = stk[p];
                    num[stk[p]]++;
                }
            } else if (c[stk[t]] == stk[t])
                num[stk[t]]++;
        }
        for (int u = 1; u <= n; u++) {
            c[u] = find(u);
            cnt[c[u]]++;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = G[i]; j; j = e[j].nxt) {
                int v = e[j].v;
                add(c[i], 1, i);
                add(c[v], -1, i);
                c[v] = c[i];
            }
        }
        for (int i = 1; i <= n; i++) {
            add(i, 0, n + 1);
            id[i] = i;
        }
        stable_sort(id + 1, id + n + 1, cmp);
        for (int _i = n; _i >= 1 && sum[id[_i]]; _i--) {
            int i = id[_i];
            double ans = (double) sum[i] / n / num[i];
            for (int j = 0; j < num[i]; j++)
                printf("%.6lf\n", ans);
        }
    }
    return 0;
}
