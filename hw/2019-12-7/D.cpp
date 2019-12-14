#include <cstdio>
#include <cstring>

#include <set>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long i64;

static int W, H, n;
static set<int> xs, ys;
static i64 ans[NMAX + 10];
static char op[NMAX + 10][2];
static int pos[NMAX + 10];

int main() {
    scanf("%d%d%d", &W, &H, &n);
    ys.insert(0);
    ys.insert(H);
    xs.insert(0);
    xs.insert(W);
    for (int i = 1; i <= n; i++) {
        scanf("%s%d", op[i], pos + i);
        if (op[i][0] == 'H') ys.insert(pos[i]);
        else xs.insert(pos[i]);
    }

    i64 xm = 0, ym = 0;
    for (auto pre = xs.begin(), cur = next(xs.begin());
         cur != xs.end(); pre++, cur++)
        xm = max(xm, static_cast<i64>(*cur - *pre));
    for (auto pre = ys.begin(), cur = next(ys.begin());
         cur != ys.end(); pre++, cur++)
        ym = max(ym, static_cast<i64>(*cur - *pre));
    for (int i = n; i >= 1; i--) {
        ans[i] = xm * ym;
        if (op[i][0] == 'H') {
            auto it = ys.find(pos[i]);
            ym = max(ym, static_cast<i64>(*next(it) - *prev(it)));
            ys.erase(it);
        } else {
            auto it = xs.find(pos[i]);
            xm = max(xm, static_cast<i64>(*next(it) - *prev(it)));
            xs.erase(it);
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);

    return 0;
}
