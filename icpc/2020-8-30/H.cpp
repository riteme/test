#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

int n, m, q, cnt;
vector<int> G[NMAX + 10], T[NMAX + 10];

struct Pair {
    Pair() {}
    Pair(int _u, int _v) : u(_u), v(_v) {}

    int u, v;
};

stack<Pair> stk;
int ecnt;
bool marked[NMAX + 10];
int idx[NMAX + 10];
int in[NMAX + 10], low[NMAX + 10], cur;
void bcc(int u, int f = 0) {
    idx[u] = ecnt;
    in[u] = low[u] = ++cur;
    for (int v : G[u]) {
        if (v == f) f = 0;
        else if (in[v])
            low[u] = min(low[u], in[v]);
        else {
            stk.push(Pair(u, v));
            bcc(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > in[u]) {
                cnt++;
                int p = n + cnt;
                T[u].push_back(p);
                T[p].push_back(u);
                T[v].push_back(p);
                T[p].push_back(v);
                stk.pop();
            } else if (low[v] >= in[u]) {
                cnt++;
                int linked = 0, p = n + cnt;
                auto add = [p, &linked](int x) {
                    if (!marked[x]) {
                        marked[x] = true;
                        T[p].push_back(x);
                        T[x].push_back(p);
                        linked++;
                    }
                };
                while (!stk.empty()) {
                    Pair x = stk.top();
                    stk.pop();
                    add(x.v);
                    add(x.u);
                    if (x.u == u && x.v == v)
                        break;
                }
                for (int v : T[p])
                    marked[v] = false;
                if (linked == 0)
                    cnt--;
            }
        }
    }
}

int sum[NMAX + 10];
int top[NMAX + 10], dep[NMAX + 10], pa[NMAX + 10];

void dfs(int x, int p) {
    sum[x] += x > n ? T[x].size() : -1;
    top[x] = 1;
    for (int i = 0; i < T[x].size(); i++) {
        int v = T[x][i];
        if (v == p)
            continue;
        dep[v] = dep[x] + 1;
        pa[v] = x;
        sum[v] = sum[x];
        dfs(v, x);
        top[x] += top[v];
    }
}

void decompose(int x, int p) {
    int u = 0;
    for (int i = 0; i < T[x].size(); i++) {
        int v = T[x][i];
        if (v != p && top[v] > top[u])
            u = v;
    }
    if (u) {
        top[u] = top[x];
        decompose(u, x);
    }
    for (int i = 0; i < T[x].size(); i++) {
        int v = T[x][i];
        if (v == p || v == u)
            continue;
        top[v] = v;
        decompose(v, x);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = pa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

void _main() {
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u++;
        v++;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            ecnt++;
            bcc(i);

            sum[i] = 0;
            dep[i] = 0;
            pa[i] = 0;
            top[i] = 0;
            dfs(i, 0);
            top[i] = i;
            decompose(i, 0);
        }
    }

    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        u++;
        v++;
        if (idx[u] != idx[v])
            printf("%d\n", n);
        else {
            int p = lca(u, v);
            int ans = sum[u] + sum[v] - sum[p] - sum[pa[p]];
            ans = n - (ans + 2);
            printf("%d\n", ans);
        }
    }
    puts("");

    memset(in + 1, 0, sizeof(int) * (n + cnt));
    memset(low + 1, 0, sizeof(int) * (n + cnt));
    for (int i = 1; i <= n + cnt; i++) {
        G[i].clear();
        T[i].clear();
    }
    cnt = cur = ecnt = 0;
    while (!stk.empty()) {
        stk.pop();
    }
}

int main() {
    int t = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        t++;
        printf("Case #%d:\n", t);
        _main();
    }
    return 0;
}
