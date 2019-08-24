/**
 * 飞行员配对方案
 * 做法：建成二分图，设置超级源点0和超级汇点m + n + 1，然后找最大流
 * 注意源点和汇点的边权不能为正无穷，而未1,因为每个人只能配对一次
 */

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
static vector<vector<int>> G;
static vector<vector<int>> W;
static vector<int> level;
static vector<bool> marked;
static vector<int> edge_to;
static bool flag;
static int answer;

void initialize() {
    scanf("%d%d", &m, &n);

    G.resize(m + n + 10);
    level.resize(m + n + 10);
    marked.resize(m + n + 10);
    edge_to.resize(m + n + 10);

    W.resize(m + n + 10);
    for (auto &e : W) {
        e.resize(m + n + 10);
    }  // foreach in W

    while (true) {
        int a, b;
        scanf("%d%d", &a, &b);

        if (a == b and a == -1) {
            break;
        }

        int u = min(a, b);
        int v = max(a, b);

        G[u].push_back(v);
        G[v].push_back(u);
        W[u][v] = 1;
    }  // while

    for (int i = 1; i <= m; i++) {
        G[0].push_back(i);
        G[i].push_back(0);
        W[0][i] = 1;
    }  // for

    for (int i = m + 1; i <= m + n; i++) {
        G[m + n + 1].push_back(i);
        G[i].push_back(m + n + 1);
        W[i][m + n + 1] = 1;
    }  // for
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

void dfs(int u) {
    for (auto v : G[u]) {
        if (!flag) {
            return;
        }

        if (W[u][v] <= 0) {
            continue;
        }

        if (!marked[v] and level[u] + 1 == level[v]) {
            marked[v] = true;
            edge_to[v] = u;

            if (v == m + n + 1) {
                flag = false;
            } else {
                dfs(v);
            }
        }
    }  // foreach in G[u]
}

void dfs() {
    for (int i = 0; i < marked.size(); i++) {
        marked[i] = false;
    }  // for

    for (auto &e : edge_to) {
        e = -1;
    }  // foreach in edge_to

    marked[0] = true;
    flag = true;

    dfs(0);
}

void dinic() {
    while (true) {
        bfs();

        if (level[m + n + 1] == INT_MAX) {
            return;
        }

        dfs();

        int newflow = INT_MAX;
        int x = m + n + 1;
        while (edge_to[x] != -1) {
            int u = edge_to[x];
            newflow = min(newflow, W[u][x]);

            x = edge_to[x];
        }  // while

        x = m + n + 1;
        while (edge_to[x] != -1) {
            int u = edge_to[x];
            W[u][x] -= newflow;
            W[x][u] += newflow;

            x = edge_to[x];
        }  // while

        answer += newflow;

        // for (int i = 0; i <= m + n + 1; i++) {
        //     printf("Node %d:", i);
        //     for (auto v : G[i]) {
        //         printf(" (%d, %d)", v, W[i][v]);
        //     }  // foreach in G[i]
        //     printf("\n");
        // }  // for
        // printf("\n");
    }  // while
}

int main() {
    freopen("air.in", "r", stdin);
    freopen("air.out", "w", stdout);
    initialize();

    dinic();

    if (answer == 0) {
        printf(NO_SOLUTION);
    } else {
        printf("%d\n", answer);

        for (int i = m + 1; i <= m + n; i++) {
            for (int j = 1; j <= m; j++) {
                if (W[i][j] > 0) {
                    printf("%d %d\n", j, i);
                }  // for
            }      // for
        }
    }

    fcloseall();
    return 0;
}  // function main
