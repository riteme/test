#include <cstdio>
#include <cstring>
#include <climits>

#include <bitset>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 1000000;
constexpr int KMAX = 60;

using bits = bitset<NMAX + 10>;

struct ran {
    int l, r, w, t;
};

int n, q;
ran p[NMAX + 10];
bits mask;

int cnt[NMAX + 10];
int pre0[NMAX + 10], pre1[NMAX + 10];
int lt[NMAX + 10], rt[NMAX + 10];

void solve() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= q; i++) if (p[i].w == 1) {
        cnt[p[i].l]++;
        cnt[p[i].r + 1]--;
    }

    memset(pre0, 0, sizeof(pre0));
    memset(pre1, 0, sizeof(pre1));
    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
        if (cnt[i] == 0)
            pre0[i]++;
        else if (cnt[i] == 1)
            pre1[i]++;

        pre0[i] += pre0[i - 1];
        pre1[i] += pre1[i - 1];
    }

    int c1 = 0, c2 = 0;
    for (int i = 1; i <= q; i++) if (p[i].w == 0) {
        if (pre0[p[i].r] - pre0[p[i].l - 1] > 0)
            p[i].t = 0;
        else if (pre1[p[i].r] - pre1[p[i].l - 1] > 0) {
            p[i].t = 1;
            c1++;
        } else {
            p[i].t = 2;
            c2++;
        }
    }

    if (c1 == 0 && c2 == 0) {
        for (int i = 1; i <= q; i++) {
            mask[i] = 1;
        }
        return;
    }

    if (c2 > 0 && c1 + c2 > 1)
        return;

    if (c2 == 0 && c1 > 0) {
        int lp = 0;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == 1)
                lp = i;
            lt[i] = lp;
        }

        lp = 0;
        for (int i = n; i >= 1; i--) {
            if (cnt[i] == 1)
                lp = i;
            rt[i] = lp;
        }

        int L = INT_MAX, R = INT_MIN;
        for (int i = 1; i <= q; i++)
        if (p[i].w == 0 && p[i].t == 1) {
            L = min(L, lt[p[i].r]);
            R = max(R, rt[p[i].l]);
        };

        for (int i = 1; i <= q; i++)
        if (p[i].w == 1) {
            if (p[i].l <= L && p[i].r >= R)
                mask[i] = 1;
        }
    }

    if (c1 + c2 == 1) {
        for (int i = 1; i <= q; i++)
        if (p[i].w == 0 && p[i].t > 0) {
            mask[i] = 1;
            break;
        }
    }
}

i64 w[NMAX + 10];
bits ans;

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d%lld", &p[i].l, &p[i].r, w + i);
        ans[i] = 1;
    }

    for (int k = 0; k <= KMAX; k++) {
        for (int i = 1; i <= q; i++) {
            p[i].w = (w[i] >> k) & 1;
        }

        mask.reset();
        solve();

        ans &= mask;
    }

    for (int i = 1; i <= q; i++) {
        putchar(ans[i] ? '1' : '0');
    }
    puts("");

    return 0;
}