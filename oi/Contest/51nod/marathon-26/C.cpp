/**
 * 思路：分治
 * 考虑两种情况：
 *  1. max/min均在一侧：可以直接判定
 *  2. max/min分开在两侧，则max要么在左侧，要么在右侧
 *  如果max在左侧，则需要满足max - min = j - i => max + i = min + j
 *  同时min_i和max_j也要满足相应的要求，单调移动时这个也是单调的
 */

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 1000000
#define OFF NMAX

static int n;
static int a[NMAX + 10];
static int mx[NMAX + 10], mn[NMAX + 10];
static int cnt[NMAX * 2 + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
}

i64 solve(int l, int r) {
    if (l == r)
        return 1;

    int m = (l + r) >> 1;
    i64 ret = solve(l, m) + solve(m + 1, r);

    mx[m] = mn[m] = a[m];
    mx[m + 1] = mn[m + 1] = a[m + 1];
    for (int i = m - 1; i >= l; i--) {
        mx[i] = max(mx[i + 1], a[i]);
        mn[i] = min(mn[i + 1], a[i]);
    }

    for (int i = m + 2; i <= r; i++) {
        mx[i] = max(mx[i - 1], a[i]);
        mn[i] = min(mn[i - 1], a[i]);
    }

    // max in left
    int a = r, b = r;
    for (int i = l; i <= m; i++) {
        int p = i + mx[i] - mn[i];
        if (m < p && p <= r && mn[i] < mn[p] && mx[p] < mx[i])
            ret++;

        for (; a >= m && mn[i] > mn[a]; a--)
            cnt[mn[a] + a]++;
        for (; b > a && mx[i] < mx[b]; b--)
            cnt[mn[b] + b]--;

        ret += cnt[mx[i] + i];
    }

    for (int i = m + 1; i <= r; i++) {
        cnt[mn[i] + i] = 0;
    }

    // max in right
    a = l, b = l;
    for (int i = r; i > m; i--) {
        int p = i - mx[i] + mn[i];
        if (l <= p && p <= m && mn[i] < mn[p] && mx[p] < mx[i])
            ret++;
        for (; b <= m && mn[i] > mn[b]; b++)
            cnt[mn[b] - b + OFF]++;
        for (; a < b && mx[i] < mx[a]; a++)
            cnt[mn[a] - a + OFF]--;

        ret += cnt[mx[i] - i + OFF];
    }

    for (int i = l; i <= m; i++) {
        cnt[mn[i] - i + OFF] = 0;
    }

    return ret;
}

int main() {
    initialize();
    printf("%lld\n", solve(1, n));

    return 0;
}
