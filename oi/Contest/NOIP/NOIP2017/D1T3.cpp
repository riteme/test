/**
 * O(m(log n + K))
 *
 * 使用最短路算法求出 d1[i] (1 -> i), d2 (i -> n) 最短路
 * 删去无用边，然后剩余的图中如果有 0 权环，则方案数无限
 * 否则替换边权为与最短路相比的损失，进行分类 DP
 * 设 f[i][j] 表示 j -> n 与最短路的差为 i 的方案数
 * 对于 w > 0 的边，f[i - w][v] -> f[i][j]
 * 对于 w = 0 的边，实际上是最短路 DAG，可以直接 DP
 */

#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 200000
#define KMAX 50
#define WMAX 1000

struct Edge {
    Edge(int _v, int _w)
        : v(_v), w(_w) {}

    int v, w;
};

struct Graph {
    vector<Edge *> G[NMAX + 10];

    vector<Edge *> &operator[](int x) {
        return G[x];
    }
};

static int n, m, K, MOD;
static Graph G, R;
static int d1[NMAX + 10], d2[NMAX + 10];

inline void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

void dijkstra(Graph &N, int *dist, int s) {
    struct State {
        State(int _u, int _s)
            : u(_u), s(_s) {}

        int u, s;

        bool operator<(const State &b) const {
            return s > b.s;
        }
    };

    memset(dist + 1, 0x3f, sizeof(int) * n);
    dist[s] = 0;

    priority_queue<State> q;
    q.push(State(s, 0));

    while (!q.empty()) {
        State u = q.top();
        q.pop();

        if (u.s != dist[u.u])
            continue;

        for (auto e : N[u.u]) {
            int v = e->v;
            if (dist[v] > u.s + e->w) {
                dist[v] = u.s + e->w;
                q.push(State(v, dist[v]));
            }
        }
    }
}

void initialize() {
    scanf("%d%d%d%d", &n, &m, &K, &MOD);

    for (int i = 1; i <= n; i++) {
        G[i].clear();
        R[i].clear();
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(new Edge(v, w));
        R[v].push_back(new Edge(u, w));
    }
}

static bool marked[NMAX + 10], exist[NMAX + 10];

bool detect(int x) {
    if (exist[x])
        return true;
    if (marked[x])
        return false;

    marked[x] = exist[x] = true;
    for (auto e : G[x]) {
        if (!e->w && detect(e->v))
            return true;
    }

    exist[x] = false;
    return false;
}

static int in[NMAX + 10], topo[NMAX + 10];

void toposort() {
    for (int u = 1; u <= n; u++) {
        for (auto e : G[u]) {
            if (!e->w)
                in[e->v]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in[i])
            q.push(i);
    }

    int tail = 1;
    while (!q.empty()) {
        int u = q.front();
        topo[tail++] = u;
        q.pop();

        for (auto e : G[u]) {
            if (e->w)
                continue;

            in[e->v]--;

            if (!in[e->v])
                q.push(e->v);
        }
    }
}

static int f[KMAX + 10][NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        initialize();
        dijkstra(G, d1, 1);
        dijkstra(R, d2, n);

        for (int u = 1; u <= n; u++) {
            for (auto e : G[u]) {
                if (d1[u] + d2[e->v] + e->w > d1[n] + K)
                    e->w = WMAX + 1;
            }
        }

        memset(marked, 0, sizeof(marked));
        memset(exist, 0, sizeof(exist));
        if (detect(1))
            puts("-1");
        else {
            for (int u = 1; u <= n; u++) {
                for (auto e : G[u]) {
                    e->w = d2[e->v] + e->w - d2[u];
                }
            }

            memset(f, 0, sizeof(f));
            toposort();

            f[0][n] = 1;
            for (int i = 0; i <= K; i++) {
                for (int u = 1; u <= n; u++) {
                    for (auto e : G[u]) {
                        if (0 < e->w && e->w <= i)
                            add(f[i][u], f[i - e->w][e->v]);
                    }
                }

                for (int j = n; j >= 1; j--) {
                    int u = topo[j];
                    for (auto e : G[u]) {
                        if (!e->w)
                            add(f[i][u], f[i][e->v]);
                    }
                }
            }

            int ans = 0;
            for (int i = 0; i <= K; i++) {
                add(ans, f[i][1]);
            }

            printf("%d\n", ans);
        }
    }

    return 0;
}
