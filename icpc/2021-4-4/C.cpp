#include <cstdio>
#include <cassert>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;
constexpr int EMAX = 400000;
constexpr int REMOVED = 1;

struct Edge {
    int u, v;
    int flag;

    int to(int x) const {
        return u == x ? v : u;
    }
} es[EMAX];
int ecnt;

int n, m;
vector<Edge *> G[NMAX + 10];
int deg[NMAX + 10];

void collect() {
    m = 0;
    memset(deg + 1, 0, sizeof(int) * n);
    for (int x = 1; x <= n; x++) {
        for (auto e : G[x]) if (!(e->flag & REMOVED)) {
            deg[x]++;
            m++;
        }
    }
}

int dfn[NMAX + 10], ccnt[NMAX + 10], cur;
bool remove_cycles(int x, int p) {
    dfn[x] = ++cur;

    bool found = false;
    for (auto e : G[x]) {
        int v = e->to(x);
        if (v == p)
            continue;

        if (dfn[v]) {
            if (dfn[v] < dfn[x]) {
                e->flag |= REMOVED;
                ccnt[v]++;
                found = true;
            }
        } else if (remove_cycles(v, x)) {
            e->flag |= REMOVED;

            if (ccnt[x] > 0)
                ccnt[x]--;
            else
                found = true;
        }
    }

    return found;
}

bool marked[NMAX + 10];
bool remove_matching(int x) {
    if (marked[x] || (deg[x] & 1) == 0)
        return false;
    marked[x] = true;

    bool matched = false;
    for (auto e : G[x]) {
        if (e->flag & REMOVED)
            continue;

        int v = e->to(x);
        if (!marked[v] && remove_matching(v) && !matched) {
            e->flag |= REMOVED;
            matched = true;
        }
    }

    return !matched;
}

int greedy_matching(int x) {
    marked[x] = true;

    int u = 0;
    for (auto e : G[x]) if (!(e->flag & REMOVED)) {
        int v = e->to(x);
        if (marked[v])
            continue;

        v = greedy_matching(v);
        if (u) {
            printf("%d %d\n", u, v);
            u = 0;
        } else
            u = v;
    }

    return u ? u : x;
}

void solve() {
    cur = 0;
    fill(dfn + 1, dfn + n + 1, 0);
    fill(ccnt + 1, ccnt + n + 1, 0);
    remove_cycles(1, 0);

    collect();
    memset(marked + 1, 0, n);
    for (int i = 1; i <= n; i++) {
        if (deg[i] & 1)
            remove_matching(i);
    }

    // for (int i = 0; i < ecnt; i++) {
    //     if (es[i].flag & REMOVED)
    //         printf("- %d, %d\n", es[i].u, es[i].v);
    // }

    collect();
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] & 1)
            cnt++;
    }

    printf("%d\n", cnt / 2);
    memset(marked + 1, 0, n);
    for (int i = 1; i <= n; i++) {
        if (!marked[i] && (deg[i] & 1) == 0)
            assert(greedy_matching(i) == i);
    }
}

void link(int u, int v) {
    auto e = es + ecnt;
    ecnt++;
    *e = {u, v, 0};
    G[u].push_back(e);
    G[v].push_back(e);
    deg[u]++;
    deg[v]++;
}

int main() {
    int q;
    while (scanf("%d%d", &n, &q) != EOF) {
        if (n == 0 && q == 0)
            break;

        // printf("n=%d, q=%d\n", n, q);
        for (int i = 1; i <= n; i++) {
            G[i].clear();
        }
        ecnt = 0;

        fill(deg + 1, deg + n + 1, 0);
        for (int i = 0; i < q; i++) {
            int c, u;
            scanf("%d%d", &c, &u);

            for (int i = 1; i < c; i++) {
                int v;
                scanf("%d", &v);
                link(u, v);
                u = v;
            }
        }

        solve();
    }

    return 0;
}