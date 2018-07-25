#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 20
#define OFF 10
#define MOD 998244353

typedef long long i64;

static int T, n, K;
static bool mat[NMAX + 10][NMAX + 10];
static int cnt[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d%d%d", &T, &n, &K);

    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        mat[x + OFF][y + OFF] = true;
    }
}

int main() {
    // freopen("wander.in", "r", stdin);
    // freopen("wander.out", "w", stdout);
    initialize();

    i64 ans = 0;
    for (int s = 0; s < (1 << 2 * T); s++) {
        int ret = 0;
        memset(cnt, 0, sizeof(cnt));

        int cx = OFF, cy = OFF;
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        cnt[cx][cy] = 1;
        if (cnt[cx][cy] == K)
            ret++;

        int x = s;
        for (int i = 0; i < T; x >>= 2, i++) {
            int dir = x & 3;
            cx += dx[dir];
            cy += dy[dir];
            if (mat[cx][cy]) {
                ret = 0;
                break;
            }
            cnt[cx][cy]++;
            if (cnt[cx][cy] == K)
                ret++;
        }

        ans += ret;
        if (ans >= MOD)
            ans -= MOD;
    }

    printf("%lld\n", ans);

    return 0;
}
