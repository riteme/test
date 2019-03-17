#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 3000

struct Edge {
    int v, w;
};

static int n, m;
static char buf[NMAX + 10];
static vector<Edge*> G[NMAX + 10];
static int dist[NMAX + 10], cnt[NMAX + 10];
static bool in[NMAX + 10];

bool spfa(int s) {
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(s);
    in[s] = true;
    dist[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (cnt[u] > n + m + 10) return false;
        in[u] = false;
        for (auto e : G[u]) {
            if (dist[u] + e->w < dist[e->v]) {
                dist[e->v] = dist[u] + e->w;
                cnt[e->v] = cnt[u] + 1;
                if (!in[e->v]) {
                    in[e->v] = true;
                    q.push(e->v);
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf + 1);
        for (int j = 1; j <= m; j++) {
            if (buf[j] == '>')
                G[i].push_back(new Edge{n + j, -1});
            else if (buf[j] == '<')
                G[n + j].push_back(new Edge{i, -1});
            else {
                G[i].push_back(new Edge{n + j, 0});
                G[n + j].push_back(new Edge{i, 0});
            }
        }
    }
    for (int i = 1; i <= n + m; i++)
        G[n + m + 1].push_back(new Edge{i, 0});
    if (!spfa(n + m + 1)) puts("No");
    else {
        puts("Yes");
        int md = 0x3f3f3f3f;
        for (int i = 1; i <= n + m; i++)
            md = min(md, dist[i]);
        for (int i = 1; i <= n; i++)
            printf("%d ", dist[i] - md + 1);
        printf("\n");
        for (int i = n + 1; i <= n + m; i++)
            printf("%d ", dist[i] - md + 1);
    }
    return 0;
}
