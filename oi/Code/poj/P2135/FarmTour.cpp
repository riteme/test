/**
 * Farm Tour
 * tags: 最小费用流
 * remark:
 *     1. 将无向边变为两条反向边,容量为1
 *     2. 建立源点，到1的容量为2，花费为0
 *     3. 类似的方法建汇点
 *     之所以源点和汇点容量为2，是因为要找两条最短路
 *     每条边的容量为1是因为一条边只能走一次
 */

// #include <bits/stdc++.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <cassert>
#include <queue>
#include <vector>
#include <algorithm>

using std::vector;
using std::queue;
using std::min;

#define NDEBUG

#define NMAX 1000
#define MMAX 10000

struct Edge {
    int from;
    int to;
    int capacity;
    int cost;
    Edge *reverse_edge;
};  // struct Edge

static int n, m;
static int s, t;
static vector<Edge *> G[NMAX + 10];
static int answer = 0;
static int dist[NMAX + 10];
static Edge *edge[NMAX + 10];

void initialize();

void spfa();

void compute_maxflow();

int main() {
    initialize();

    compute_maxflow();

    printf("%d", answer);

    return 0;
}  // function main

inline void add_edge(int u, int v, int capacity, int w) {
    Edge *e = NULL, *re = NULL;
    e = new Edge();
    re = new Edge();

    assert(e != NULL);
    assert(re != NULL);

    e->from = u;
    e->to = v;
    e->capacity = capacity;
    e->cost = w;
    e->reverse_edge = re;

    re->from = v;
    re->to = u;
    re->capacity = 0;
    re->cost = -w;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    scanf("%d%d", &n, &m);
    s = 0;
    t = n + 1;

    while (m > 0) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        add_edge(u, v, 1, w);
        add_edge(v, u, 1, w);

        m--;
    }  // while

    add_edge(s, 1, 2, 0);
    add_edge(n, t, 2, 0);
}

void spfa() {
    for (int i = 0; i <= t; i++) {
        dist[i] = INT_MAX;
        edge[i] = NULL;
    }  // for

    dist[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];

            if (e->capacity == 0) {
                continue;
            }

            int v = e->to;
            if (dist[v] > dist[u] + e->cost) {
                dist[v] = dist[u] + e->cost;
                edge[v] = e;
                q.push(v);
            }
        }  // for
    }      // while
}

void compute_maxflow() {
    while (true) {
        spfa();

        if (edge[t] == NULL) {
            return;
        }

        int x = t;
        int flow = INT_MAX;
        while (edge[x] != NULL) {
            Edge *e = edge[x];
            flow = min(flow, e->capacity);
            x = e->from;
        }  // while

        x = t;
        while (edge[x] != NULL) {
            Edge *e = edge[x];
            e->capacity -= flow;
            e->reverse_edge->capacity += flow;
            x = e->from;
        }  // while

        answer += dist[t];
    }  // while
}
