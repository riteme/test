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

static int m, n;
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
    freopen("trans.in", "r", stdin);
    freopen("trans.out", "w", stdout);
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
    scanf("%d%d", &m, &n);

    s = 0;
    t = m + n + 1;

    for (int i = 1; i <= m; i++) {
        int a;
        scanf("%d", &a);

        add_edge(G, s, i, a, 0);
        add_edge(N, s, i, a, 0);
    }  // for

    for (int i = m + 1; i <= m + n; i++) {
        int a;
        scanf("%d", &a);

        add_edge(G, i, t, a, 0);
        add_edge(N, i, t, a, 0);
    }  // for

    for (int i = 1; i <= m; i++) {
        for (int j = m + 1; j <= m + n; j++) {
            int a;
            scanf("%d", &a);

            add_edge(G, i, j, INFTY, a);
            add_edge(N, i, j, INFTY, -a);
        }  // for
    }      // for
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

        answer += dist[t] * minflow;
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

        answer += dist[t] * minflow;
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
