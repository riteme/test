#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int LMAX = 60;

i64 B, n;
i64 f[LMAX + 1][2][2][2];  // f[i][sum][tail][less]

void solve() {
    f[LMAX][0][0][0] = 1;
    for (int i = LMAX; i > 0; i--) {
        int b = (B >> (i - 1)) & 1;
        int u = (n >> (i - 1)) & 1;
        for (int s = 0; s < 2; s++)
        for (int t = 0; t < 2; t++)
        for (int l = 0; l < 2; l++) {
            if (!f[i][s][t][l])
                continue;
            // 0
            int nl = l || 0 < u;
            if (b)
                f[i - 1][s ^ 1][t ^ 1][nl] += f[i][s][t][l];
            else
                f[i - 1][s][0][nl] += f[i][s][t][l];
            // 1
            if (l || u > 0) {
                if (b)
                    f[i - 1][s ^ 1 ^ t ^ 1][0][l] += f[i][s][t][l];
                else
                    f[i - 1][s][t ^ 1][l] += f[i][s][t][l];
            }
        }
    }

    i64 ans = f[0][1][0][1] + f[0][1][1][1];
    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &B, &n);
        memset(f, 0, sizeof(f));
        solve();
    }
    return 0;
}
