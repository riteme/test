#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500000

typedef long long i64;

int n, q;
int val[NMAX + 10];
char col[NMAX + 10];

i64 gn, vn;
i64 gc[NMAX + 10], vc[NMAX + 10];

void modify(i64 *a, int x, i64 v) {
    for ( ; x <= NMAX; x += x & -x)
        a[x] += v;
}

i64 query(i64 *a, int x) {
    i64 r = 0;
    for ( ; x; x -= x & -x)
        r += a[x];
    return r;
}

int main() {
    scanf("%d%d%s", &n, &q, col + 1);
    for (int i = 1; i <= n; i++) {
        val[i] = 1;
        if (col[i] == 'G') {
            gn++;
            modify(gc, 1, 1);
        } else {
            vn++;
            modify(vc, 1, 1);
        }
    }

    i64 ans = 0;
    while (q--) {
        int i, d;
        scanf("%d%d", &i, &d);
        if (col[i] == 'G') {
            ans -= vn - query(vc, val[i]);
            modify(gc, val[i], -1);
            val[i] += d;
            ans += vn - query(vc, val[i]);
            modify(gc, val[i], +1);
        } else {
            ans -= query(gc, val[i] - 1);
            modify(vc, val[i], -1);
            val[i] += d;
            ans += query(gc, val[i] - 1);
            modify(vc, val[i], +1);
        }

        printf("%lld\n", ans);
    }

    return 0;
}