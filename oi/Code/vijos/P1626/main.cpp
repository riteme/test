#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define NMAX 1000

static int n, m;
static vector<int> G[NMAX + 1];
static vector<int> GT[NMAX + 1];
static bool marked[NMAX + 1];
static int now;
static int finish[NMAX + 1];
static int scc[NMAX + 1];
static int nodecnt;
static int target;

inline void initialize() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        G[u].push_back(v);
        GT[v].push_back(u);
    }  // for

    nodecnt = 0;
    target = -1;
    now = 0;
}

inline void quit() { printf("%d\n", nodecnt); }

void generate_finish(int x) {
    marked[x] = true;

    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            generate_finish(v);

            finish[v] = now;
        }
    }  // for

    now++;
}

void generate_scc(int x, int id) {
    marked[x] = true;
    scc[x] = id;

    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) generate_scc(x, id);
    }  // for
}

int main() {
    initialize();

    memset(marked, 0, sizeof(marked));
    for (int i = 1; i <= n; i++) {
        if (!marked[i]) generate_finish(i);
    }  // for

    memset(marked, 0, sizeof(marked));
    for (int i = 1; i <= n; i++) {
        if (!marked[i]) {
            generate_scc(i, nodecnt);
            nodecnt++;
        }
    }  // for

    quit();
    return 0;
}  // function main
