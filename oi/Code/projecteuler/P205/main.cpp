#include <cstdio>

#include <algorithm>

using namespace std;

typedef long long i64;

static i64 f[10][40];
static i64 g[10][40];

int main() {
    f[0][0] = g[0][0] = 1;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 36; j++) {
            for (int k = 1; k <= min(j, 4); k++) {
                f[i][j] += f[i - 1][j - k];
            }
        }
    }

    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 36; j++) {
            for (int k = 1; k <= min(j, 6); k++) {
                g[i][j] += g[i - 1][j - k];
            }
        }
    }

    i64 fsum = 0, gsum = 0;
    for (int i = 0; i <= 36; i++) {
        fsum += f[9][i];
        printf("f[%d] = %lld\n", i, f[9][i]);
    }
    for (int i = 0; i <= 36; i++) {
        gsum += g[6][i];
        printf("g[%d] = %lld\n", i, g[6][i]);
    }

    printf("fsum = %lld, gsum = %lld\n", fsum, gsum);

    double answer = 0;
    for (int i = 1; i <= 36; i++) {
        if (i > 1)
            g[6][i - 1] += g[6][i - 2];
        if (g[6][i - 1])
            answer += (f[9][i] / 262144.0) * (g[6][i - 1] / 46656.0);
    }

    printf("%.7lf\n", answer);

    return 0;
}
