#include <cassert>
#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef unsigned long long u64;

#define NMAX 5000
#define DMAX 200
#define MMAX 1000000
#define BASE 19260817ull

struct UnionFind {
    UnionFind() {
        memset(fa, 0, sizeof(fa));
        for (int i = 1; i <= NMAX; i++)
            pre[i] = nxt[i] = i;
    }

    int fa[NMAX + 10];
    int pre[NMAX + 10], nxt[NMAX + 10];

    int find(int x) {
        return fa[x] > 0 ? fa[x] = find(fa[x]) : x;
    }

    void link(int u, int v) {
        assert(fa[u] <= fa[v]);
        if (fa[u] == fa[v]) fa[u]--;
        fa[v] = u;
        pre[nxt[v]] = u;
        pre[nxt[u]] = v;
        swap(nxt[u], nxt[v]);
    }
};

static int n, m, d, ans;
static u64 val[NMAX + 10], P[DMAX + 10];
static UnionFind set[DMAX + 10];
static unordered_map<u64, int> cnt;

int main() {
    P[0] = 1;
    for (int i = 1; i <= DMAX; i++)
        P[i] = P[i - 1] * BASE;

    scanf("%d%d%d", &d, &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= d; j++)
            val[i] += P[j];
        val[i] *= i;
        cnt[val[i]]++;
    }

    while (m--) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);

        u = set[k].find(u);
        v = set[k].find(v);
        if (u != v) {
            if (set[k].fa[u] > set[k].fa[v]) swap(u, v);
            int x = v;
            do {
                ans -= cnt[val[x]];
                cnt[val[x]]--;
                val[x] += (u - v) * P[k];
                cnt[val[x]]++;
                ans += cnt[val[x]];
                x = set[k].nxt[x];
            } while (x != v);
            set[k].link(u, v);
        }

        printf("%d\n", ans * 2 + n);
    }

    return 0;
}
