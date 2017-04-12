#include <cstdio>

typedef long long i64;
typedef long double f128;

static int b[100];
static bool vis[100][40][200];
static i64 f[100][40][200];

i64 dp(int i, int j, int s) {
    if (j == 0 && s == 0)
        return 1;
    if (i <= 0 || j <= 0)
        return 0;
    if (vis[i][j][s])
        return f[i][j][s];
    vis[i][j][s] = true;
    i64 &ret = f[i][j][s];

    ret += dp(i - 1, j, s);

    if ((s >> b[i]) & 1) {
        ret += dp(i - 1, j - 1, s);
        ret += dp(i - 1, j - 1, s ^ (1 << b[i]));
    }

    return ret;
}

int main() {
    int c = 7;
    int n = 70;
    int m = 20;
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < 10; j++) {
            b[i * 10 + j] = i;
        }
    }

    i64 ans = 0;
    for (int s = 0; s < (1 << c); s++) {
        int cnt = 0;
        for (int i = 0; i < c; i++) {
            cnt += (s >> i) & 1;
        }
        ans += cnt * dp(n, m, s);
    }

    printf("%lld\n", ans);

    return 0;
}
