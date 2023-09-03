#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;

struct edge {
    int u, v, i;
    char c;

    int to(int x) {
        return u == x ? v : u;
    }
};

int n, m;
edge e[NMAX + 10];
char s[NMAX + 10];
int pa[NMAX + 10];
bool ok[NMAX + 10];
int cnt = 0;
int ans[NMAX + 10];
vector<edge *> G[NMAX + 10];

void submit(int i) {
    ans[++cnt] = i;
}

int find(int u) {
    return pa[u] ? pa[u] = find(pa[u]) : u;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        char t[16];
        scanf("%d%d%s", &e[i].u, &e[i].v, t);
        e[i].i = i;
        e[i].c = t[0];
        G[e[i].u].push_back(e + i);
        G[e[i].v].push_back(e + i);
    }
    scanf("%s", s + 1);

    for (int i = 1; i <= m; i++) {
        auto [u, v, _, c] = e[i];
        if (s[u] == c && s[v] == c) {
            u = find(u);
            v = find(v);
            if (u == v)
                continue;
            pa[u] = v;
            ok[v] = true;
            submit(i);
        }
    }

    queue<int> Q;
    for (int u = 1; u <= n; u++) {
        int x = find(u);
        if (ok[x]) {
            ok[u] = true;
            Q.push(u);
        }
    }

    while (Q.size()) {
        int u = Q.front();
        Q.pop();
        for (auto e : G[u]) {
            int v = e->to(u);
            if (!ok[v] && s[v] == e->c) {
                submit(e->i);
                ok[v] = true;
                pa[find(v)] = find(u);
                Q.push(v);
            }
        }
    }

    bool failed = false;
    for (int u = 1; u <= n; u++) {
        if (!ok[find(u)])
            failed = true;
    }

    if (failed) {
        puts("No");
        return 0;
    }

    for (int i = 1; i <= m; i++) {
        int u = find(e[i].u);
        int v = find(e[i].v);
        if (u != v) {
            pa[u] = v;
            submit(i);
        }
    }

    if (cnt == n - 1) {
        puts("Yes");
        for (int i = 1; i <= cnt; i++) {
            printf("%d ", ans[i]);
        }
        puts("");
    } else {
        puts("No");
    }

    return 0;
}
