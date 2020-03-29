#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 20
#define SMAX (1 << NMAX)

int n;
i64 DPS[NMAX], HP[NMAX];
i64 f[SMAX];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%lld%lld", DPS + i, HP + i);
        memset(f, 0x3f, sizeof(i64) * (1 << n));

        f[0] = 0;
        for (int s = 1; s < (1 << n); s++) {
            i64 sum = 0;
            for (int i = 0; i < n; i++)
            if ((s >> i) & 1) sum += DPS[i];
            for (int i = 0; i < n; i++) if ((s >> i) & 1) {
                f[s] = min(f[s], f[s ^ (1 << i)] + sum * HP[i]);
            }
        }

        printf("%lld\n", f[(1 << n) - 1]);
    }

    return 0;
}