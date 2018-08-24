#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef unsigned long long u64;

#define NMAX 6
#define MMAX 300
#define SMAX (1 << NMAX)
#define MOD 1000000007

#define BLACK(i) ((C >> (i - 1)) & 1)
#define WHITE(i) (!BLACK(i))
#define SEL(i)   ((S >> (i - 1)) & 1)
#define UNSEL(i) (!SEL(i))

static int n, m, cnt;
static unordered_map<u64, int> f[2][SMAX];  // f[i][C][S]

inline int set(int S, int i) {
    S |= 1 << (i - 1);
    return S;
}

inline int unset(int S, int i) {
    S = S & (~(1 << (i - 1)));
    return S;
}

inline void add(int &dest, int src) {
    dest += src;
    if (dest >= MOD) dest -= MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    cnt = 1 << n;
    if ((n & 1) && (m & 1)) {
        puts("0");
        return 0;
    }

    f[0][0][1] = f[0][1][1] = 1;
    int cur = 1, nxt = 0;
    int maxs = 0;
    for (int j = 1; j <= m; j++)
    for (int i = 1; i <= n; i++) {
        if (i == n && j == m) break;
        swap(cur, nxt);
        for (int C = 0; C < cnt; C++)
            f[nxt][C].clear();

        for (int C = 0; C < cnt; C++) {
            maxs = max(maxs, static_cast<int>(f[cur][C].size()));
        for (auto e : f[cur][C]) {
        u64 mask = e.first, nmask;
        int dp = e.second, p = i < n ? i + 1 : 1;

#define DP(COLOR) \
        nmask = 0; \
        for (int S = 0; S < cnt; S++) { \
            if (!((mask >> S) & 1)) continue; \
            if ((j > 1 || i == n) && UNSEL(p) && COLOR(p)) \
                nmask |= 1LL << set(S, p); \
            else if ((j == 1 && i < n) || SEL(p)) { \
                nmask |= 1LL << unset(S, p); \
                if (p > 1 && UNSEL(i) && COLOR(i)) \
                    nmask |= 1LL << set(set(S, i), p); \
            } \
        }

        DP(BLACK)
        add(f[nxt][unset(C, p)][nmask], dp);
        DP(WHITE)
        add(f[nxt][set(C, p)][nmask], dp);
#undef DP
    }}}

    int ans = 0;
    for (int C = 0; C < cnt; C++) {
        maxs = max(maxs, static_cast<int>(f[cur][C].size()));
        for (auto e : f[nxt][C]) {
            if ((e.first >> (cnt - 1)) & 1) add(ans, e.second);
        }
    }
    printf("maxs = %d\n", maxs);  // maxs <= 75 ?
    printf("%d\n", ans);

    return 0;
}
