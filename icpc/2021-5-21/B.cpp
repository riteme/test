#include <cstdio>
#include <cassert>
#include <cstring>

#include <set>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 600000;

int n, m;
int c[NMAX + 10];
set<int> G[NMAX + 10];
vector<int> ops;

void link(int u, int v) {
    G[u].insert(v);
    G[v].insert(u);
}

void del(int u) {
    ops.push_back(u);
    for (int v : G[u]) {
        G[v].erase(u);
    }
    G[u].clear();
}

void cdup() {
    ops.push_back(0);

    for (int i = 1; i <= n; i++) {
        int j = n + i;
        for (int v : G[i]) {
            G[j].insert(n + v);
        }
        link(i, j);
    }
}

bool test(int x, int t) {
    for (int v : G[x]) {
        if (c[v] != 0 && c[v] == t)
            return false;
    }
    return true;
}

void dfs(int x) {
    if (test(x, 1))
        c[x] = 1;
    else if (test(x, 2))
        c[x] = 2;
    else {
        assert(test(x, 3));
        c[x] = 3;
    }

    for (int v : G[x]) if (c[v] == 0) {
        dfs(v);
    }
}

bool in[NMAX + 10];

void trim(int N) {
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (G[i].size() & 1) {
            in[i] = true;
            q.push(i);
        }
    }

    while (q.size()) {
        int u = q.front();
        q.pop();
        in[u] = false;

        if (G[u].size() % 2 == 0)
            continue;

        for (int v : G[u]) {
            if (!in[v] && G[v].size() % 2 == 0) {
                in[v] = true;
                q.push(v);
            }
        }

        del(u);
    }
}

void solve() {
    trim(n);

    for (int i = 1; i <= n; i++) {
        if (c[i] == 0)
            dfs(i);
    }

    cdup();

    for (int i = 1; i <= n; i++) {
        if (c[i] == 1)
            del(i);
        if (c[i] == 2)
            del(n + i);
    }

    trim(2 * n);

    for (int i = 1; i <= 2 * n; i++) {
        assert(G[i].empty());
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        link(u, v);
    }

    solve();

    printf("0 %zu\n", ops.size());
    for (int u : ops) {
        if (u == 0)
            puts("2");
        else
            printf("1 %d\n", u);
    }

    return 0;
}