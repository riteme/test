#pragma comment(linker, "/STACK:16777216")

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000

static int n;
static vector<int> G[NMAX + 10];
static i64 cnt[NMAX + 10], sum[NMAX + 10];
static i64 ans;

void dp(int x, int f) {
    cnt[x] = 1;
    sum[x] = 0;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == f) continue;
        dp(v, x);
        ans += cnt[x] * sum[v] + cnt[v] * sum[x];
        sum[x] += sum[v] + cnt[v];
        cnt[x] += cnt[v];
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        ans = 0;
        dp(1, 0);
        ans = (i64) n * (n - 1) * (n - 2) / 6 - ans;
        printf("%lld\n", ans);
        for (int i = 1; i <= n; i++)
            G[i].clear();
    }
    return 0;
}
