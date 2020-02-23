#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

struct Item {
    int p, c;
};

struct Query {
    int i, l;
};

int n, m, q;
int rt[NMAX + 10];
int sum[NMAX + 10];
int ans[NMAX + 10];
vector<Item> ins[NMAX + 10];
vector<Query> op[NMAX + 10];

void modify(int x, int v) {
    if (!x) return;
    for ( ; x; x -= x & -x)
        sum[x] += v;
}

int query(int x) {
    int ret = 0;
    for ( ; x <= NMAX; x += x & -x)
        ret += sum[x];
    return ret;
}

void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (u > v) swap(u, v);
        ins[v].push_back({u, w});
    }

    for (int i = 1; i <= q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        op[r].push_back({i, l});
    }
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        for (auto &e : ins[i]) {
            modify(rt[e.c], -1);
            rt[e.c] = max(rt[e.c], e.p);
            modify(rt[e.c], +1);
        }

        for (auto &e : op[i])
            ans[e.i] = query(e.l);
    }

    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}