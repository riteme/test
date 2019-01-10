#include <cstdio>
#include <cstring>

#define NMAX 1000000

typedef long long i64;

static int n, m, fa[NMAX + 10], seq[NMAX + 10], w[NMAX + 10];
static i64 cnt[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(cnt + 1, 0, sizeof(i64) * n);
        int t = 0;
        m = 0;
        for (int i = 2; i <= n; i++) {
            scanf("%d%d", fa + i, w + i);
            cnt[fa[i]] += w[i];
        }
        for (int i = 1; i <= n; i++) if (t += cnt[i] & 1;
        if (t & 1) {
            for (int i = 1; i <= n; i++) {
                if (!cnt[i] && fa[i] && (cnt[fa[i]] & 1)) seq[++m] = i;
                if (cnt[i] && (w[i] & 1)) seq[++m] = i;
            }
            printf("%d\n", m);
            for (int i = 1; i <= m; i++) printf("%d ", seq[i]);
            puts("");
        } else puts("0");
    }
    return 0;
}
