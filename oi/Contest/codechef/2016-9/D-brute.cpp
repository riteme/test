#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define NMAX 1000
// #define NMAX 100

static int n, m;
static bool W[NMAX + 10][NMAX + 10];

static void initialize() {
    memset(W, 0, sizeof(W));

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        W[a][b] = W[b][a] = true;
    }  // for

    for (int i = 1; i <= n; i++) {
        W[i][i] = true;
    }  // for
}

static vector<int> G[NMAX * 2 + 10];

static void construct_graph() {
    for (int i = 1; i <= n * 2; i++) {
        G[i].clear();
    }  // for

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!W[i][j]) {
                G[i].push_back(j + n);
                G[j].push_back(i + n);
                G[i + n].push_back(j);
                G[j + n].push_back(i);
            }
        }  // for
    }      // for
}

static int timestamp;
static int dfn[NMAX * 2 + 10];
static int low[NMAX * 2 + 10];
static bool marked[NMAX * 2 + 10];
static stack<int> stk;

static void scc(int x) {
    if (dfn[x])
        return;
    dfn[x] = low[x] = ++timestamp;
    stk.push(x);

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!dfn[v])
            scc(v);
        if (!marked[v])
            low[x] = min(low[x], low[v]);
    }  // for

    if (dfn[x] == low[x]) {
        while (true) {
            int u = stk.top();
            stk.pop();

            marked[u] = true;

            if (u == x)
                break;
        }  // while
    }
}

static void scc() {
    timestamp = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(marked, 0, sizeof(marked));

    for (int i = 1; i <= n * 2; i++) {
        if (!dfn[i])
            scc(i);
    }  // for
}

static bool test(int selected) {
    vector<int> A;
    vector<int> B;

    for (int i = 1; i <= n; i++) {
        if (selected & (1 << (i - 1)))
            A.push_back(i);
        else
            B.push_back(i);
    }  // for

    for (int i = 0; i < A.size(); i++) {
        int u = A[i];
        for (int j = 0; j < A.size(); j++) {
            if (!W[u][A[j]])
                return false;
        }  // for
    }      // for

    for (int i = 0; i < B.size(); i++) {
        int u = B[i];
        for (int j = 0; j < B.size(); j++) {
            if (!W[u][B[j]])
                return false;
        }  // for
    }      // for

    return true;
}

static bool brute() {
    int selected = 1;

    for (; selected < 1 << (n + 1); selected++) {
        if (test(selected))
            return true;
    }  // for

    return false;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        bool flag = true;

        flag = brute();

        if (flag)
            puts("YES");
        else
            puts("NO");
    }  // while

    return 0;
}  // function main
