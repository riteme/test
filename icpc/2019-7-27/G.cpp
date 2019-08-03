#define NDEBUG
#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define NMAX 2000
#define MMAX 12
#define MOD 1000000007
#define A 19260817
#define B 0xDEADBEEF9B7EFF61

typedef unsigned long long u64;

static int n, q, m;
static vector<int> G[NMAX + 10];
static vector<int> T[NMAX + 10];
static unordered_map<u64, int> cnt[MMAX + 10];
static unordered_map<u64, int> dp[NMAX + 10][MMAX + 1];

inline void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

inline u64 insert(u64 a, u64 b) {
    return a * (b ^ B);
}

void scan(int x, int fa) {
    dp[x][1][A] = 1;
    for (int v : G[x]) if (v != fa) {
        scan(v, x);
        for (int j = MMAX; j >= 2; j--) for (int k = 1; k <= j - 1; k++)
        for (auto &xt : dp[x][k]) for (auto &vt : dp[v][j - k])
            add(dp[x][j][insert(xt.first, vt.first)], xt.second * vt.second);
    }
    for (int i = 1; i <= MMAX; i++) for (auto &xt : dp[x][i])
        add(cnt[i][xt.first], xt.second);
}

u64 H(int x, int fa) {
    u64 r = A;
    for (int v : T[x])
        if (v != fa) r = insert(r, H(v, x));
    return r;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        assert(1 <= u && u <= n);
        assert(1 <= v && v <= n);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scan(1, 0);

    scanf("%d", &q);
    while (q--) {
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) T[i].clear();
        for (int i = 1; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            assert(1 <= u && u <= m);
            assert(1 <= v && v <= m);
            T[u].push_back(v);
            T[v].push_back(u);
        }
        int ans = 0;
        unordered_set<u64> used;
        for (int i = 1; i <= m; i++) {
            auto key = H(i, 0);
            if (used.count(key)) continue;
            used.insert(key);
            add(ans, cnt[m][key]);
            //fprintf(stderr, "i = %d, cnt = %d\n", i, cnt[m][key]);
        }
        printf("%d\n", ans);
    }

    return 0;
}
