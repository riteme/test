#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

#define NMAX 1000

static int n, m;
static unordered_set<int> G[NMAX + 10];

bool test(int s, int t) {
    static bool mark[NMAX + 10];
    static unordered_set<int> D[NMAX + 10];
    memset(mark, 0, sizeof(mark));
    queue<int> q;
    for (int u = 1; u <= n; u++) {
        D[u] = G[u];
        if (D[u].size() == 2) {
            q.push(u);
            mark[u] = true;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (D[u].size() < 2 || u == s || u == t) continue;
        int a = *D[u].begin();
        int b = *next(D[u].begin());
        D[a].erase(u);
        D[b].erase(u);
        D[a].insert(b);
        D[b].insert(a);
        if (D[a].size() == 2 && !mark[a]) {
            q.push(a);
            mark[a] = true;
        }
        if (D[b].size() == 2 && !mark[b]) {
            q.push(b);
            mark[b] = true;
        }
    }

    return D[s].size() == 1 && D[t].size() == 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].insert(v);
        G[v].insert(u);
    }

    long long ans = 0;
    for (int s = 1; s <= 1; s++) for (int t = s + 1; t <= n; t++) {
        if (test(s, t)) {
            ans++;
            fprintf(stderr, "%d -- %d\n", s, t);
        }
    }
    printf("%lld\n", ans);

    return 0;
}
