#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 400000
#define CMAX 20
#define SMAX (1 << (CMAX))

typedef long long i64;

int n;
int a[NMAX + 10];
i64 w[CMAX + 10][CMAX + 10];
i64 f[SMAX];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= CMAX; i++)
    for (int j = 1; j <= CMAX; j++) if (i != j) {
        i64 s = 0;
        for (int k = 1; k <= n; k++)
        if (a[k] == j) s++;
        else if (a[k] == i) w[i][j] += s;
    }

    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int s = 0; s < SMAX - 1; s++) {
        for (int i = 1; i <= CMAX; i++) if (!((s >> (i - 1)) & 1)) {
            i64 t = 0;
            for (int j = 1; j <= CMAX; j++) if ((s >> (j - 1)) & 1)
                t += w[i][j];

            int ns = s | (1 << (i - 1));
            f[ns] = min(f[ns], f[s] + t);
        }
    }

    printf("%lld\n", f[SMAX - 1]);
    return 0;
}