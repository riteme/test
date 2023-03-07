#include <cstdio>
#include <cstring>

#include <vector>

using namespace std;

constexpr int NMAX = 5000;

int n;
vector<int> G[NMAX + 10];
int f[NMAX + 10];
int dist[NMAX + 10];

void dfs(int u, int p) {
    for (int v : G[u]) if (!f[v] && v != p) {
        dist[v] = dist[u] + 1;
        dfs(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; ) {
        if (f[i]) {
            i++;
            continue;
        }

        dist[i] = 1;
        dfs(i, 0);
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (!f[j] && dist[j] > dist[u])
                u = j;
        }

        dist[u] = 1;
        dfs(u, 0);
        int v = 0;
        for (int j = 1; j <= n; j++) {
            if (!f[j] && dist[j] > dist[v])
                v = j;
        }

        f[u] = v;
        f[v] = u;
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", f[i]);
    }

    return 0;
}
