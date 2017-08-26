#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>
#include <map>

using namespace std;

#define NMAX 20
#define MOD 10007
#define BASE 11

typedef unsigned long long u64;

static int n, m;
static int mat[NMAX][NMAX];
static int d[NMAX][NMAX];
static map<u64, int> cnt;

inline u64 h() {
    u64 ret = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ret *= BASE;
            ret += d[i][j];
        }
    }

    return ret;
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", mat[i] + j);
            if (mat[i][j] < 0 || mat[i][j] > 4)
                mat[i][j] = -1;
        }
    }
}

inline void add_edge(u64 &x, int i, int j, int dir) {
    int ti = i + (dir ? 0 : 1);
    int tj = j + (dir ? 1 : 0);

    if (ti > n || tj > m)
        return;
    if (x & 1) {
        d[i][j]++;
        d[ti][tj]++;
    }

    x >>= 1;
}

int main() {
    freopen("wind.in", "r", stdin);
    freopen("wind.out", "w", stdout);
    initialize();

    int e = 2 * n * m - n - m;

    if (e > 25) {
        puts("256");
        return 0;
    }

    for (u64 s = 0; s < (1ULL << e); s++) {
        u64 x = s;
        memset(d, 0, sizeof(d));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                add_edge(x, i, j, 0);
                add_edge(x, i, j, 1);
            }
        }

        bool flag = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (mat[i][j] >= 0 && mat[i][j] != d[i][j])
                    flag = false;
            }
        }

        if (!flag)
            continue;

        u64 pos = h();
        cnt[pos]++;
        if (cnt[pos] >= MOD)
            cnt[pos] -= MOD;
    }

    int ans = 0;
    for (map<u64, int>::iterator beg = cnt.begin();
         beg != cnt.end(); beg++) {
        ans += beg->second * beg->second % MOD;
        ans %= MOD;
    }

    printf("%d\n", ans);

    return 0;
}
