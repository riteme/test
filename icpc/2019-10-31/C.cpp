#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static bool vis[NMAX + 10];
static vector<int> G[NMAX + 10];
static struct {
    int x, y;
} p[NMAX + 10];

static int size[NMAX + 10];

void dfs(int x, int f) {
    size[x] = 1;
    for (int v : G[x]) if (!vis[v] && v != f) {
        dfs(v, x);
        size[x] += size[v];
    }
}

void embed(int u, int l, int y);

void plot(int x, int f, int std, int i, int y) {
    vis[x] = true;
    p[x] = {i, y};
    for (int v : G[x]) if (!vis[v] && v != f) {
        if (size[v] * 2 >= std) {
            plot(v, x, std, i + size[x] - size[v], y);
            break;
        }
    }
    int s = 0;
    for (int v : G[x]) if (!vis[v] && v != f) {
        embed(v, i + s, y + 1);
        s += size[v];
    }
}

void embed(int u, int l, int y) {
    dfs(u, 0);
    plot(u, 0, size[u], l, y);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    embed(1, 1, 1);

    for (int i = 1; i <= n; i++)
        printf("%d %d\n", p[i].x, p[i].y);

    return 0;
}
