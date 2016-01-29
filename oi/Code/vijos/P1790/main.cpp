#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static int m;
static vector<int> G[NMAX + 10];
static int level[NMAX + 10];
static vector<int> topo;
static vector<int> topoLevel[NMAX + 10];
static int in[NMAX + 10];
static int a[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    memset(level, 0, sizeof(level));
    memset(in, 0, sizeof(in));

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        G[x].push_back(y);
        in[y]++;
    }  // for
}

void topological_sort() {
    in[0] = INT_MAX;

    while (topo.size() < n) {
        int v = 0;
        for (int i = 1; i <= n; i++) {
            if (in[i] < in[v]) {
                v = i;
            }
        }  // for

        for (int i = 0; i < G[v].size(); i++) {
            in[G[v][i]]--;
        }  // for

        topo.push_back(v);
        in[v] = INT_MAX;
    }  // while
}

int main() {
    initialize();

    topological_sort();

    for (int i = 0; i < topo.size(); i++) {
        int u = topo[i];

        topoLevel[level[u]].push_back(u);

        for (int j = 0; j < G[u].size(); j++) {
            int v = G[u][j];

            level[v] = max(level[v], level[u] + 1);
        }  // for
    }      // for

    int ncnt = 1;
    for (int i = 0; topoLevel[i].size() > 0; i++) {
        sort(topoLevel[i].begin(), topoLevel[i].end());

        for (int j = 0; j < topoLevel[i].size(); j++) {
            a[topoLevel[i][j]] = ncnt++;
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }  // for

    return 0;
}  // function main
