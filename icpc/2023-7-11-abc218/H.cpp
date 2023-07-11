#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

int n;
i64 w[NMAX + 10];

struct val {
    i64 v;
    int c;

    val operator+(const val &z) const {
        return {v + z.v, c + z.c};
    }

    bool operator<(const val &z) const {
        return v < z.v || (v == z.v && c > z.c);
    }
};

val f[NMAX + 10][2];

val dp(i64 K) {
    f[1][0] = {0, 0};
    f[1][1] = {-K, 1};
    for (int i = 2; i <= n; i++) {
        f[i][0] = max(f[i - 1][0], f[i - 1][1] + val{w[i - 1], 0});
        f[i][1] = f[i - 1][0] + val{w[i - 1] - K, 1};
    }

    val v = max(f[n][0], f[n][1]);
    // printf("v=%lld, c=%d\n", v.v, v.c);
    return v;
}

int main() {
    int R;
    scanf("%d%d", &n, &R);
    if (R > n / 2)
        R = n - R;
    for (int i = 1; i < n; i++) {
        scanf("%lld", w + i);
    }

    i64 l = 0, r = 10000000000;
    while (l < r) {
        i64 m = (l + r) / 2;
        val v = dp(m);
        // printf("l=%lld, r=%lld, K=%lld, v=%lld, c=%d\n", l, r, m, v.v + m * v.c, v.c);
        if (v.c <= R)
            r = m;
        else
            l = m + 1;
    }

    val v = dp(l);
    printf("%lld\n", v.v + R * l);
    return 0;
}
