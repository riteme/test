#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

constexpr int NMAX = 200000;

int n, m;
vector<int> G[NMAX + 10];
int C[NMAX + 10];
int pa[NMAX + 10];

int find(int x) {
    return pa[x] ? pa[x] = find(pa[x]) : x;
}

void link(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v)
        return;
    pa[u] = v;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", C + i);
    }

    for (int u = 1; u <= n; u++) {
        for (int v : G[u]) {
            if (C[u] != C[v])
                link(u, v);
        }
    }

    bool okay = false;
    for (int u = 1; u <= n; u++) {
        for (int v : G[u]) {
            if (C[u] == C[v] && find(u) == find(v))
                okay = true;
        }
    }

    puts(okay ? "Yes" : "No");

    return 0;
}
