#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

struct Edge {
    int u;
    int v;
    int capacity;
    Edge *reverse_edge;
};  // struct Edge

static int n;
static int s, t;
static int maxlis;
static int answer;
static int num[NMAX + 10];
static int f[NMAX + 10];
static vector<int> map[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int level[NMAX + 10];
static bool marked[NMAX + 10];

void initialize();

void generate_lis();

void setup_flow_network();
void bfs();
int dfs(int u, int maxflow);
void dinic();

void rebuild_flow_network();

int main() {
    freopen("alis.in", "r", stdin);
    freopen("alis.out", "w", stdout);
    initialize();

    generate_lis();
    setup_flow_network();
    dinic();

    printf("%d\n%d\n", maxlis, answer);

    // 如果最长不下降序列长度为1,那么就只能抽出n个
    if (maxlis == 1) {
        printf("%d", n);
        return 0;
    }

    rebuild_flow_network();
    dinic();

    printf("%d", answer);

    fcloseall();
    return 0;
}  // function main

inline void add_edge(int u, int v, int capacity) {
    Edge *e = new Edge();
    Edge *re = new Edge();

    e->u = u;
    e->v = v;
    e->capacity = capacity;
    e->reverse_edge = re;

    re->u = v;
    re->v = u;
    re->capacity = 0;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);

    // printf("u = %d, v = %d, capacity = %d\n", u, v, capacity);
}

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", num + i);
    }  // for

    maxlis = 0;
    s = 0;
    t = n + 1;
}

void generate_lis() {
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++) {
            if (num[j] <= num[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }  // for

        map[f[i]].push_back(i);
        maxlis = max(maxlis, f[i]);
        // printf("%d ", f[i]);
    }  // for
    // printf("\n");
}

void bfs() {
    for (int i = s; i <= t; i++) {
        marked[i] = false;
        level[i] = INT_MAX;
    }  // for

    queue<int> q;
    q.push(s);
    marked[s] = true;
    level[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &e : G[u]) {
            if (not marked[e->v] and e->capacity != 0) {
                marked[e->v] = true;
                level[e->v] = level[u] + 1;
                q.push(e->v);
            }
        }  // foreach in G[u]
    }      // while
}

int dfs(int u, int maxflow) {
    if (u == t) {
        return maxflow;
    }

    int current = 0;
    for (auto &e : G[u]) {
        if (level[u] + 1 != level[e->v] or e->capacity == 0) {
            continue;
        }

        int flow = min(maxflow - current, e->capacity);
        flow = dfs(e->v, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current >= maxflow) {
            return maxflow;
        }
    }  // foreach in G{u}

    return current;
}

void dinic() {
    answer = 0;

    while (true) {
        bfs();

        if (level[t] == INT_MAX) {
            return;
        }

        answer += dfs(s, INT_MAX);
    }  // while
}

void setup_flow_network() {
    for (auto v : map[1]) {
        add_edge(0, v, 1);
    }  // foreach in map[1]

    for (auto u : map[maxlis]) {
        add_edge(u, t, 1);
    }  // foreach in map[maxlis]

    for (int i = 1; i < maxlis; i++) {
        for (auto u : map[i]) {
            for (auto v : map[i + 1]) {
                if (u >= v or num[u] > num[v]) {
                    continue;
                }

                add_edge(u, v, 1);
            }  // foreach in G[i+1]
        }      // foreach in G[i]
    }          // for
}

void rebuild_flow_network() {
    for (int i = s; i <= t; i++) {
        G[i].clear();
    }  // for

    for (auto v : map[1]) {
        if (v == 1 or v == n) {
            add_edge(0, v, INT_MAX);
        } else {
            add_edge(0, v, 1);
        }
    }  // foreach in map[1]

    for (auto u : map[maxlis]) {
        if (u == 1 or u == n) {
            add_edge(u, t, INT_MAX);
        } else {
            add_edge(u, t, 1);
        }
    }  // foreach in map[maxlis]

    for (int i = 1; i < maxlis; i++) {
        for (auto u : map[i]) {
            for (auto v : map[i + 1]) {
                if (u >= v or num[u] > num[v]) {
                    continue;
                }

                if (u != 1 and v == n) {
                    add_edge(u, v, INT_MAX);
                } else {
                    add_edge(u, v, 1);
                }
            }  // foreach in G[i+1]
        }      // foreach in G[i]
    }          // for
}
