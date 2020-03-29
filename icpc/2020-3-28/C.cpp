#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

int n, m, K;
vector<int> G[NMAX + 10];
int fa[NMAX + 10], dep[NMAX + 10];
int out[NMAX + 10];

void dfs(int x) {
    for (int v : G[x]) {
        dep[v] = dep[x] + 1;
        dfs(v);
    }
}

void initialize() {
    scanf("%d%d%d", &n, &m, &K);
    memset(fa + 1, 0, sizeof(int) * n);
    for (int i = 1; i <= n; i++)
        G[i].clear();

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[v].push_back(u);
        fa[u] = v;
        out[v]++;
    }

    for (int i = 1; i <= n; i++) if (!fa[i]) {
        dep[i] = 0;
        dfs(i);
    }
}

struct Node {
    int u;

    bool operator<(const Node &z) const {
        return dep[u] < dep[z.u];
    }
};

void solve() {
    initialize();

    priority_queue<Node> q;
    for (int i = 1; i <= n; i++)
        if (!out[i]) q.push({i});

    int cnt = 0;
    vector<int> batch;
    batch.reserve(K);
    do {
        cnt++;
        batch.clear();
        for (int i = 0; i < K && !q.empty(); i++) {
            batch.push_back(q.top().u);
            q.pop();
        }

        for (int v : batch) {
            int u = fa[v];
            out[u]--;
            if (!out[u])
                q.push({u});
        }
    } while (!q.empty());

    printf("%d\n", cnt);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}