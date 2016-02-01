/**
 * Uncommitted
 */

#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

#define NMAX 1000

struct Edge {
    int from;
    int to;
    int capacity;
    int cost;
    Edge *reverse_edge;
};  // struct Edge

static int n, p;
static int nfast, pfast;
static int nslow, pslow;
static int need[NMAX + 10];
static int s, t;
static int shop, fast, slow;
static vector<Edge *> G[NMAX + 10];
static int dist[NMAX + 10];
static Edge *edge[NMAX + 10];
static int answer = 0;

void initialize();
void spfa();
void ford_fulkerson();

int main() {
    // freopen("napk.in", "r", stdin);
    // freopen("napk.out", "w", stdout);
    initialize();

    ford_fulkerson();

    printf("%d", answer);

    fcloseall();
    return 0;
}  // function main

inline void add_edge(int u, int v, int capacity, int cost) {
    Edge *e = new Edge();
    Edge *re = new Edge();

    e->from = u;
    e->to = v;
    e->capacity = capacity;
    e->cost = cost;
    e->reverse_edge = re;

    re->from = v;
    re->to = u;
    re->capacity = 0;
    re->cost = -cost;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    scanf("%d%d%d%d%d%d", &n, &p, &nfast, &pfast, &nslow, &pslow);

    for (int i = 1; i <= n; i++) {
        scanf("%d", need + i);
    }  // for

    s = 0;
    shop = n + 1;
    fast = n + 2;
    slow = n + 3;
    t = n + 4;

    add_edge(s, shop, INT_MAX, p);

    for (int i = 1; i <= n; i++) {
        add_edge(i, t, INT_MAX, 0);

        // Buy new ones
        add_edge(shop, i, need[i], 0);

        // Send to fast washer
        if (i + nfast <= n) {
            add_edge(i, fast, need[i], pfast);
            add_edge(fast, i + nfast, need[i], 0);
        }

        // Send to slow washer
        if (i + nslow <= n) {
            add_edge(i, slow, need[i], pslow);
            add_edge(slow, i + nslow, need[i], 0);
        }
    }  // for
}

void spfa() {
    for (int i = s; i <= t; i++) {
        dist[i] = INT_MAX;
        edge[i] = NULL;
    }  // for
    dist[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &e : G[u]) {
            int v = e->to;

            if (e->capacity == 0) {
                continue;
            }

            if (dist[v] > dist[u] + e->cost) {
                dist[v] = dist[u] + e->cost;
                edge[v] = e;
                q.push(v);
            }
        }  // foreach in G[u]
    }      // while
}

void ford_fulkerson();
