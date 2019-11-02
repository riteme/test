#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500000

static int n, m;
static struct Point {
    int x, v;

    bool operator<(const Point &z) const {
        return x < z.x || (x == z.x && v < z.v);
    }
} p[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        m = 0;
        for (int i = 1; i <= n; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            p[m++] = {l, 1};
            p[m++] = {r + 1, -1};
        }
        sort(p, p + m);
        int ans = 0;
        for (int i = 0, s = 0; i < m; i++) {
            s += p[i].v;
            ans = max(ans, s);
        }
        printf("%d\n", ans);
    }
    return 0;
}
