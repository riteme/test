#include <vector>
#include <stack>

using namespace std;

#define SIZEMAX 100

static int n;
static vector<int> G[SIZEMAX + 10];
static int cnt;
static int dfn[SIZEMAX + 10];
static int low[SIZEMAX + 10];
static stack<int> s;
static int scccnt;
static int scc[SIZEMAX + 10];

// memset(dfn, 0, sizeof(dfn));
// memset(low, 0, sizeof(low));
// memset(in, 0, sizeof(in));
// cnt = 1;
// scccnt = 0;

void tarjan_scc(int u) {
    dfn[u] = low[u] = cnt++;
    s.push(u);

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
        int x;
        scccnt++;

        do {
            x = s.top();
            s.pop();
            scc[x] = scccnt;
        } while (u != x);  // do ... while
    }
}
