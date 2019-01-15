#include <cstdio>
#include <cstring>

#include <queue>
#include <utility>
#include <algorithm>
#include <unordered_set>

using namespace std;

#define NMAX 100000
#define MMAX 300000

static int n, m;
static bool mark[NMAX + 10];
static unordered_set<int> G[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].insert(v);
        G[v].insert(u);
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) if (G[i].size() == 2) {
        q.push(i);
        mark[i] = true;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (G[u].size() < 2) {
            mark[u] = false;
            continue;
        }
        int a = *G[u].begin(), b = *next(G[u].begin());
        G[a].erase(u);
        G[b].erase(u);
        G[a].insert(b);
        G[b].insert(a);
        if (!mark[a] && G[a].size() == 2) {
            q.push(a);
            mark[a] = true;
        }
        if (!mark[b] && G[b].size() == 2) {
            q.push(b);
            mark[b] = true;
        }
    }
    puts(count(mark + 1, mark + n + 1, false) == 2 ? "Yes" : "No");

    return 0;
}
