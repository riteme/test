#include <cstdio>
#include <climits>
#include <cstring>

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, m;
static int cat, mouse;
static vector<int> G[NMAX + 10];

static bool marked[NMAX + 10];
static bool in_queue[NMAX + 10];
static int dist[NMAX + 10];
static int id[NMAX + 10];

static int nxt[NMAX + 10][NMAX + 10];

static void bfs(int s) {
    memset(marked, 0, sizeof(marked));
    memset(in_queue, 0, sizeof(in_queue));

    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        id[i] = INT_MAX;
    }

    queue<int> q;
    marked[s] = true;
    dist[s] = 0;
    id[s] = s;

    for (size_t i = 0; i < G[s].size(); i++) {
        int v = G[s][i];

        in_queue[v] = true;
        dist[v] = 1;
        id[v] = v;
        q.push(v);
    }

    while (!q.empty()) {
        int u = q.front();
        marked[u] = true;
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (!marked[v] && dist[u] + 1 == dist[v])
                id[v] = min(id[v], id[u]);

            if (!in_queue[v]) {
                in_queue[v] = true;
                dist[v] = dist[u] + 1;
                id[v] = id[u];

                q.push(v);
            }
        }
    }

    memcpy(&nxt[s][0], id, sizeof(id));
}

static void initialize() {
    scanf("%d%d%d%d", &n, &m, &cat, &mouse);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        bfs(i);
    }
}

static bool visited[NMAX + 10][NMAX + 10];
static double f[NMAX + 10][NMAX + 10];

static double dp(int c, int m) {
    if (c == m)
        return 0.0;
    if (visited[c][m])
        return f[c][m];
    visited[c][m] = true;
    
    double &answer = f[c][m];
    int n1 = nxt[c][m];
    int n2 = nxt[n1][m];
    if (n1 == m || n2 == m)
        answer = 1.0;
    else {
        answer = dp(n2, m);
        for (size_t i = 0; i < G[m].size(); i++) {
            int v = G[m][i];

            answer += dp(n2, v);
        }

        answer = (answer / (G[m].size() + 1.0)) + 1.0;
    }

    return answer;
}

int main() {
    initialize();

    printf("%.3lf\n", dp(cat, mouse));

    return 0;
}

