#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 5000
#define MMAX 50000
#define INFTY 1000000000

struct Edge {
    int from;
    int to;
    int capacity;
    Edge *reverse_edge;
};  // struct Edge

static int n, m;
static int sum;
static int s, t;
static vector<Edge *> G[NMAX + MMAX + 10];

inline void add_edge(int from, int to, int capacity) {
    Edge *e = new Edge;
    Edge *re = new Edge;

    e->from = from;
    e->to = to;
    e->capacity = capacity;
    e->reverse_edge = re;
    re->from = to;
    re->to = from;
    re->capacity = 0;
    re->reverse_edge = e;

    G[from].push_back(e);
    G[to].push_back(re);
}

static int level[NMAX + MMAX + 10];

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

static int dfs(int x, int maxflow) {
    if (x == t)
	return maxflow;

    int current = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
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

	if (!level[t])
	    break;
	
	answer += dfs(s, INFTY);
    }

    return answer;
}

static void initialize() {
    scanf("%d%d", &n, &m);

    s = n + m + 1;
    t = n + m + 2;
    for (int i = 1; i <= n; i++) {
	int v;
	scanf("%d", &v);

	add_edge(i + m, t, v);
    }

    for (int i = 1; i <= m; i++) {
	int a, b, v;
	scanf("%d%d%d", &a, &b, &v);

	sum += v;;
	add_edge(s, i, v);
	add_edge(i, a + m, INFTY);
	add_edge(i, b + m, INFTY);
    }
}

int main() {
    initialize();

    printf("%d\n", sum - dinic());

    return 0;
}
