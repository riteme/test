#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

template <typename T>
T chkmin(T &a, T b) {
    return a = (a < b ? a : b);
}

struct vec {
    int x, y;

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }

    i64 operator%(const vec &z) const {
        return (i64)x * z.y - (i64)y * z.x;
    }
};

constexpr int NMAX = 100;
constexpr int KMAX = 20;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int n, m, K;
vec p[NMAX + 10];
vec s[NMAX * NMAX + 10];
i64 f[NMAX + 10][NMAX + 10][KMAX + 10];
i64 g[NMAX + 10][KMAX + 10];

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            s[++m] = {i, j};
        }
    }
    sort(s + 1, s + m + 1, [&](const vec &a, const vec &b) {
        vec u = p[a.y] - p[a.x];
        vec v = p[b.y] - p[b.x];
        return atan2(u.y, u.x) < atan2(v.y, v.x);
    });

    i64 ans = INF;
    for (int a = 1; a <= n; a++) {
        memset(f, 0x3f, sizeof(f));
        memset(g, 0x3f, sizeof(g));
        for (int l = 1; l <= m; l++) {
            int i = s[l].x, j = s[l].y;
            if (i == a) {
                chkmin(f[i][j][1], p[i] % p[j]);
                chkmin(g[j][1], f[i][j][1]);
            }
            for (int k = 2; k <= K; k++) {
                chkmin(f[i][j][k], g[i][k - 1] + p[i] % p[j]);
                chkmin(g[j][k], f[i][j][k]);
            }
        }
        chkmin(ans, g[a][K]);
    }

    if (ans < INF / 2)
        printf("%.4lf\n", (double)ans / 2);
    else
        puts("0");
    return 0;
}
