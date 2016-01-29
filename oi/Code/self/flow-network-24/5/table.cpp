#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NO_SOLUTION "No Solution!"

static int m;
static int n;
static int cnt;
static vector<vector<int>> G;
static vector<vector<int>> W;
static vector<int> level;
static vector<bool> marked;
static vector<int> edge_to;
static vector<int> min_edge;
static int last;

void initialize() {
    scanf("%d%d", &m, &n);

    G.resize(m + n + 10);
    level.resize(m + n + 10);
    marked.resize(m + n + 10);
    edge_to.resize(m + n + 10);
    min_edge.resize(m + n + 10);

    W.resize(m + n + 10);
    for (auto &e : W) {
        e.resize(m + n + 10);
    }  // foreach in W

    cnt = 0;
    for (int i = 1; i <= m; i++) {
        int a;
        scanf("%d", &a);

        G[0].push_back(i);
        G[i].push_back(0);
        W[0][i] = a;
        cnt += a;
    }  // for

    for (int i = m + 1; i <= m + n; i++) {
        int a;
        scanf("%d", &a);

        G[i].push_back(m + n + 1);
        G[m + n + 1].push_back(i);
        W[i][m + n + 1] = a;
    }  // for

    for (int i = 1; i <= m; i++) {
        for (int j = m + 1; j <= m + n; j++) {
            G[i].push_back(j);
            G[j].push_back(i);
            W[i][j] = 1;
        }  // for
    }      // for
}

void bfs() {
    for (auto &e : level) {
        e = INT_MAX;
    }  // foreach in level

    for (int i = 0; i < marked.size(); i++) {
        marked[i] = false;
    }  // for

    queue<int> q;
    q.push(0);
    marked[0] = true;
    level[0] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : G[u]) {
            if (W[u][v] <= 0) {
                continue;
            }

            if (!marked[v]) {
                marked[v] = true;
                level[v] = min(level[v], level[u] + 1);

                q.push(v);
            }
        }  // foreach in G[u]
    }      // while
}

bool dfs(int u) {
    bool status = false;

    for (auto v : G[u]) {
        if (W[u][v] <= 0) {
            continue;
        }

        if (v == m + n + 1) {
            last = 0;
            edge_to[v] = u;
            int x = v;
            int newflow = min(min_edge[u], W[u][v]);
            while (edge_to[x] != -1) {
                int p = edge_to[x];
                W[p][x] -= newflow;
                W[x][p] += newflow;

                if (W[p][x] == 0 and last == 0) {
                    last = p;
                }
            }  // while

            break;
        }

        if (!marked[v] and level[u] + 1 == level[v]) {
            marked[v] = true;
            edge_to[v] = u;
            min_edge[v] = min(min_edge[u], W[u][v]);

            status = status or dfs(v);
        }
    }  // foreach in G[u]

    if (flag) {
        if (edge_to[u] != -1) {
            int p = edge_to[u];

            W[p][u] -= min_edge[u];
            W[u][p] += min_edge[u];

            if (W[p][u] == 0) {
                flag = true;
            }
        }
    }

    return status;
}

void dfs() {
    for (int i = 0; i < marked.size(); i++) {
        marked[i] = false;
    }  // for

    for (auto &e : edge_to) {
        e = -1;
    }  // foreach in edge_to

    for (auto &e : min_edge) {
        e = INT_MAX;
    }  // foreach in min_edge

    marked[0] = true;
    flag = true;
    last = 0;

    dfs(0);
}

void dinic() {
    while (true) {
        bfs();

        if (level[m + n + 1] == INT_MAX) {
            return;
        }

        dfs();

        // for (int i = 0; i <= m + n + 1; i++) {
        //     printf("Node %d:", i);
        //     for (auto v : G[i]) {
        //         if (W[i][v] > 0) {
        //             printf(" (%d, %d)", v, W[i][v]);
        //         }
        //     }  // foreach in G[i]
        //     printf("\n");
        // }  // for
        // printf("\n");
    }  // while
}

int main() {
    // freopen("table.in", "r", stdin);
    // freopen("table.out", "w", stdout);
    initialize();

    dinic();

    int people_count = 0;
    for (int i = 1; i <= m; i++) {
        people_count += W[i][0];
    }  // for

    if (people_count < cnt) {
        printf("0");
    } else {
        printf("1\n");

        for (int i = 1; i <= m; i++) {
            for (int j = m + 1; j <= m + n; j++) {
                if (!W[i][j]) {
                    printf("%d ", j - m);
                }
            }  // for

            printf("\n");
        }  // for
    }

    fcloseall();
    return 0;
}  // function main
