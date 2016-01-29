#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200
#define MMAX 1000

static int n;
static int m;
static int level[NMAX + 10];
static vector<int> G[NMAX + 10];
static bool marked[NMAX + 10];
static int W[NMAX + 10][NMAX + 10];
static bool flag;
static int edge_to[NMAX + 10];
static int answer;

void bfs() {
    for (int i = 1; i <= n; i++) {
        level[i] = INT_MAX;
    }  // for
    level[1] = 0;

    memset(marked, false, sizeof(marked));
    marked[1] = true;
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (W[u][v] <= 0) {
                continue;
            }

            if (!marked[v]) {
                level[v] = min(level[v], level[u] + 1);
                marked[v] = true;
                q.push(v);
            }
        }  // for
    }      // while
}

void dfs(int u) {
    for (int i = 0; i < G[u].size() and !flag; i++) {
        int v = G[u][i];

        if (W[u][v] <= 0) {
            continue;
        }

        if (level[u] + 1 == level[v] and !marked[v]) {
            marked[v] = true;
            edge_to[v] = u;

            if (v == n) {
                flag = true;
            } else {
                dfs(v);
            }
        }
    }  // for
}

void dfs() {
    memset(marked, false, sizeof(marked));
    memset(edge_to, 0, sizeof(edge_to));
    marked[1] = true;
    edge_to[1] = 0;
    flag = false;

    dfs(1);
}

void dinic() {
    while (true) {
        bfs();

        if (level[n] == INT_MAX) {
            return;
        }

        dfs();

        int x = n;
        int newflow = INT_MAX;
        while (edge_to[x] != 0) {
            int u = edge_to[x];
            newflow = min(newflow, W[u][x]);

            x = edge_to[x];
        }  // while

        answer += newflow;
        x = n;
        while (edge_to[x] != 0) {
            int u = edge_to[x];
            W[u][x] -= newflow;
            W[x][u] += newflow;

            x = edge_to[x];
        }  // while
    }      // while
}

void initialize() {
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            W[x][y] = 0;
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }  // for

    for (int i = 1; i <= m; i++) {
        int u, v;
        int w;
        scanf("%d%d%d", &u, &v, &w);

        G[u].push_back(v);
        G[v].push_back(u);
        W[u][v] = w;
    }  // for

    answer = 0;
}

int main() {
    freopen("dinic.in", "r", stdin);
    freopen("dinic.out", "w", stdout);

    while (scanf("%d%d", &n, &m) != EOF) {
        initialize();

        dinic();

        printf("%d\n", answer);
    }  // while

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
