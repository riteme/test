#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 200000

struct Edge {
    int v, id;
};

static int n, m, t;
static int deg[NMAX + 10], fa[NMAX + 10];
static vector<Edge> G[NMAX + 10];
static bool mark[MMAX + 10];
static int cur[NMAX + 10];
static int seq[MMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

void dfs(int x) {
    for (int &i = cur[x]; i < G[x].size(); ) {
        auto &e = G[x][i++];
        int j = abs(e.id);
        if (mark[j])
            continue;
        mark[j] = true;
        dfs(e.v);
        seq[t--] = e.id;
    }
}

int main() {
    int type;
    scanf("%d%d%d", &type, &n, &m);
    int cnt = n;
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        int x = find(u);
        int y = find(v);
        if (x != y) {
            fa[x] = y;
            cnt--;
        }

        G[u].push_back({v, i});
        if (type == 1) {
            G[v].push_back({u, -i});
            deg[u]++;
            deg[v]++;
        } else {
            deg[u]++;
            deg[v]--;
        }
    }

    for (int i = 1; i <= n; i++)
        cnt -= G[i].empty();

    bool ok = cnt <= 1;
    for (int i = 1; ok && i <= n; i++) {
        if (type == 1)
            ok &= deg[i] % 2 == 0;
        else
            ok &= deg[i] == 0;
    }

    if (ok) {
        puts("YES");

        t = m;
        for (int i = 1; i <= n; i++)
        if (!G[i].empty()) {
            dfs(i);
            break;
        }

        for (int i = 1; i <= m; i++)
            printf("%d ", seq[i]);
        puts("");
    } else puts("NO");

    return 0;
}
