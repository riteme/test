#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

using i64 = long long;

constexpr int NMAX = 50;
constexpr int DMAX = 5000000;

int n, q;
int V[NMAX + 10];
i64 C[NMAX + 10];
i64 f[DMAX + 10];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d%lld", V + i, C + i);
    }
    fill(f + 1, f + DMAX + 1, -1);
    for (int j = 1; j <= n; j++) {
        for (int i = V[j]; i <= DMAX; i++) {
            int k = i - V[j];
            if (f[k] >= 0)
                f[i] = max(f[i], f[k] + C[j]);
        }
    }

    // for (int i = 1; i <= n; i++) {
    //     int maxv = V[i];
    //     i64 maxc = C[i];
    //     for (int v = V[i]; v <= DMAX; v += V[i]) {
    //         if (maxc * v < maxv * f[v]) {
    //             maxv = v;
    //             maxc = f[v];
    //         }
    //     }
    //     V[i] = maxv;
    //     C[i] = maxc;
    // }

    while (q--) {
        i64 v;
        scanf("%lld", &v);
        i64 ans = -1;
        for (int i = 1; i <= n; i++) {
            i64 k = (v - DMAX + V[i] - 1) / V[i];
            i64 c = v - k * V[i];
            if (f[c] >= 0) {
                i64 w = f[c] + k * C[i];
                ans = max(ans, w);
            }
        }
        if (ans < 0)
            puts("-1");
        else
            printf("%lld\n", ans);
    }

    return 0;
}
