#include <cstdio>
#include <cstring>

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define PRI 19260817ULL
#define PINV 7089841341079321457ULL

typedef unsigned long long u64;

static int n, ans, pos, sz[NMAX + 10];
static vector<int> G[NMAX + 10];
static u64 H[NMAX + 10], p[NMAX + 10], pi[NMAX + 10];
static unordered_map<u64, int> cnt;

u64 eval(int x, int fa = 0) {
    u64 &r = H[x] = 0;
    sz[x] = 0;
    for (int v : G[x]) if (v != fa) {
        r += eval(v, x) /* p[sz[v]] */;
        sz[x] += 1;
    }
    r = (r + 1) * p[sz[x]];
    cnt[r]++;
    return r;
}

inline void inc(u64 x) {
    cnt[x]++;
}

inline void dec(u64 x) {
    cnt[x]--;
    if (!cnt[x]) cnt.erase(x);
}

void dfs(int x, int fa = 0) {
    if (cnt.size() > ans) {
        ans = cnt.size();
        pos = x;
    }
    u64 cpyx = H[x];
    for (int v : G[x]) if (v != fa) {
        u64 cpyv = H[v];
        dec(H[x]); dec(H[v]);
        H[x] = ((((H[x] * pi[sz[x]]) - 1) - (H[v] /** p[sz[v]]*/)) + 1) * p[sz[x] - 1];
        H[v] = ((((H[v] * pi[sz[v]]) - 1) + (H[x] /** p[sz[x] - 1]*/)) + 1) * p[sz[v] + 1];
        sz[x]--; sz[v]++;
        inc(H[x]); inc(H[v]);
        dfs(v, x);
        dec(H[x]); dec(H[v]);
        H[x] = cpyx; H[v] = cpyv;
        sz[x]++; sz[v]--;
        inc(H[x]); inc(H[v]);
    }
}

int main() {
    scanf("%d", &n);
    p[0] = 1; pi[0] = 1;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        p[i] = p[i - 1] * PRI;
        pi[i] = pi[i - 1] * PINV;
    }
    eval(1);
    dfs(1);
    printf("%d\n", pos);
    fprintf(stderr, "ans = %d\n", ans);
    return 0;
}
