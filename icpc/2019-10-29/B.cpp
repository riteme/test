#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long i64;

struct State {
    int i;
    double d;

    bool operator<(const State &z) const {
        return d < z.d;
    }
};

static int n, m;
static i64 a[NMAX + 10];
static i64 c[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++) {
        scanf("%d%d", &n, &m);
        i64 S = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", a + i);
            S += a[i];
            a[i] *= a[i];
        }

        double v = 0;
        priority_queue<State> q;
        for (int i = 1; i <= n; i++) {
            c[i] = 1;
            v += (double) a[i] / c[i];
            q.push({i, (double) a[i] / c[i] / (c[i] + 1)});
        }

        for (int j = n + 1; j <= m; j++) {
            State u = q.top();
            int i = u.i;
            q.pop();
            v -= (double) a[i] / c[i];
            c[i]++;
            v += (double) a[i] / c[i];
            q.push({i, (double) a[i] / c[i] / (c[i] + 1)});
        }

        double ans = v / m - (double) S * S / m / m;
        printf("Case #%d: %.12lf\n", _t, ans);
    }
    return 0;
}
