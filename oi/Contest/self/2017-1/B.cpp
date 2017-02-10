#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t pos = BUFFERSIZE;
static char buffer[BUFFERSIZE];

inline char _getchar() {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buffer, 1, BUFFERSIZE, stdin);
    }

    return buffer[pos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c)) {
        c = _getchar();
    }

    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 30000
#define MMAX 50000

struct Edge {
    int id;
    int to;
    int capacity;
    int next;
};

static int n, m, k;
static int s, t;
static int head[NMAX * 2 + 10];
static int mcnt;
static Edge edges[MMAX * 4 + NMAX * 2 + 100];

inline void add_edge(int u, int v, int capacity) {
    Edge &e = edges[mcnt];
    Edge &re = edges[mcnt + 1];

    e.id = mcnt;
    e.to = v;
    e.capacity = capacity;
    e.next = head[u];
    head[u] = e.id;

    re.id = mcnt + 1;
    re.to = u;
    re.capacity = 0;
    re.next = head[v];
    head[v] = re.id;

    mcnt += 2;
}

static void initialize() {
    // scanf("%d%d%d", &n, &m, &k);
    n = readint();
    m = readint();
    k = readint();
    s = n * 2 + 1;
    t = n * 2 + 2;

    memset(head, 0, sizeof(head));
    mcnt = 2;

    for (int i = 1; i <= n; i++) {
        if (i == k)
            add_edge(i, i + n, 2);
        else
            add_edge(i, i + n, 1);
    }

    add_edge(s, k, 2);
    add_edge(1 + n, t, 1);
    add_edge(n + n, t, 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = readint();
        v = readint();

        add_edge(u + n, v, 1);
        add_edge(v + n, u, 1);
    }
}

static bool marked[NMAX * 2 + 10];
static int level[NMAX * 2 + 10];
static int qhead, qtail;
static int que[NMAX * 2 + 100];

static void bfs() {
    memset(marked, 0, sizeof(marked));
    memset(level, 0, sizeof(level));

    qhead = 0;
    qtail = 0;
    marked[s] = true;
    que[qtail++] = s;

    while (qhead != qtail) {
        int u = que[qhead++];

        for (int i = head[u]; i; i = edges[i].next) {
            Edge &e = edges[i];
            int v = e.to;

            if (marked[v] || e.capacity == 0)
                continue;

            marked[v] = true;
            level[v] = level[u] + 1;
            que[qtail++] = v;
        }
    }
}

static int dfs(int x, int maxflow) {
    if (x == t)
        return maxflow;

    int current = 0;
    for (int i = head[x]; i; i = edges[i].next) {
        Edge &e = edges[i];
        int v = e.to;

        if (e.capacity == 0 || level[v] != level[x] + 1)
            continue;

        int flow = min(maxflow - current, e.capacity);
        flow = dfs(v, flow);
        e.capacity -= flow;
        edges[e.id ^ 1].capacity += flow;
        current += flow;

        if (current >= maxflow)
            break;
    }

    return current;
}

static int dinic() {
    int answer = 0;

    while (true) {
        bfs();

        if (!marked[t])
            break;

        answer += dfs(s, INT_MAX);
    }

    return answer;
}

int main() {
    freopen("B.in", "r", stdin);
    int test;
    // scanf("%d", &test);
    test = readint();

    while (test--) {
        initialize();
        
        puts(dinic() == 2 ? "YES" : "NO");
    }

    return 0;
}
