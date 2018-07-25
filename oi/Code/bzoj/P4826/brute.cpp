#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000

static int n, m;
static i64 p1, p2;
static int P[NMAX + 10];

void initialize() {
    scanf("%d%d%lld%lld", &n, &m, &p1, &p2);

    for (int i = 1; i <= n; i++) {
        scanf("%d", P + i);
    }
}

i64 query(int l, int r) {
    i64 cnt1 = 0, cnt2 = 0;

    for (int i = l; i <= r; i++) {
        int maxv = 0;
        for (int j = i + 1; j <= r; j++) {
            if (P[i] > maxv && P[j] > maxv)
                cnt2++;
            if (P[i] > maxv || P[j] > maxv)
                cnt1++;
            maxv = max(maxv, P[j]);
        }
    }

    return cnt2 * p1 + (cnt1 - cnt2) * p2;
}

int main() {
    initialize();

    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", query(l, r));
    }

    return 0;
}
