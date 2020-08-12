#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 2000

typedef long long i64;

struct item_t {
    i64 t, w;

    bool operator<(const item_t &z) const {
        return t > z.t;
    }
};

int n, T;
item_t a[NMAX + 10], s[NMAX + 10];
i64 f[NMAX + 10];

int main() {
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &a[i].t, &a[i].w);
    }
    sort(a + 1, a + n + 1);
    for (int i = n; i >= 1; i--) {
        s[i].t = s[i + 1].t + a[i].t;
        s[i].w = s[i + 1].w + a[i].w;
    }

    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    i64 ans = s[1].t <= T ? s[1].w : LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            for (int j = T - a[i - 1].t; j >= 0; j--) {
                f[j + a[i - 1].t] = min(f[j + a[i - 1].t], f[j] + a[i - 1].w);
            }
        }

        for (int j = T; j >= 0 && j + s[i + 1].t > T - a[i].t; j--) {
            ans = min(ans, f[j] + s[i + 1].w);
        }
    }
    printf("%lld\n", ans);

    return 0;
}
