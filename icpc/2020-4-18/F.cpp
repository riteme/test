#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 1000

int n;
bool del[NMAX + 10], in[NMAX + 10];
i64 G[NMAX + 10][NMAX + 10], v[NMAX + 10], c[NMAX + 10];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
        scanf("%lld", &G[i][j]);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", v + i);
        c[i] = G[i][i] - v[i];
        for (int j = 1; j <= n; j++)
            if (i != j) c[i] += G[i][j] + G[j][i];
        del[i] = in[i] = false;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
    if (c[i] <= 0) {
        q.push(i);
        in[i] = true;
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        del[u] = true;
        for (int v = 1; v <= n; v++) if (!del[v]) {
            c[v] -= G[u][v] + G[v][u];
            if (!in[v] && c[v] <= 0) {
                q.push(v);
                in[v] = true;
            }
        }
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) if (!del[i]) {
        ans -= v[i];
        ans += G[i][i];
        for (int j = 1; j <= n; j++) if (!del[j] && i != j)
            ans += G[i][j];
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}