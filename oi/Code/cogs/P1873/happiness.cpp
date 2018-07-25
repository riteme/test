#include <cstdio>
#include <cstring>
#include <climits>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define EPSILON 0.0000001

template <typename T>
inline bool almost_equal(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

#define NMAX 100

struct Edge {
    int from;
    int to;
    double capacity;
    Edge *reverse_edge;
};

static int n, m;
static int s, t;
static double sum;
static vector<Edge *> G[NMAX * NMAX + 10];
static int matrix[NMAX + 10][NMAX + 10];

inline void add_edge(int u, int v, double w) {
    Edge *e = new Edge;
    Edge *re = new Edge;

    e->from = u;
    e->to = v;
    e->capacity = w;
    e->reverse_edge = re;
    re->from = v;
    re->to = u;
    re->capacity = 0.0;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);
}

static void initialize() {
    scanf("%d%d", &n, &m);

    s = n * m + 1;
    t = n * m + 2;
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < m; j++) {
	    int v;
	    scanf("%d", &v);
	    sum += v;

	    add_edge(s, i * n + j, v);
	}
    }

    for (int i = 0; i < n; i++) {
	for (int j = 0; j < m; j++) {
	    int v;
	    scanf("%d", &v);
	    sum += v;

	    add_edge(i * n + j, t, v);
	}
    }

    for (int i = 0; i < n - 1; i++) {
	for (int j = 0; j < m; j++) {
	    int v;
	    scanf("%d", &v);
	    sum += v;
	    matrix[i][j] = v;
    
	    add_edge(s, i * n + j, v / 2.0);
	    add_edge(s, (i + 1) * n + j, v / 2.0);
	}
    }

    for (int i = 0; i < n - 1; i++) {
	for (int j = 0; j < m; j++) {
	    int v;
	    scanf("%d", &v);
	    sum += v;
	    matrix[i][j] += v;

	    add_edge(i * n + j, t, v / 2.0);
	    add_edge((i + 1) * n + j, t, v / 2.0);
	    add_edge(i * n + j, (i + 1) * n + j, matrix[i][j] / 2.0);
	    add_edge((i + 1) * n + j, i * n + j, matrix[i][j] / 2.0);
	}
    }

    memset(matrix, 0, sizeof(matrix));

    for (int i = 0; i < n; i++) {
	for (int j = 0; j < m - 1; j++) {
	    int v;
	    scanf("%d", &v);
	    sum += v;
	    matrix[i][j] = v;
    
	    add_edge(s, i * n + j, v / 2.0);
	    add_edge(s, i * n + (j + 1), v / 2.0);
	}
    }

    for (int i = 0; i < n; i++) {
	for (int j = 0; j < m - 1; j++) {
	    int v;
	    scanf("%d", &v);
	    sum += v;
	    matrix[i][j] += v;

	    add_edge(i * n + j, t, v / 2.0);
	    add_edge(i * n + (j + 1), t, v / 2.0);
	    add_edge(i * n + j, i * n + (j + 1), matrix[i][j] / 2.0);
	    add_edge(i * n + (j + 1), i * n + j, matrix[i][j] / 2.0);
	}
    }
}

static int level[NMAX * NMAX + 10];

static bool bfs() {
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

	    if (level[v] || almost_equal(e->capacity, 0.0))
		continue;

	    level[v] = level[u] + 1;
	    q.push(v);
	}
    }

    return level[t];
}

static size_t current_index[NMAX * NMAX + 10];

static double dfs(int x, double maxflow) {
    if (x == t)
	return maxflow;

    double current = 0.0;
    for (size_t &i = current_index[x]; i < G[x].size(); i++) {
	Edge *e = G[x][i];
	int v = e->to;

	if (level[x] + 1 != level[v] || almost_equal(e->capacity, 0.0))
	    continue;
	
	double flow = min(maxflow - current, e->capacity);
	flow = dfs(v, flow);
	e->capacity -= flow;
	e->reverse_edge->capacity += flow;
	current += flow;

	if (current >= maxflow)
	    break;
    }

    return current;
}

static double dinic() {
    double answer = 0.0;

    while(bfs()) {
	memset(current_index, 0, sizeof(current_index));
	answer += dfs(s, INT_MAX);
    }

    return answer;
}

int main() {
    freopen("nt2011_happiness.in", "r", stdin);
    freopen("nt2011_happiness.out", "w", stdout);
    initialize();

    double answer = sum - dinic();
    printf("%d\n", int(answer + 0.5));

    fclose(stdin);
    fclose(stdout);
    return 0;
}
