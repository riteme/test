/**
 * 分配问题
 * tags: 残余网络最短/最长路
 * ps: 残余网络找最长路（初始时不能有环）：直接将所有边权取反，用SPFA找最短路
 * 找最长路径过程中不会出现负环。
 * 在增广的过程中，会出现反向边，**反向边的权值相反**，可能导致有环，而原网络中没有环，故出现的环中必定有源点
 * 对于**任意**一条边(u, v)，
 * 设源点s到v的最短距离为a，s到v的最短距离为b，此边权为w
 * 由最短路径的三角不等式可知
 *     a <= b + w       (1.1)
 * 增广后会出现一个 s -> ... -> u -> v -> ... -> s的环，其权值之和为：
 *     \sum = -a + b + w
 * 由(1.1)可知：
 *     -a + b + w >= 0
 * 故知此环的权值不为负
 */

#include <bits/stdc++.h>

using namespace std;

#define NMAX 10000
#define INFTY 100000000

struct Edge {
    int from;
    int to;
    int flow;
    int capacity;
    int cost;
    Edge *reverse_edge;

    int remaining() const {
        return capacity - flow;
    }
};  // struct Edge

static int n;
static int s, t;
static vector<Edge *> G[NMAX + 10];
static vector<Edge *> N[NMAX + 10];
static Edge *edge[NMAX + 10];
static int dist[NMAX + 10];
static bool in_queue[NMAX + 10];

void initialize();
void SPFA_1();
int ford_fulkerson_1();
void SPFA_2();
int ford_fulkerson_2();

int main() {
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);
    initialize();

    printf("%d\n%d", ford_fulkerson_1(), ford_fulkerson_2());

    fcloseall();
    return 0;
}  // function main

inline void add_edge(vector<Edge *> *G, int u, int v, int capacity, int cost) {
    Edge *e = new Edge();
    Edge *re = new Edge();

    e->from = u;
    e->to = v;
    e->flow = 0;
    e->capacity = capacity;
    e->cost = cost;
    e->reverse_edge = re;

    re->from = v;
    re->to = u;
    re->flow = capacity;
    re->capacity = capacity;
    re->cost = -cost;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    scanf("%d", &n);

    s = 0;
    t = 2 * n + 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int c;
            scanf("%d", &c);

            add_edge(G, i, j + n, 1, c);
            add_edge(N, i, j + n, 1, -c);
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        add_edge(G, s, i, 1, 0);
        add_edge(G, i + n, t, 1, 0);
        add_edge(N, s, i, 1, 0);
        add_edge(N, i + n, t, 1, 0);
    }  // for
}

void SPFA_1() {
    for (int i = s; i <= t; i++) {
        dist[i] = INFTY;
        edge[i] = NULL;
        in_queue[i] = false;
    }  // for
    dist[s] = 0;

    queue<int> q;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (auto e : G[u]) {
            int v = e->to;

            if (e->remaining() == 0) {
                continue;
            }

            if (dist[u] + e->cost < dist[v]) {
                dist[v] = dist[u] + e->cost;
                edge[v] = e;

                if (not in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }  // foreach in N[u]
    }      // while
}

int ford_fulkerson_1() {
    int answer = 0;

    while (true) {
        SPFA_1();

        if (dist[t] == INFTY) {
            break;
        }

        int minflow = INFTY;
        int x = t;
        while (edge[x]) {
            minflow = min(minflow, edge[x]->remaining());

            x = edge[x]->from;
        }  // while

        answer += dist[t];
        x = t;
        while (edge[x]) {
            Edge *e = edge[x];

            e->flow += minflow;
            e->reverse_edge->flow -= minflow;

            x = e->from;
        }  // while
    }      // while

    return answer;
}

void SPFA_2() {
    for (int i = s; i <= t; i++) {
        dist[i] = INFTY;
        edge[i] = NULL;
        in_queue[i] = false;
    }  // for
    dist[s] = 0;

    queue<int> q;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (auto e : N[u]) {
            int v = e->to;

            if (e->remaining() == 0) {
                continue;
            }

            if (dist[u] + e->cost < dist[v]) {
                dist[v] = dist[u] + e->cost;
                edge[v] = e;

                if (not in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }  // foreach in N[u]
    }      // while
}

int ford_fulkerson_2() {
    int answer = 0;

    while (true) {
        SPFA_2();

        if (dist[t] == INFTY) {
            break;
        }

        int minflow = INFTY;
        int x = t;
        while (edge[x]) {
            minflow = min(minflow, edge[x]->remaining());

            x = edge[x]->from;
        }  // while

        answer += dist[t];
        x = t;
        while (edge[x]) {
            Edge *e = edge[x];

            e->flow += minflow;
            e->reverse_edge->flow -= minflow;

            x = e->from;
        }  // while
    }      // while

    return -answer;
}
