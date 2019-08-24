/**
 * POJ 2391 Ombrophobic Bovines
 * 考虑到每个点都有两个属性，因此拆点，一个为牛的数量，一个棚子大小
 * 由于要使最短路径中最长的尽可能短，考虑使用二分枚举
 * 点数和边数较少，可以使用Floyd进行最短路计算
 * 此题非常无耻**卡指针**，就只能用数组模拟了......
 */

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define PATHMAX 600000
#define MEMORY_SIZE 200000
#define INFTY 4000000000000

typedef long long ntype;

struct Edge {
    int from;
    int to;
    ntype capacity;
    Edge *reverse_edge;
};  // struct Edge

static int n, m, ncows;
static int s, t;
static int a[NMAX + 10];
static int b[NMAX + 10];
static ntype W[NMAX + 10][NMAX + 10];
static ntype P[NMAX + 10][NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int level[NMAX + 10];
static int path_count;
static ntype paths[PATHMAX];
static Edge memory[MEMORY_SIZE];
static int used;

inline void refresh_memory() {
    used = 0;
}

inline Edge *allocate() {
    return &memory[used++];
}

static void initialize() {
    scanf("%d%d", &n, &m);
    ncows = 0;
    s = 2 * n + 1;
    t = 2 * n + 2;

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", a + i, b + i);
        ncows += a[i];
    }  // for

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                W[i][j] = P[i][j] = 0;
            else
                W[i][j] = P[i][j] = INFTY;
        }  //    for
    }      // for

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        if (u != v && w < W[u][v])
            W[u][v] = W[v][u] = P[u][v] = P[v][u] = w;
    }  // for
}

static void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (P[i][k] + P[k][j] < P[i][j]) {
                    P[i][j] = P[i][k] + P[k][j];
                }
            }  // for
        }      // for
    }          // for
}

static void sort_path() {
    paths[0] = 0;
    unsigned pos = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (P[i][j] < INFTY)
                paths[pos++] = P[i][j];
        }  // for
    }      // for

    sort(paths, paths + pos);

    path_count = pos - 1;
}

inline void add_edge(int u, int v, ntype capacity) {
    // Edge *e = new Edge;
    // Edge *re = new Edge;
    Edge *e = allocate();
    Edge *re = allocate();

    e->from = u;
    e->to = v;
    e->capacity = capacity;
    e->reverse_edge = re;

    re->from = v;
    re->to = u;
    re->capacity = 0;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);
}

static void setup_network(ntype limit) {
    refresh_memory();

    for (int i = 1; i <= t; i++) {
        G[i].clear();
    }  // for

    for (int i = 1; i <= n; i++) {
        add_edge(s, i, a[i]);
        add_edge(i + n, t, b[i]);
    };  // for

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (P[i][j] <= limit) {
                add_edge(i, j + n, INFTY);
            }
        }  // for
    }      // for
}

static void bfs() {
    memset(level, 0, sizeof(level));

    level[s] = 1;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (unsigned i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];

            if (e->capacity == 0)
                continue;

            int v = e->to;

            if (level[v] == 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }  // for
    }      // while
}

static ntype dfs(int u, ntype maxflow) {
    if (u == t)
        return maxflow;

    int current = 0;

    for (unsigned i = 0; i < G[u].size(); i++) {
        Edge *e = G[u][i];
        int v = e->to;

        if (level[u] + 1 != level[v] || e->capacity == 0)
            continue;

        ntype flow = min(maxflow - current, e->capacity);
        flow = dfs(v, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current >= maxflow)
            break;
    }  // for

    return current;
}

static int dinic() {
    int result = 0;

    while (true) {
        bfs();

        if (level[t] == 0)
            break;

        result += dfs(s, INFTY);
    }  // while

    return result;
}

static bool test(ntype limit) {
    setup_network(limit);

    int result = dinic();

    return result == ncows;
}

int main() {
    initialize();

    floyd();
    sort_path();

    int left = 0, right = path_count;
    while (right - left > 1) {
        int mid = (left + right) >> 1;
        ntype limit = paths[mid];

        bool flag = test(limit);
        if (flag)
            right = mid;
        else
            left = mid;
    }  // while

    if (right != left) {
        if (!test(paths[left]))
            left = right;
    }

    if (left == path_count && !test(paths[left]))
        printf("-1");
    else
        printf("%lld", paths[left]);

    return 0;
}  // function main
