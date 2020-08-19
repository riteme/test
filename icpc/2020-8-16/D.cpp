#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

struct ran {
    int l, r;

    bool contain(const ran &z) const {
        return l <= z.l && z.r <= r;
    }

    bool contain(int x) const {
        return l <= x && x <= r;
    }

    bool intersect(const ran &z) const {
        return contain(z.l) || contain(z.r) || z.contain(l) || z.contain(r);
    }

    bool operator<(const ran &z) const {
        return r < z.r || (r == z.r && l > z.l);
    }
};

int n, q, idcnt;
int pa[NMAX + 10];
vector<int> G[NMAX + 10];
ran A[NMAX + 10];
int top[NMAX + 10], dep[NMAX + 10], idx[NMAX + 10], rev[NMAX + 10];

void dfs(int x) {
    top[x] = 1;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        dep[v] = dep[x] + 1;
        dfs(v);
        top[x] += top[v];
    }
}

void decompose(int x) {
    rev[idcnt] = x;
    idx[x] = idcnt++;
    int u = 0;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (top[v] >= top[u])
            u = v;
    }
    if (u) {
        top[u] = top[x];
        decompose(u);
    }
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (u == v)
            continue;
        top[v] = v;
        decompose(v);
    }
}

int query(int x, int R) {
    while (top[x] != n + 1 && A[rev[idx[pa[top[x]]]]].r <= R) {
        x = pa[top[x]];
    }

    int u = top[x];
    if (A[rev[idx[u]]].r <= R)
        return rev[idx[u]];

    int l = idx[u], r = idx[x];
    while (l < r) {
        int m = (l + r) / 2 + 1;
        int v = rev[m];
        if (A[v].r > R)
            l = m;
        else
            r = m - 1;
    }

    return rev[l + 1];
}

void _main() {
    for (int i = 1; i <= n + 1; i++) {
        G[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &A[i].l, &A[i].r);
        A[i].r--;
    }

    sort(A + 1, A + n + 1);
    int j = 1;
    for (int i = 2; i <= n; i++) {
        if (A[i].contain(A[j]))
            continue;
        A[++j] = A[i];
    }
    n = j;

    A[0].l = A[0].r = -1;
    A[n + 1].l = A[n + 1].r = INT_MAX;

    j = 1;
    pa[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
        while (j <= n && A[i].intersect(A[j])) {
            j++;
        }
        pa[i] = j;
        G[pa[i]].push_back(i);
    }

    idcnt = 1;
    dep[n + 1] = 1;
    dfs(n + 1);
    top[n + 1] = n + 1;
    decompose(n + 1);

    while (q--) {
        int L, R;
        scanf("%d%d", &L, &R);
        R--;

        int l = 0, r = n;
        while (l < r) {
            int m = (l + r) / 2 + 1;
            if (A[m].l < L)
                l = m;
            else
                r = m - 1;
        }

        int x = l + 1;
        int ans;
        if (x <= n && A[x].r <= R) {
            int u = query(x, R);
            ans = dep[x] - dep[u] + 1;
        } else
            ans = 0;
        printf("%d\n", ans);
    }
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        _main();
    }
    return 0;
}
