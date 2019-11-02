#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long i64;

static int n;
static i64 cnt[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld", cnt + i);
        for (int i = n; i >= 1; i--)
            cnt[i] -= cnt[i - 1];
        i64 sum = 0;
        bool ok = true;
        for (int i = 1; ok && i <= n; i++) {
            if (i > 3)
                sum += cnt[i - 3];
            if (cnt[i] < 0) {
                sum += cnt[i];
                ok &= sum >= 0;
                cnt[i] = 0;
            }
        }
        if (n >= 2)
            ok &= cnt[n - 1] == 0;
        ok &= cnt[n] == 0;
        printf("Case #%d: %s\n", _t, (ok ? "Yes" : "No"));
    }
    return 0;
}
