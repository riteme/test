// FUCK GCC
// `-finline-functions` makes my program receiving SIGSEGV,
// which is enabled by `-O3`
#pragma GCC optimize(2)

#define NDEBUG

#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define DEBUG(msg, ...) printf(msg, __VA_ARGS__);
#else
#define DEBUG(...)
#endif

typedef long long i64;

#define NMAX 200000

struct Edge {
    int u, v, t;
};

static int n, m, cnt, dfn[NMAX + 10], col[NMAX + 10];
static bool mark[NMAX + 10];
static vector<int> G[NMAX + 10], T[NMAX + 10];
static vector<int> B[NMAX + 10];
static vector<Edge> E[NMAX + 10];
static i64 f[NMAX + 10][2], ans[NMAX + 10][2];

void bcc(int x, int p) {
    static int cur, low[NMAX + 10];
    static stack<Edge> stk;
    dfn[x] = low[x] = ++cur;
    // DEBUG("enter %d [dfn = %d]\n", x, dfn[x]);
    mark[x] = true;

    for (int v : G[x]) {
        if (v == p) continue;
        if (!dfn[v]) {
            bcc(v, x);
            if (mark[v]) continue;
            if (dfn[v] == low[v]) {
                DEBUG("cut: %d - %d\n", x, v);
                T[x].push_back(v);
                T[v].push_back(x);
            } else stk.push({x, v, low[v]});
            if (low[v] == dfn[x]) {
                mark[x] = false;
                cnt++;
                DEBUG("bcc %d:", cnt);
#define ADD(x) \
                    if (!mark[x]) { \
                        mark[x] = true; \
                        B[cnt].push_back(x); \
                        DEBUG(" %d", x); \
                    }
                do {
                    Edge e = stk.top();
                    stk.pop();
                    E[cnt].push_back(e);
                    ADD(e.u);
                    ADD(e.v);
                } while (!stk.empty() && stk.top().t >= dfn[x]);
                DEBUG("%s", "\n");
            }
        }
        if (mark[v]) low[x] = min(low[x], dfn[v]);
        else low[x] = min(low[x], low[v]);
    }

    mark[x] = false;
    // DEBUG("leave %d [low = %d]\n", x, low[x]);
}

bool dfs(int x) {
    for (int v : G[x]) {
        if (!mark[v]) continue;
        if (col[v] && col[v] == col[x]) return false;
        else if (!col[v]) {
            col[v] = -col[x];
            if (!dfs(v)) return false;
        }
    }
    return true;
}

void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

void dp(int x) {
    mark[x] = true;
    f[x][0] = 1;
    for (int v : T[x]) {
        if (mark[v]) continue;
        dp(v);
        ans[x][0] += f[x][0] * f[v][1] + f[x][1] * f[v][0];
        ans[x][1] += f[x][0] * f[v][0] + f[x][1] * f[v][1];
        f[x][0] += f[v][1];
        f[x][1] += f[v][0];
    }
}

int main() {
    initialize();
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) bcc(i, 0);
    memset(mark, 0, sizeof(mark));
    for (int i = 1; i <= cnt; i++) {
        for (int x : B[i]) {
            col[x] = 0;
            mark[x] = true;
        }
        col[B[i][0]] = 1;
        if (dfs(B[i][0])) {
            for (auto &e : E[i]) {
                T[e.u].push_back(e.v);
                T[e.v].push_back(e.u);
            }
        }
        for (int x : B[i]) mark[x] = false;
    }

    i64 eans = 0, oans = 0;
    for (int i = 1; i <= n; i++) {
        if (!mark[i]) dp(i);
        eans += ans[i][0];
        oans += ans[i][1];
    }
    printf("%lld %lld\n", eans, oans);

    return 0;
}
