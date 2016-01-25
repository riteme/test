#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

#define NMAX 100

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u;
    int v;
    int w;

    bool operator<(const Edge &b) const {
        return w < b.w;
    }
};  // struct Edge

static int n;
static vector<int> G[NMAX + 10];
static int cnt;
static int scccnt;
static int dfn[NMAX + 10];
static int low[NMAX + 10];
static bool exist[NMAX + 10];
static stack<int> s;
static int W[NMAX + 10][NMAX + 10];
static int in[NMAX + 10];
static int scc[NMAX + 10];
static vector<Edge> edges;
static int set[NMAX + 10];
static int total;

inline void make_set(int size) {
    for (int i = 1; i <= size; i++) {
        set[i] = i;
    }  // for
}

inline int find_set(int x) {
    return x == set[x] ? x : set[x] = find_set(set[x]);
}

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int x;
        while (true) {
            scanf("%d", &x);

            if (x == 0) {
                break;
            }

            G[i].push_back(x);
        }  // while
    }      // for

    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(exist, false, sizeof(exist));
    memset(in, 0, sizeof(in));

    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            W[x][y] = 0;
        }  // for
    }      // for

    cnt = 1;
    scccnt = 0;
}

void tarjan_scc(int u) {
    dfn[u] = low[u] = cnt++;
    exist[u] = true;
    s.push(u);

    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (dfn[v] == 0 and scc[v] == 0) {
            tarjan_scc(v);
            low[u] = min(low[u], low[v]);
        } else if (exist[v]) {
            low[u] = min(low[v], dfn[v]);
        }
    }  // for

    if (dfn[u] == low[u]) {
        int x;
        scccnt++;

        do {
            x = s.top();
            exist[x] = false;
            s.pop();
            scc[x] = scccnt;
        } while (u != x);  // do ... while
    }
}

void kruskal() {
    make_set(scccnt);

    sort(edges.begin(), edges.end());

    int index = 0;
    int edgeCnt = 0;

    total = 0;
    while (edgeCnt < n - 1 and index < edges.size()) {
        Edge &e = edges[index];

        int x = find_set(e.u);
        int y = find_set(e.v);

        if (x != y) {
            set[x] = y;
            total += e.w;
            edgeCnt++;
        }

        index++;
    }  // while
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        if (low[i] == 0) {
            s = stack<int>();

            tarjan_scc(i);
        }
    }  // for

    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", scc[i]);
    // }  // for
    // printf("\n");

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            int v = G[i][j];

            if (scc[i] != scc[v] and W[scc[i]][scc[v]] == 0) {
                W[scc[i]][scc[v]] = 1;
                in[scc[v]]++;
            }
        }  // for
    }      // for

    for (int i = 1; i <= scccnt; i++) {
        for (int j = i + 1; j <= scccnt; j++) {
            int edgecnt = W[i][j] + W[j][i];

            edges.push_back(Edge(i, j, 2 - edgecnt));
        }  // for
    }      // for

    int zerocnt = 0;
    for (int i = 1; i <= scccnt; i++) {
        if (in[i] == 0) {
            zerocnt++;
        }
    }  // for

    kruskal();

    printf("%d\n%d\n", zerocnt, total);

    return 0;
}  // function main
