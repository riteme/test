#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long i64;

static int n, m, K;
static bool cov[NMAX + 10];
static int pre[NMAX + 10];
static int loc[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        cov[x] = true;
    }
    int lp = 0;
    for (int i = 0; i <= n; i++) {
        if (!cov[i]) lp = i;
        pre[i] = lp;
    }

    i64 ans = LLONG_MAX;
    for (int k = 1; k <= K; k++) {
        i64 c, sum = 0;
        scanf("%lld", &c);
        int i = 0, t = 0;
        while (sum >= 0 && i < n) {
            if (cov[i]) {
                if (cov[pre[i]]) sum = -1;
                else i = pre[i];
            } else {
                cov[i] = true;
                loc[t++] = i;
                sum += c;
                i += k;
            }
        }
        for (int i = 0; i < t; i++)
            cov[loc[i]] = false;
        if (sum >= 0) ans = min(ans, sum);
    }
    if (ans == LLONG_MAX) puts("-1");
    else printf("%lld\n", ans);

    return 0;
}
