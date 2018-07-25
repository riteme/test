
#include "bits/stdc++.h"
#define inf 2e18
#define N 200000
#define MOD 998244353

using namespace std;
typedef long long LL;

struct Edge {
    int next, to;
} ed[N + 5];

int n, le[N + 5], ri[N + 5], value[N + 5], last[N + 5], minn[N + 5][20],
    beg[N + 5], dep[N + 5], que[N + 5], lg[N + 5], cnt = 0, ecnt = 0;
LL dis[N + 5], ans[N + 5];

void add(int u, int v) {
    ed[++ecnt].to = v, ed[ecnt].next = last[u], last[u] = ecnt;
    return;
}

void buildST() {
    lg[0] = -1;
    for (int i = 1; i <= cnt; i++)
        minn[i][0] = que[i], lg[i] = lg[i >> 1] + 1;
    for (int j = 1; j <= lg[cnt]; j++)
        for (int i = 1; i <= cnt; i++)
            if (dep[minn[i][j - 1]] <
                dep[minn[min(i + (1 << j - 1), cnt)][j - 1]])
                minn[i][j] = minn[i][j - 1];
            else
                minn[i][j] = minn[min(i + (1 << j - 1), cnt)][j - 1];
    return;
}
int getLCA(int u, int v) {
    if (beg[u] > beg[v])
        swap(u, v);
    int l = beg[u], r = beg[v], len = lg[r - l + 1];
    if (dep[minn[l][len]] < dep[minn[r - (1 << len) + 1][len]])
        return minn[l][len];
    return minn[r - (1 << len) + 1][len];
}
void getDFS(int x) {
    que[++cnt] = x;
    beg[x] = cnt;
    for (int i = last[x], v = ed[i].to; i; i = ed[i].next, v = ed[i].to) {
        dep[v] = dep[x] + 1;
        dis[v] = dis[x] + value[v];
        getDFS(v);
        que[++cnt] = x;
    }
    return;
}

int main() {
    freopen("watchdog.in", "r", stdin);
    // freopen("watchdog.out","w",stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", le + i, ri + i);
    for (int i = 2; i <= n; i++) {
        int father;
        scanf("%d%d", &father, value + i);
        add(father, i);
    }
    cnt = 0;
    dis[1] = dep[1] = 0;
    getDFS(1);
    buildST();
    for (int i = 1; i <= n; i++)
        ans[i] = -1;
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++) {
            int l = getLCA(i, j), dp = dep[i] + dep[j] - (dep[l] << 1);
            LL len = dis[i] + dis[j] - 2 * dis[l];
            if (dp >= le[l] && dp <= ri[l])
                ans[l] = max(ans[l], len);
        }
    LL now = 1;
    ans[0] = 0;
    long long tpow = 1;
    long long answer = 0;
    for (int i = n; i >= 1; i--) {
        ans[i] %= MOD;
        answer = (answer + tpow * ans[i]) % MOD;
        tpow = tpow * 23333 % MOD;
    }  // for

    if (answer < 0)
        answer += MOD;

    printf("%lld\n", answer);
    return 0;
}
