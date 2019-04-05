// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 100000
#define DMAX 50

typedef unsigned long long u64;

inline void chkmin(int &a, int b) {
    if (b < a) a = b;
}

inline void chkmax(int &a, int b) {
    if (b > a) a = b;
}

static int n, m, D;
static vector<int> G[NMAX + 10];
static u64 ok[NMAX + 10];
static int id[NMAX + 10][DMAX];
static int scc[NMAX + 10], cnt[NMAX + 10], sc;
static int seq[NMAX + 10], K;
static u64 dp[NMAX + 10];
static vector<int> f[NMAX + 10], g[NMAX + 10];

inline u64 rot(u64 x) {
    return ((x << 1) & ((1ULL << D) - 1)) | (x >> (D - 1));
}

inline int nxt(int x) {
    if (x == D - 1) return 0;
    return x + 1;
}

void spfa(int x, int j, int s) {
    static bool in[NMAX + 10];
    queue<int> q;
    q.push(x);
    in[x] = true;
    for (int i = 0; i < K; i++) dp[seq[i]] = 0;
    dp[x] = 1ULL << j;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in[u] = false;
        for (int v : G[u]) if (scc[v] == s) {
            u64 ns = dp[v] | rot(dp[u]);
            if (ns != dp[v]) {
                dp[v] = ns;
                if (!in[v]) {
                    q.push(v);
                    in[v] = true;
                }
            }
        }
    }
    cnt[s]++;
    for (int i = 0; i < K; i++) for (int k = 0; k < D; k++)
        if ((dp[seq[i]] >> k) & 1) id[seq[i]][k] = cnt[s];
    int c = 0;
    for (int i = 0; i < K; i++)
        if (dp[seq[i]] & ok[seq[i]]) c++;
    g[s].push_back(c);
}

void dfs(int x) {
    static int dfn[NMAX + 10], low[NMAX + 10], cur;
    static stack<int> stk;
    dfn[x] = low[x] = ++cur;
    stk.push(x);
    for (int v : G[x]) {
        if (!dfn[v]) dfs(v);
        if (!scc[v]) chkmin(low[x], low[v]);
    }

    if (dfn[x] != low[x]) return;
    K = 0;
    int u;
    sc++;
    do {
        seq[K++] = u = stk.top();
        stk.pop();
        scc[u] = sc;
    } while (u != x);
    g[sc].resize(1);
    for (int j = 0; j < D; j++)
        if (!id[x][j]) spfa(x, j, sc);

    f[sc].resize(1 + cnt[sc]);
    for (int i = 0; i < K; i++) {
        u = seq[i];
        for (int j = 0; j < D; j++) if (id[u][j])
        for (int v : G[u]) if (scc[v] && scc[v] != sc)
            chkmax(f[sc][id[u][j]], f[scc[v]][id[v][nxt(j)]]);
    }
    for (int i = 1; i <= cnt[sc]; i++)
        f[sc][i] += g[sc][i];
}

int main() {
    scanf("%d%d%d", &n, &m, &D);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        static char buf[64];
        scanf("%s", buf);
        for (int j = 0; j < D; j++)
            ok[i] |= u64(buf[j] == '1') << j;
    }
    dfs(1);
    printf("%d\n", f[scc[1]][id[1][0]]);
    return 0;
}
