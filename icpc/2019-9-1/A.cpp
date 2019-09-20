#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MMAX 100000
#define QMAX 100000

typedef long long i64;

static i64 bit[NMAX + 10];

inline void modify(int x, i64 v) {
    for ( ; x <= NMAX; x += x & -x) bit[x] += v;
}

inline i64 query(int x) {
    i64 r = 0;
    for ( ; x; x -= x & -x) r += bit[x];
    return r;
}

inline void clear() {
    memset(bit, 0, sizeof(bit));
}

inline i64 rev(i64 x, i64 y) {
    i64 k = max(abs(x), abs(y));
    return (2 * k) * (2 * k) +
           (x < y ? -1 : 1) * (2 * k + x + y);
}

inline i64 sum(i64 v) {
    i64 r = 0;
    for (; v; v /= 10) r += v % 10;
    return r;
}

#define POINT 0
#define QUERY1 1
#define QUERY2 -1

static int n, m, q, cnt, K;
static i64 ans[QMAX + 10];
static struct Operation {
    int t, x, y;
    i64 v;

    bool operator<(const Operation &z) const {
        return y < z.y ||
            (y == z.y && x < z.x) ||
            (y == z.y && x == z.x && t == 0);
    }
} op[6 * QMAX + 10];

inline i64 loc(i64 x, i64 y) {
    //swap(x, y);
    x -= K; y -= K;
    return i64(n) * n - rev(x, y);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        clear();
        memset(ans, 0, sizeof(ans));
        scanf("%d%d%d", &n, &m, &q);
        K = n / 2 + 1;
        cnt = 0;
        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            i64 v = sum(loc(x, y));
            op[cnt++] = {POINT, x, y, v};
            //fprintf(stderr, "x = %d, y = %d, v = %lld\n", x, y, v);
        }
        for (int i = 1; i <= q; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            op[cnt++] = {1, x2, y2, i};
            op[cnt++] = {1, x1 - 1, y1 - 1, i};
            op[cnt++] = {-1, x1 - 1, y2, i};
            op[cnt++] = {-1, x2, y1 - 1, i};
        }
        sort(op, op + cnt);
        for (int i = 0; i < cnt; i++) {
            Operation &e = op[i];
            if (e.t == POINT) modify(e.x, e.v);
            else ans[e.v] += e.t * query(e.x);
        }
        for (int i = 1; i <= q; i++)
            printf("%lld\n", ans[i]);
    }
    return 0;
}
