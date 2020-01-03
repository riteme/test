#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, m;
static int ed[NMAX + 10];
static int in[NMAX + 10], seq[NMAX + 10];
static vector<int> G[NMAX + 10];
static vector<int> R[NMAX + 10];
static bool mark[NMAX + 10];

void dfs(int x) {
    if (mark[x]) return;
    mark[x] = true;
    for (int v : R[x])
        dfs(v);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", ed + i);
    for (int v = 1; v <= n; v++) {
        int t;
        scanf("%d", &t);
        while (t--) {
            int u;
            scanf("%d", &u);
            G[u].push_back(v);
            R[v].push_back(u);
        }
    }

    for (int i = 1; i <= m; i++)
        dfs(ed[i]);
    int mcnt = 0;
    for (int u = 1; u <= n; u++) if (mark[u]) {
        mcnt++;
        for (int v : G[u]) if (mark[v])
            in[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (mark[i] && !in[i]) q.push(i);
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        seq[++cnt] = u;
        q.pop();
        for (int v : G[u]) if (mark[v]) {
            in[v]--;
            if (!in[v]) q.push(v);
        }
    }

    if (cnt != mcnt) puts("-1");
    else {
        printf("%d\n", cnt);
        for (int i = 1; i <= mcnt; i++)
            printf("%d ", seq[i]);
        puts("");
    }

    return 0;
}
