#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

int n, K;
bool mark[NMAX + 10];
int fa[NMAX + 10], f[NMAX + 10];
vector<int> G[NMAX + 10];

void dp(int x) {
    for (int v : G[x]) if (v != fa[x]) {
        fa[v] = x;
        dp(v);
        f[x] += f[v];
    }
}

int m;
int seq[NMAX + 10];

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 0; i < K; i++) {
        int j;
        scanf("%d", &j);
        f[j] = 1;
        mark[j] = true;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dp(1);
    for (int i = 1; i <= n; i++) if (!mark[i]) {
        bool ok = true;
        int sum = 0;
        for (int v : G[i]) if (v != fa[i]) {
            ok &= f[v] ? 1 : 0;
            sum += f[v];
        }
        if (fa[i]) ok &= sum < K;
        if (ok) seq[m++] = i;
    }

    printf("%d\n", m);
    for (int i = 0; i < m; i++)
        printf("%d ", seq[i]);
    puts("");
    return 0;
}