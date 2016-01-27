/**
 * Network of Schools
 * tags: 强连通分量
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

#define NMAX 100

static int n;
static vector<int> G[NMAX + 10];
static int cnt;
static int dfn[NMAX + 10];
static int low[NMAX + 10];
static stack<int> s;
static int scccnt;
static int scc[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];

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
    memset(in, 0, sizeof(in));

    cnt = 1;
    scccnt = 0;
}

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

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan_scc(i);
        }
    }  // for

    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", scc[i]);
    // }  // for
    // printf("\n");

    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            int v = G[i][j];

            if (scc[i] != scc[v]) {
                in[scc[v]]++;
                out[scc[i]]++;
            }
        }  // for
    }      // for

    int i = 0, o = 0;
    if (scccnt != 1) {
        i = count(in + 1, in + scccnt + 1, 0);
        o = count(out + 1, out + scccnt + 1, 0);
    } else {
        printf("1\n0\n");

        return 0;
    }

    printf("%d\n%d\n", i, max(i, o));

    return 0;
}  // function main
