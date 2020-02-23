#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 500000
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

static int n;
static i64 L, R;
static i64 a[NMAX + 10];
static i64 d[NMAX + 10];

struct State {
    i64 u, t;

    bool operator<(const State &z) const {
        return t > z.t;
    }
};

int main() {
    scanf("%d%lld%lld", &n, &L, &R);
    for (int i = 0; i < n; i++)
        scanf("%lld", a + i);
    sort(a, a + n);
    int j = 0;
    for ( ; !a[j]; j++) ;

    memset(d, 0x3f, sizeof(i64) * a[j]);
    d[0] = 0;
    priority_queue<State> q;
    q.push({0, 0});
    while (!q.empty()) {
        auto _ = q.top();
        q.pop();
        if (_.t > d[_.u])
            continue;
        i64 u = _.u;
        for (int i = j + 1; i < n; i++) {
            i64 v = (u + a[i]) % a[j];
            if (d[v] > d[u] + a[i]) {
                d[v] = d[u] + a[i];
                q.push({v, d[v]});
            }
        }
    }

    i64 ans = 0;
    for (i64 i = 0; i < a[j]; i++) if (d[i] <= R) {
        i64 l = max(0LL, (L - d[i] + a[j] - 1) / a[j]);
        i64 r = (R - d[i]) / a[j];
        //printf("d[%lld] = %lld, l = %lld, r = %lld\n", i, d[i], l, r);
        ans += r - l + 1;
    }

    printf("%lld\n", ans);
    return 0;
}
