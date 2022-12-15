#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

struct fuck {
    i64 v, w;
    bool operator<(const fuck &z) const {
        if (v * z.w == z.v * w)
            return w > z.w;
        return v * z.w > z.v * w;
    }
};

int n, m;
fuck fu[2000];
i64 f[20000];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &fu[i].v);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &fu[i].w);
    }
    sort(fu + 1, fu + m + 1);
    for (int i = 0; i <= n; i++) {
        f[i] = -INF;
    }
    f[n] = 0;
    for (int i = 1; i <= m; i++) {
        for (i64 j = 0; j <= n - fu[i].w; j++) {
            f[j] = max(f[j], f[j + fu[i].w] + (j + fu[i].w) * fu[i].v);
        }
    }
    i64 ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, f[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
