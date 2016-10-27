#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 500
#define MMAX 30000
#define TMAX 30000

static int n, m, tmin, tmax;
static int X[MMAX + 10];
static int T[MMAX + 10];
static int f[TMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d", X + i);
    }

    tmin = INT_MAX;
    for (int i = 1; i <= m; i++) {
        scanf("%d", T + i);

        tmin = min(tmin, T[i]);
        tmax = max(tmax, T[i]);
    }
}

int main() {
    freopen("fruit.in", "r", stdin);
    freopen("fruit.out", "w", stdout);
    initialize();
    
    for (int i = 1; i <= m; i++)
        f[T[i]][X[i]] = 1;

    for (int t = tmin; t <= tmax; t++) {
        for (int x = 1; x <= n; x++) {
            f[t][x] += max(f[t - 1][x],
                           max(f[t - 1][x - 1], f[t - 1][x + 1])
                          );
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; i++)
        answer = max(answer, f[tmax][i]);

    printf("%d\n", answer);

    return 0;
}
