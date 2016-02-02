/**
 * 餐巾计划
 * tags: 单位最小费用流
 */

#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

#define NMAX 10000

using std::vector;
using std::queue;
using std::min;
using std::max;

typedef long long ntype;

struct Edge {
    ntype from;
    ntype to;
    ntype flow;
    ntype capacity;
    ntype cost;
    Edge *reverse_edge;

    ntype reserve() const {
        return capacity - flow;
    }
};  // struct Edge

static ntype n, p;
static ntype nfast, pfast;
static ntype nslow, pslow;
static ntype need[NMAX + 10];
static ntype s, t;
static vector<Edge *> G[NMAX + 10];
static ntype dist[NMAX + 10];
static Edge *edge[NMAX + 10];
static bool in_queue[NMAX + 10];  // 防重复优化
static ntype answer = 0;

void initialize();
void spfa();
void ford_fulkerson();

int main() {
    freopen("napk.in", "r", stdin);
    freopen("napk.out", "w", stdout);
    initialize();

    ford_fulkerson();

    printf("%lld", answer);

    fcloseall();
    return 0;
}  // function main

inline void add_edge(ntype u, ntype v, ntype capacity, ntype cost) {
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
    scanf("%lld%lld%lld%lld%lld%lld", &n, &p, &nfast, &pfast, &nslow, &pslow);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", need + i);
    }  // for

    s = 0;
    t = n * 2 + 1;

    for (int i = 1; i <= n; i++) {
        add_edge(s, i, need[i], p);
        add_edge(s, i + n, need[i], 0);
        add_edge(i, t, need[i], 0);

        if (i + nfast <= n) {
            add_edge(i + n, i + nfast, INT_MAX, pfast);
        }

        if (i + nslow <= n) {
            add_edge(i + n, i + nslow, INT_MAX, pslow);
        }

        if (i + 1 <= n) {
            add_edge(i + n, i + n + 1, INT_MAX, 0);
        }
    }  // for

    // for (int i = s; i <= t; i++) {
    //     for (auto &e : G[i]) {
    //         if (e->reserve() > 0) {
    //             printf("(%lld, %lld, capacity = %lld, cost = %lld)\n",
    //             e->from,
    //                    e->to, e->capacity, e->cost);
    //         }
    //     }  // foreach in G[i]
    // }      // for
}

void spfa() {
    for (int i = s; i <= t; i++) {
        dist[i] = INT_MAX;
        edge[i] = NULL;
        in_queue[i] = false;
    }  // for
    dist[s] = 0;

    queue<ntype> q;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        ntype u = q.front();
        q.pop();
        in_queue[u] = false;

        for (auto &e : G[u]) {
            ntype v = e->to;

            if (e->reserve() == 0) {
                continue;
            }

            if (dist[v] > dist[u] + e->cost) {
                dist[v] = dist[u] + e->cost;
                edge[v] = e;

                if (not in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }  // foreach in G[u]
    }      // while
}

void ford_fulkerson() {
    answer = 0;

    while (true) {
        spfa();

        if (dist[t] == INT_MAX) {
            return;
        }

        ntype minflow = INT_MAX;
        int x = t;
        while (edge[x] != NULL) {
            minflow = min(edge[x]->reserve(), minflow);
            x = edge[x]->from;
        }  // while

        x = t;
        while (edge[x] != NULL) {
            Edge *e = edge[x];

            answer += minflow * e->cost;

            // printf("(%lld, %lld)\n", e->from, e->to);
            // printf("answer += %lld\n", minflow * e->cost);

            e->flow += minflow;
            e->reverse_edge->flow -= minflow;

            x = e->from;
        }  // while
    }      // while
}
