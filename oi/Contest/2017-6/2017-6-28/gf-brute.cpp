#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 5000

typedef long long i64;

static int n, cnt;
static i64 seq[NMAX + 10];
static i64 sorted[NMAX + 10];
static i64 f[NMAX + 10][NMAX + 10];
static i64 g[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = n; i >= 1; i--) {
        scanf("%lld", seq + i);
    }

    memcpy(sorted, seq, sizeof(seq));
    sort(sorted + 1, sorted + n + 1);
    cnt = unique(sorted + 1, sorted + n + 1) - sorted - 1;
}

int main() {
    initialize();

    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    for (int i = 0; i <= cnt; i++) {
        f[0][i] = g[0][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= cnt; j++) {
            i64 w = 0;
            for (int l = 1; l <= i; l++) {
                w += abs(sorted[j] - seq[i - l + 1]);
                f[i][j] = min(f[i][j], g[i - l][j - 1] + w);
            }

            g[i][j] = min(g[i][j - 1], f[i][j]);
        }
    }

    printf("%lld\n", g[n][cnt]);

    return 0;
}
