#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 60
#define MOD 998244353
#define rep(x, l, r) for (int x = l; x <= r; x++)
#define rrep(x, r, l) for (int x = r; x >= l; x--)

typedef long long i64;

static int n, m, B, C, A[100], N[100];
static i64 f[NMAX][NMAX * NMAX];
static i64 g[NMAX][NMAX][NMAX];
static char buf[100];

bool initialize() {
    scanf("%d%d%d%s", &m, &B, &C, buf);

    n = strlen(buf);
    rep(i, 0, n - 1) {
        N[i] = buf[i] - '0';
    }

    if (n == 1 && N[0] == 0)
        return false;

    reverse(N, N + n);

    N[0]--;
    rep(i, 0, n) {
        if (N[i] >= 0)
            break;
        N[i] += 10;
        N[i + 1]--;
    }

    rep(i, 0, m - 1) {
        rrep(j, n - 1, 0) {
            A[i] = (A[i] * 10 + N[j]) % B;
        }

        int r = 0;
        rrep(j, n - 1, 0) {
            r = r * 10 + N[j];
            N[j] = r / B;
            r %= B;
        }
    }

    return true;
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

i64 dp(int i, int j, int k) {
    if (i < 0)
        return j == 0;
    if (g[i][j][k] >= 0)
        return g[i][j][k];

    i64 &r = g[i][j][k] = 0;
    rep(k, 0, (m - t - i + 1) * (B - 1)) {
        if ((j + k) % B == A[i])
            add(r, solve(t, i + 1, (j + k) / B) * f[max(0, m - t - i + 1)][k] % MOD);
        if (i && t && (j + k + 1) % B == A[i])
            add(r, solve(t - 1, i + 1, (j + k + 1) / B) * f[max(0, m - t - i + 1)][k] % MOD);
    }

    return r;
}

int main() {
    if (!initialize()) {
        puts("0");
        return 0;
    }

    f[0][0] = 1;
    rep(i, 0, m) rep(j, 0, i * (B - 1)) rep(k, 0, B - 1) {
        add(f[i + 1][j + k], f[i][j]);
    }

    memset(g, -1, sizeof(g));

    i64 ans = 0;
    if (C == 0) {
        rep(t, 0, m) {
            add(ans, solve(t, 0, 0));
        }
    } else
        ans = solve(0, 0, 0);

    printf("%lld\n", ans);

    return 0;
}
