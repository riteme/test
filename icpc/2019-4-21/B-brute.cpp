#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 2000

static int n, q, K, pt[NMAX + 10];
static i64 seq[NMAX + 10], pre[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &q, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
        pre[i] = pre[i - 1] + seq[i];
    }
    pt[K + 1] = n + 1;
    while (q--) {
        for (int i = 1; i <= K; i++) scanf("%d", pt + i);
        i64 ans = 0;
        for (int i = 1; i <= K + 1; i++)
            ans += pre[pt[i] - 1] - pre[pt[i - 1]];
        printf("! %lld\n", ans);
    }
    return 0;
}
