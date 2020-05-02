#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define XMIN -1000'000'010
#define XMAX 1000'000'000

int n, m;
struct Event {
    int x, v;

    bool operator<(const Event &z) const {
        return x < z.x;
    }
} ev[NMAX * 3 + 10];
int xs[NMAX * 3 + 10], t;

void initialize() {
    scanf("%d", &n);
    m = t = 0;
    for (int i = 0; i < n; i++) {
        char op[8], ret[8];
        int a;
        scanf("%s%d%s", op, &a, ret);

        if (op[0] == '=') {
            xs[t++] = a - 1;
            xs[t++] = a;
            xs[t++] = a + 1;
            if (ret[0] == 'T') {
                ev[m++] = {XMIN, +1};
                ev[m++] = {a, -1};
                ev[m++] = {a + 1, +1};
            } else {
                ev[m++] = {a, +1};
                ev[m++] = {a + 1, -1};
            }
        } else if (op[0] == '>') {
            xs[t++] = a;
            xs[t++] = a + 1;
            if (ret[0] == 'T') {
                ev[m++] = {XMIN, +1};
                ev[m++] = {a + 1, -1};
            } else {
                ev[m++] = {a + 1, +1};
            }
        } else {
            xs[t++] = a - 1;
            xs[t++] = a;
            if (ret[0] == 'T') {
                ev[m++] = {a, +1};
            } else {
                ev[m++] = {XMIN, +1};
                ev[m++] = {a, -1};
            }
        }
    }

    sort(ev, ev + m);
    sort(xs, xs + t);
}

void solve() {
    initialize();

    int ans = INT_MAX, sum = 0;
    for (int i = 0, p = 0; i < t; i++) {
        int x = min(XMAX, max(1, xs[i]));
        while (p < m && ev[p].x <= x)
            sum += ev[p++].v;
        ans = min(ans, sum);
    }

    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}