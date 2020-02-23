#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define DMAX 100
#define NMAX 20000
#define MOD 1000000007

int D, n;
int d[NMAX + 10], t[NMAX + 10];
int c[DMAX + 10], a[DMAX + 10];
int s[DMAX + 10];

void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

void initialize() {
    scanf("%d%d", &D, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", d + i);
    for (int i = 1; i <= D; i++) {
        int _;
        scanf("%d%d%d", c + i, a + i, &_);
        d[n + 1] += a[i];
        t[c[i]] = _;
    }
    d[n + 1]++;

    for (int i = 1; i <= n; i++)
        if (!t[i]) d[0] = max(d[0], d[i]);
    memcpy(s, c, sizeof(s));
    s[D + 1] = n + 1;
    sort(s, s + D + 2, [](int i, int j) {
        return d[i] + t[i] < d[j] + t[j];
    });
}

int f[NMAX + 10];

int main() {
    initialize();

    int ans = 0;
    for (int i = 0; i <= D; i++) {
        int cur = d[s[i]] + t[s[i]];
        if (cur < d[0] || cur >= d[n + 1])
            continue;

        memset(f, 0, sizeof(f));
        f[0] = 1;
        for (int j = 1; j <= D; j++) {
            if (d[c[j]] + t[c[j]] > cur)
                memset(f, 0, sizeof(int) * d[c[j]]);
            for (int k = NMAX; k >= a[j]; k--)
                add(f[k], f[k - a[j]]);
        }

        for (int j = cur; j < d[s[i + 1]] + t[s[i + 1]]; j++)
            add(ans, f[j]);
    }

    printf("%d\n", ans);
    return 0;
}