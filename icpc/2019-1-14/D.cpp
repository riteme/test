#include <cstdio>

using namespace std;

#define NMAX 250000
#define KMAX 9
#define INF 0x3f3f3f3f3f3f3f3f

#define rep(i, l, r) for (int i = (l); i <= (r); i++)

typedef long long i64;

static int n, K;
static i64 w[NMAX + 10];
static i64 f[NMAX + 10][KMAX + 1][KMAX + 1][3];

template <typename T>
inline T min(const T &a, const T &b) {
    return a < b ? a : b;
}

template <typename T, typename ... T2>
inline T min(const T &a, const T &b, const T2& ... args) {
    return min(min(a, b), args...);
}

int main() {
    scanf("%d%d", &n, &K);
    rep(i, 1, n) scanf("%lld", w + i);
    rep(j, 0, K) rep(k, 0, K) f[0][j][k][0] = f[0][j][k][1] = f[0][j][k][2] = INF;
    f[0][0][0][1] = 0;
    rep(i, 1, n) rep(j, 0, K) rep(k, 0, K) {
        f[i][j][k][0] = f[i - 1][j][k][1];
        f[i][j][k][1] = f[i - 1][j][k][2];
        f[i][j][k][2] = w[i] + min(f[i - 1][j][k][0], f[i - 1][j][k][1], f[i - 1][j][k][2]);
        if (j) {
            f[i][j][k][0] = min(f[i][j][k][0], f[i - 1][j - 1][k][1] + w[i]);
            f[i][j][k][1] = min(f[i][j][k][1], f[i - 1][j - 1][k][2] + w[i]);
        }
        if (k)
            f[i][j][k][2] = min(f[i][j][k][2], f[i - 1][j][k - 1][0], f[i - 1][j][k - 1][1], f[i - 1][j][k - 1][2]);
    }
    i64 ans = INF;
    rep(j, 0, K) ans = min(ans, f[n][j][j][1], f[n][j][j][2]);
    printf("%lld\n", ans);
    return 0;
}
