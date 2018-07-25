#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

#define NMAX 1000
#define MMAX 5000

struct Edge {
    int id;
    int from;
    int to;
    int w;
};  // struct Edge

static int n, m;
static Edge edges[MMAX + 10];
static vector<Edge *> out[NMAX + 10];
static bool marked[MMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        edges[i].id = i;
        edges[i].from = u;
        edges[i].to = v;
        edges[i].w = w;
        out[u].push_back(edges + i);
    }
}

int dfs();

int walk(int x, int sum) {
    int answer = 0;

    for (size_t i = 0; i < out[x].size(); i++) {
        Edge *e = out[x][i];

        if (marked[e->to])
            continue;

        marked[e->to] = true;
        int result = dfs() + e->w + sum;
        answer = max(answer, result);
        answer = max(answer, walk(e->to, sum + e->w));
        marked[e->to] = false;
    }

    return answer;
}

int dfs() {
    int answer = 0;

    for (int i = 1; i <= n; i++) {
        if (marked[i])
            continue;

        marked[i] = true;
        answer = max(answer, walk(i, 0));
        marked[i] = false;
    }

    return answer;
}

int main() {
    initialize();

    printf("%d\n", dfs());

    return 0;
}  // function main
