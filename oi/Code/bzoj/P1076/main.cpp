#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 15
#define KMAX 100
#define SMAX (1 << NMAX)

static int n, k;
static double w[NMAX + 10];
static int req[NMAX + 10];
static double f[KMAX + 10][SMAX + 10];

static void initialize() {
    scanf("%d%d", &k, &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lf", w + i);

        int v;
        while (scanf("%d", &v) != EOF) {
            if (v == 0)
                break;

            req[i] |= 1 << (v - 1);
        }
    }
}

int main() {
    initialize();

    for (int i = k; i > 0; i--) {
        for (int s = 0; s < (1 << n); s++) {
            for (int j = 1; j <= n; j++) {
                if ((s & req[j]) == req[j])
                    f[i][s] += max(
                        f[i + 1][s],
                        f[i + 1][s | (1 << (j - 1))] + w[j]
                    );
                else
                    f[i][s] += f[i + 1][s];
            }

            f[i][s] /= n;
        }
    }

    printf("%.6lf\n", f[1][0]);

    return 0;
}
