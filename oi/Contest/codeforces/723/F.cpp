#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 200000

struct Edge {
    int from;
    int to;
    int capacity;
    Edge *reverse_edge;
};

static int n, m;
static int s, t, ds, dt;
static vector<int> N[NMAX + 10];
static int source, sink, gs, gt;
static int cnt[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

static int set[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
}

inline int find_set(int x) {
    return set[x] == x ? x : set[x] = find_set(set[x]);
}

inline void add_edge(int u, int v, int capacity) {
    Edge *e = new Edge;
    Edge *re = new Edge;

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

static int level[NMAX + 10];
static size_t current_index[NMAX + 10];

static void bfs() {
    memset(level, 0, sizeof(level));

    queue<int> q;
    q.push(source);
    level[source] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->to;

            if (level[v] || e->capacity == 0)
                continue;

            level[v] = level[u] + 1;
            q.push(v);
        }
    }
}

static int dfs(int x, int maxflow) {
    if (x == sink)
        return maxflow;

    int current = 0;
    for (size_t &i = current_index[x]; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (level[v] != level[x] + 1 || e->capacity == 0)
            continue;

        int flow = min(maxflow - current, e->capacity);
        flow = dfs(v, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current == maxflow)
            break;
    }

    return current;
}

static int dinic() {
    int answer = 0;

    while (true) {
        bfs();

        if (!level[sink])
            break;

        memset(current_index, 0, sizeof(current_index));
        answer += dfs(source, INT_MAX);
    }

    return answer;
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        N[u].push_back(v);
        N[v].push_back(u);
    }  // for

    scanf("%d%d%d%d", &s, &t, &ds, &dt);
}

static bool marked[NMAX + 10];

static void spanning(int x) {
    marked[x] = true;

    for (size_t i = 0; i < N[x].size(); i++) {
        int v = N[x][i];

        if (v == s || v == t || marked[v])
            continue;

        printf("%d %d\n", x, v);
        spanning(v);
    }  // for
}

int main() {
    initialize();

    make_set();
    for (int i = 1; i <= n; i++) {
        if (i == s || i == t)
            continue;

        for (size_t j = 0; j < N[i].size(); j++) {
            int v = N[i][j];

            if (v == s || v == t)
                continue;

            int a = find_set(i);
            int b = find_set(v);
            set[a] = b;
        }  // for
    }      // for

    source = n + 1;
    sink = n + 2;
    gs = n + 3;
    gt = n + 4;

    add_edge(source, gs, ds);
    add_edge(source, gt, dt);

    for (size_t i = 0; i < N[s].size(); i++) {
        int v = N[s][i];

        if (v == t) {
            add_edge(gs, t, 1);
            // add_edge(gt, s, 1);
        }
    }  // for

    for (size_t i = 0; i < N[gs].size(); i++) {
        cnt[find_set(N[gs][i])] = 1;
    }  // for

    for (int i = 1; i <= n; i++) {
        if (cnt[i])
            add_edge(gs, i, 1);
    }  // for

    memset(cnt, 0, sizeof(cnt));
    for (size_t i = 0; i < N[gt].size(); i++) {
        cnt[find_set(N[gt][i])] = 1;
    }  // for

    for (int i = 1; i <= n; i++) {
        if (cnt[i])
            add_edge(gt, i, 1);
    }  // for

    for (int i = 1; i <= n; i++) {
        add_edge(i, sink, 1);
    }  // for

    int answer = dinic();

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        if (i == s || i == t)
            continue;

        cnt[find_set(i)] = 1;
    }  // for

    int size = count(cnt + 1, cnt + n + 1, 1);

    if (answer < size)
        puts("No");
    else {
        puts("Yes");

        for (size_t i = 0; i < G[gs].size(); i++) {
            Edge *e = G[gs][i];
            if (1 <= e->to && e->to <= n) {
                if (e->capacity == 0)
                    printf("%d %d\n", s, e->to);
            }
        }  // for

        for (size_t i = 0; i < G[gt].size(); i++) {
            Edge *e = G[gt][i];
            if (1 <= e->to && e->to <= n) {
                if (e->capacity == 0)
                    printf("%d %d\n", t, e->to);
            }
        }  // for

        for (int i = 1; i <= n; i++) {
            if (i == s || i == t || marked[i])
                continue;

            spanning(i);
        }  // for
    }

    return 0;
}  // function main
