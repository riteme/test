#include <cstdio>
#include <cstring>
#include <cassert>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300

struct Edge {
    int u, v, id;
    bool avail;

    int to(int x) const {
        return u == x ? v : u;
    }
};

int n, m, K;
int maxd = 0, mind = INT_MAX;
int deg[NMAX + 10];
vector<Edge*> G[NMAX + 10];

int mat[NMAX + 10], lev[NMAX + 10];

bool extend(int x) {
    for (auto e : G[x]) if (e->avail) {
        int v = e->to(x);
        if (deg[x] == deg[v])
            continue;

        if (lev[mat[v]] == lev[x] + 1)
        if (!mat[v] || extend(mat[v])) {
            mat[v] = x;
            mat[x] = v;
            return true;
        }
    }
    lev[x] = 0;
    return false;
}

int q[NMAX + 10], *qb, *qe;
int hopcroft() {
    int re = 0;
    memset(mat, 0, sizeof(int) * (n + 1));
    while (true) {
        qb = qe = q;
        memset(lev, 0, sizeof(int) * (n + 1));
        for (int i = 1; i <= n; i++)
        if (!mat[i])
            lev[*qe++ = i] = 1;
        while (qb != qe) {
            int x = *qb++;
            if (lev[0]) break;
            for (auto e : G[x]) if (e->avail) {
                int j = e->to(x);
                if (deg[x] == deg[j])
                    continue;

                if (!lev[mat[j]])
                    lev[*qe++ = mat[j]] = lev[x] + 1;
            }
        }
        if (!lev[0]) break;
        for (int i = 1; i <= n; i++)
        if (!mat[i]) re += extend(i);
    }
    return re;
}

void update() {
    maxd = 0, mind = INT_MAX;
    for (int i = 1; i <= n; i++) {
        maxd = max(maxd, deg[i]);
        mind = min(mind, deg[i]);
    }
}

void fuck() {
    for (int u = 1; u <= n; u++) if (deg[u] == maxd)
    for (auto e : G[u]) if (e->avail) {
        int v = e->to(u);
        if (deg[v] == maxd) {
            e->avail = false;
            deg[u]--;
            deg[v]--;
            break;
        }
    }

    hopcroft();
    for (int u = 1; u <= n; u++) if (deg[u] == maxd) {
        assert(mat[u]);
        for (auto e : G[u]) if (e->avail) {
            int v = e->to(u);
            if (v == mat[u]) {
                e->avail = false;
                deg[u]--;
                deg[v]--;
                break;
            }
        }
    }

    update();
}

int idx[NMAX * NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        auto e = new Edge{u, v, i, true};
        G[u].push_back(e);
        G[v].push_back(e);
        deg[u]++;
        deg[v]++;
    }
    update();

    if (K <= maxd) {
        while (!(mind <= K && K <= maxd))
            fuck();
    }

    if (mind <= K && K <= maxd) {
        puts("YES");
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        for (auto e : G[i])
        if (e->avail && e->u == i)
            idx[cnt++] = e->id;
        sort(idx, idx + cnt);

        printf("%d\n", cnt);
        for (int i = 0; i < cnt; i++)
            printf("%d ", idx[i]);
        puts("");
    } else puts("NO");

    return 0;
}
