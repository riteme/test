#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;

#define NMAX 100000

typedef tr1::unordered_map<int, int> mp;

struct rec {
    rec() : p(NULL), cnt(0) {}

    mp *p;
    int cnt;
};

int n, K, q;
int w[NMAX + 10], ans[NMAX + 10];
vector<int> G[NMAX + 10];

rec meld(rec x, rec y) {
    if (!x.p)
        return y;
    if (!y.p)
        return x;
    if (x.p->size() < y.p->size())
        swap(x, y);

    mp &xmp = *x.p;
    for (mp::iterator it = y.p->begin(); it != y.p->end(); it++) {
        int key = it->first, val = it->second;
        if (xmp[key] == K)
            x.cnt--;
        xmp[key] += val;
        if (xmp[key] == K)
            x.cnt++;
    }

    delete y.p;
    return x;
}

rec dfs(int x, int pa) {
    rec rax;
    rax.p = new mp;
    (*rax.p)[w[x]] = 1;
    if (K == 1)
        rax.cnt = 1;

    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == pa)
            continue;

        rec ret = dfs(v, x);
        rax = meld(rax, ret);
    }

    ans[x] = rax.cnt;
    return rax;
}

void _main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%d", w + i);
        G[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    rec ret = dfs(1, 0);
    delete ret.p;

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int u;
        scanf("%d", &u);
        printf("%d\n", ans[u]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d:\n", i);
        _main();
        if (i < T)
            puts("");
    }
    return 0;
}
