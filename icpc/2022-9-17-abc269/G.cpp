#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;
constexpr int INF = 0x3f3f3f3f;

int n, m;
int a[NMAX + 10], b[NMAX + 10];
int f[2 * NMAX + 10];

void dp(int v, int t) {
    if (v > 0) {
        for (int i = m; i >= -m; i--) {
            if (m + i - v >= 0 && f[m + i] > f[m + i - v] + t)
                f[m + i] = f[m + i - v] + t;
        }
    } else {
        for (int i = -m; i <= m; i++) {
            if (m + i - v <= 2 * m && f[m + i] > f[m + i - v] + t)
                f[m + i] = f[m + i - v] + t;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", a + i, b + i);
    }
    memset(f, 0x3f, sizeof(f));
    f[m] = 0;

    int s0 = 0;
    for (int i = 1; i <= n; i++) {
        s0 += a[i];
        a[i] = b[i] - a[i];
    }

    sort(a + 1, a + n + 1);
    for (int i = a[1], j = 1; i <= a[n]; i++) {
        int k = j;
        while (k <= n && a[k] == i) {
            k++;
        }
        if (j == k)
            continue;
        if (i != 0) {
            int c = k - j;
            for (int t = 1; t <= c; t <<= 1) {
                dp(t * i, t);
                c -= t;
            }
            if (c) {
                dp(c * i, c);
            }
        }
        j = k;
    }

    for (int j = -s0; j <= m - s0; j++) {
        int i = m + j;
        if (f[i] < INF)
            printf("%d\n", f[i]);
        else
            puts("-1");
    }

    return 0;
}
