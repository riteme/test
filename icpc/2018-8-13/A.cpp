#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int T, n, size[NMAX + 10];
static vector<int> roots;
static vector<int> G[NMAX + 10];

void dfs(int x, int f) {
    size[x] = 1;
    for (int v : G[x]) {
        if (v == f) continue;
        dfs(v, x);
        size[x] += size[v];
    }
}

static int cnt, seq[NMAX + 10];

void scan(int x, int f) {
    seq[++cnt] = x;
    for (int v : G[x]) {
        if (v == f) continue;
        scan(v, x);
    }
}

bool chk(int x, int f) {
    cnt = 0;
    scan(x, f);
    int mins = 1e9, cur;
    for (int i = 1; i <= cnt; i++) {
        int v = seq[i], maxs = size[x] - size[v];
        for (auto c : G[v])
            if (size[c] < size[v]) maxs = max(maxs, size[c]);
        mins = min(mins, maxs);
        if (v == x) cur = maxs;
    }

    if (cur != mins) return false;
    for (int v : G[x]) {
        if (v == f) continue;
        if (!chk(v, x)) return false;
    }
    return true;
}

int main() {
    scanf("%d%d", &T, &n);
    while (T--) {
        roots.clear();
        for (int i = 1; i <= n; i++)
            G[i].clear();

        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }

        dfs(1, 0);
        int mins = 1e9;
        for (int x = 1; x <= n; x++) {
            int val = size[1] - size[x];
            for (int v : G[x])
                if (size[v] < size[x]) val = max(val, size[v]);
            if (val < mins) {
                roots.clear();
                mins = val;
            }
            if (val <= mins)
                roots.push_back(x);
        }

        bool ok = false;
        for (int r : roots) {
            dfs(r, 0);
            if (chk(r, 0)) {
                ok = true;
                break;
            }
        }

        puts(ok ? "Centroid" : "Random");
    }

    return 0;
}
