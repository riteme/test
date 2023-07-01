#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

constexpr int NMAX = 2000;

int n, m;
vector<int> G[NMAX + 10];
int c[NMAX + 10];
int dist[NMAX + 10];

void bfs(int s) {
    memset(dist, 0, sizeof(dist));
    dist[s] = 1;
    queue<int> q;
    q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : G[u]) {
            if (!dist[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int q;
int s[NMAX + 10], d[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", s + i, d + i);
        bfs(s[i]);
        for (int u = 1; u <= n; u++) {
            if (dist[u] - 1 < d[i])
                c[u] = -1;
        }
    }
    bool okay = true;
    for (int i = 1; i <= q; i++) {
        bfs(s[i]);
        int cnt = 0;
        for (int u = 1; u <= n; u++) {
            if (c[u] >= 0 && dist[u] - 1 == d[i]) {
                cnt++;
                c[u] = 1;
            }
        }
        if (cnt == 0)
            okay = false;
    }
    puts(okay ? "Yes" : "No");
    if (okay) {
        if (q == 0)
            c[1] = 1;
        for (int u = 1; u <= n; u++) {
            printf("%d", (c[u] == 1));
        }
        puts("");
    }
    return 0;
}
