#include <cstdio>

using namespace std;

using i64 = long long;

constexpr i64 MOD = 998244353;

void solve(i64 n) {
    i64 ans = 0;

    // x < y = z
    for (i64 z = 1; z * z <= n; z++) {
        i64 y = z;
        ans = (ans + y - 1) % MOD;
    }

    // x, y < z
    for (i64 z = 1; z * z <= n; z++) {
        ans = (ans + (z - 1) * (z - 1)) % MOD;
    }
    for (i64 nz = 1; nz * nz < n; nz++) {
        i64 zmin = (n / (nz + 1)) + 1;
        i64 zmax = n / nz;
        if (zmin * zmin <= n)
            continue;
        // printf("nz=%lld, zmin=%lld, zmax=%lld\n", nz, zmin, zmax);
        ans = (ans + nz * nz % MOD * (zmax - zmin + 1)) % MOD;
    }

    ans = ans * 3 % MOD;

    // x = y = z
    for (i64 z = 1; z * z <= n; z++) {
        ans++;
    }

    ans = (ans % MOD + MOD) % MOD;

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n;
        scanf("%lld", &n);
        solve(n);
    }
    return 0;
}
