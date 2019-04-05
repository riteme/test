#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 3000
#define MMAX ((NMAX * (NMAX + 1)) / 2)
#define MOD 1000000007LL

typedef long long i64;

static int n, m, seq[NMAX + 10];
static int fa[MMAX + 10], ch[MMAX + 10][2];
static i64 dp[MMAX + 10], ans;

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

inline void update(int x) {
    int p = x, cur = 0, i = 0;
    do {
        cur = (cur << 1) | (ch[fa[p]][1] == p);
        p = fa[p];
        i++;
        if (i < 4 ||
            (cur != 12 && cur != 10 && cur != 7 && cur != 15))
            add(dp[x], dp[p]);
    } while (p && i < 4);
    add(ans, dp[x]);
}

int main() {
    int q;
    scanf("%d", &q);
    dp[0] = 1;
    while (q--) {
        int c;
        scanf("%d", &c);
        n++;
        for (int i = 0; i < n; i++) {
            int x = seq[i];
            if (!ch[x][c]) {
                fa[++m] = x;
                ch[x][c] = m;
                update(m);
            }
            seq[i] = ch[x][c];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
