#include <cstdio>
#include <vector>

using namespace std;

constexpr int NMAX = 100000;

int n;
vector<int> G[NMAX + 10];
bool mark[NMAX + 10];
int s[NMAX + 10];
int p[NMAX + 10];

void dfs(int u, int p) {
    s[u] = 1;
    for (int v : G[u]) {
        if (mark[v] || v == p)
            continue;

        dfs(v, u);
        s[u] += s[v];
    }
}

int centor(int u, int p, int maxs) {
    int maxv = 0;
    for (int v : G[u]) {
        if (mark[v] || v == p)
            continue;
        if (s[v] > s[maxv])
            maxv = v;
    }
    return s[maxv] * 2 > maxs ? centor(maxv, u, maxs) : u;
}

int solve(int x) {
    dfs(x, 0);
    int u = centor(x, 0, s[x]);
    mark[u] = true;
    for (int v : G[u]) {
        if (mark[v])
            continue;

        p[solve(v)] = u;
    }
    return u;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    p[solve(1)] = -1;
    for (int i = 1; i <= n; i++) {
        printf("%d ", p[i]);
    }
    puts("");

    return 0;
}
