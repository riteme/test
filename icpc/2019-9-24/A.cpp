#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 1000000007

typedef long long i64;
typedef unsigned long long u64;

static int n, m;
static struct Edge {
    int u, v;
    u64 w;

    bool operator<(const Edge &z) const {
        return w < z.w;
    }
} e[NMAX + 10];
static u64 k1, k2;

u64 xorshift() {
    u64 k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= k3 << 23;
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

static int fa[NMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%llu%llu", &n, &m, &k1, &k2);
        for (int i = 1; i <= m; i++) {
            e[i] = {int(xorshift() % n + 1), int(xorshift() % n + 1), xorshift()};
        }
        sort(e + 1, e + m + 1);
        memset(fa + 1, 0, sizeof(int) * n);
        u64 ans = 0;
        int c = 0;
        for (int i = 1; i <= m; i++) {
            int u = find(e[i].u);
            int v = find(e[i].v);
            if (u == v) continue;
            c++;
            fa[u] = v;
            ans = (ans + e[i].w) % MOD;
        }
        printf("%llu\n", c == n - 1 ? ans : 0U);
    }
    return 0;
}
