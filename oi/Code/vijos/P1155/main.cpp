#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200
#define INFTY 3000000000.0

struct Edge {
    Edge() : u(0), v(0) {}
    Edge(int _u, int _v) : u(_u), v(_v) {}

    int u;
    int v;
};  // struct Edge

static int n;
static int m;
static double x[NMAX + 10];
static double y[NMAX + 10];
static double W[NMAX + 10][NMAX + 10];
static vector<int> G[NMAX + 10];
static double dist[NMAX + 10];
static int edgeTo[NMAX + 10];
static vector<Edge> edgeList;
static double answer;

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", x + i, y + i);
    }  // for

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        W[u][v] = W[v][u] =
            sqrt((x[u] - x[v]) * (x[u] - x[v]) + (y[u] - y[v]) * (y[u] - y[v]));

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    answer = INFTY;
}

double spfa(int s, int t) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INFTY;
    }  // for
    dist[s] = 0.0;
    edgeTo[s] = s;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (dist[v] > dist[u] + W[u][v]) {
                dist[v] = dist[u] + W[u][v];
                edgeTo[v] = u;

                q.push(v);
            }
        }  // for
    }      // while

    return dist[t];
}

int main() {
    initialize();

    double minlength = spfa(1, n);
    if (minlength >= INFTY) {
        printf("-1");
        return 0;
    }

    int node = n;
    while (node != 1) {
        edgeList.push_back(Edge(node, edgeTo[node]));

        node = edgeTo[node];
    }  // while

    for (int i = 0; i < edgeList.size(); i++) {
        int u = edgeList[i].u;
        int v = edgeList[i].v;
        double origin = W[u][v];
        W[u][v] = W[v][u] = INFTY;

        double length = spfa(1, n);
        if (length < answer) {
            answer = length;
        }

        W[u][v] = W[v][u] = origin;
    }  // for

    if (answer >= INFTY) {
        printf("-1");
    } else {
        printf("%.2lf", answer);
    }

    return 0;
}  // function main
