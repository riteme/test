/**
 * Popular Cows
 * tags: 强连通分量
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 10000

static int n;
static int m;
static vector<int> G[NMAX + 10];
static int dfsCount = 1;
static int sccCount = 0;
static int dfn[NMAX + 10];
static int low[NMAX + 10];
static stack<int> stk;
static int scc[NMAX + 10];
static int size[NMAX + 10];
static bool hasout[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        G[x].push_back(y);
    }  // for

    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(scc, 0, sizeof(scc));
    memset(size, 0, sizeof(size));
    memset(hasout, false, sizeof(hasout));
}

void tarjan_scc(int u) {
    dfn[u] = low[u] = dfsCount++;
    stk.push(u);

    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (dfn[v] == 0) {
            tarjan_scc(v);
            low[u] = min(low[u], low[v]);
        } else if (scc[v] == 0) {
            low[u] = min(low[u], dfn[v]);
        }
    }  // for

    if (dfn[u] == low[u]) {
        sccCount++;

        int x;
        do {
            x = stk.top();
            stk.pop();

            scc[x] = sccCount;
            size[sccCount]++;
        } while (x != u);  // do ... while
    }
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan_scc(i);
        }
    }  // for

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            int v = G[i][j];

            if (scc[i] != scc[v]) {
                hasout[scc[i]] = true;
            }
        }  // for
    }      // for

    /**
     * 缩点后的图为DAG，不可能存在环
     * 故出度为0的点就是答案
     * 但可能有**多个**出度为0的点，那么因该输出0......
     */
    int which = 0;
    int zerocnt = 0;
    for (int i = 1; i <= sccCount; i++) {
        if (!hasout[i]) {
            which = i;
            zerocnt++;
        }
    }  // for

    if (zerocnt == 1) {
        printf("%d", size[which]);
    } else {
        printf("0");
    }

    return 0;
}  // function main
