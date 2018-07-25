#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 20000
#define MMAX 200000

typedef long long int64;

struct Edge {
    int from;
    int to;
    int64 capacity;
    Edge *reverse_edge;
};

static size_t pos;
static Edge memory[4000000];

inline Edge *allocate() {
    return &memory[pos++];
}

static int n, m;
static int s, t;
static vector<Edge *> G[NMAX + 10];

inline void add_edge(int u, int v, int64 capacity) {
//    Edge *e = new Edge;
//    Edge *re = new Edge;
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

static void initialize() {
    scanf("%d%d", &n, &m);

    s = n + 1;
    t = n + 2;
    for (int i = 1; i <= n; i++) {
	int64 a, b;
	scanf("%lld%lld", &a, &b);

	add_edge(s, i, a);
	add_edge(i, t, b);
    }

    for (int i = 0; i < m; i++) {
	int a, b;
	int64 w;
	scanf("%d%d%lld", &a, &b, &w);

	add_edge(a, b, w);
	add_edge(b, a, w);
    }
}

static int level[NMAX+10];
static size_t current_index[NMAX+10];

static void bfs() {
    memset(level, 0, sizeof(level));

    queue<int> q;
    q.push(s);
    level[s] = 1;

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

static int64 dfs(int x, int64 maxflow) {
    if (x == t)
	return maxflow;

    int64 current = 0;
    for (size_t &i = current_index[x]; i < G[x].size(); i++) {
//    for (size_t i = 0; i < G[x].size(); i++) {
	Edge *e = G[x][i];
	int v = e->to;

	if (level[v] != level[x] + 1 || e->capacity == 0)
	    continue;
	
	int64 flow = min(maxflow - current, e->capacity);
	flow = dfs(v, flow);
	e->capacity -= flow;
	e->reverse_edge->capacity += flow;
	current += flow;

	if (current == maxflow)
	    break;
    }

    return current;
}

static int64 dinic() {
    int64 answer = 0;

    while (true) {
	bfs();

	if (!level[t])
	    break;
	
	memset(current_index, 0, sizeof(current_index));
	answer += dfs(s, LLONG_MAX);
    }

    return answer;
}

int main() {
    initialize();

    printf("%lld\n", dinic());

    return 0;
}
