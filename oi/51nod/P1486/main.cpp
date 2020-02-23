#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2000
#define WMAX 300000
#define MOD 1000000007

typedef long long i64;

i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

static int W, H, n;
static struct Point {
    int x, y;

    bool operator<(const Point &z) const {
        return x < z.x || (x == z.x && y < z.y);
    }
} p[NMAX + 10];
static i64 fac[WMAX + 10], fi[WMAX + 10];
static i64 f[NMAX + 10];

i64 C(int n, int m) {
    if (n < m) return 0;
    return fac[n] * fi[m] % MOD * fi[n - m] % MOD;
}

i64 P(int x, int y) {
    return C(x + y, x);
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= WMAX; i++)
        fac[i] = fac[i - 1] * i % MOD;
    fi[WMAX] = inv(fac[WMAX]);
    for (int i = WMAX - 1; i >= 0; i--)
        fi[i] = fi[i + 1] * (i + 1) % MOD;

    scanf("%d%d%d", &H, &W, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);

    if (H == W && H == 1)
        return puts("1"), 0;

    p[++n] = {H, W};
    sort(p + 1, p + n + 1);

    for (int i = 1; i <= n; i++) {
        f[i] = P(p[i].x - 1, p[i].y - 1);
        for (int j = 1; j < i; j++)
        if (p[j].x <= p[i].x && p[j].y <= p[i].y)
            f[i] = (f[i] - P(p[i].x - p[j].x, p[i].y - p[j].y) * f[j]) % MOD;
    }

    i64 ans = (f[n] + MOD) % MOD;
    printf("%lld\n", ans);
    return 0;
}
