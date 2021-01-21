#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

constexpr int NMAX = 500000;

int n;
int a[NMAX + 10];
bool black[NMAX + 10];
int stk[NMAX + 10], p;

struct ran_t {
    int l, r;

    bool operator<(const ran_t &z) const {
        return l < z.l || (l == z.l && r > z.r);
    }
} ran[NMAX + 10];

int mi[NMAX + 10];

void modify_mi(int x, int v) {
    for ( ; x; x -= x & -x) {
        mi[x] = min(mi[x], v);
    }
}

int query_mi(int l) {
    int r = INT_MAX;
    for ( ; l <= n; l += l & -l) {
        r = min(r, mi[l]);
    }
    return r;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        mi[i] = INT_MAX;
    }

    int hi = 0;
    for (int i = 1; i <= n; i++) {
        while (p > 0) {
            if (a[i] < a[stk[p]]) {
                if (black[stk[p]]) {
                    puts("-1");
                    return 0;
                }

                black[i] = true;
                p--;
            } else if (a[i] < a[hi]) {
                black[i] = true;
                break;
            } else {
                hi = i;
                break;
            }
        }

        stk[++p] = i;

        if (black[i])
            ran[i] = {query_mi(a[i]), i};
        else
            ran[i] = {i, i};

        modify_mi(a[i], i);
    }

    sort(ran + 1, ran + n + 1);

    int cnt[2], ans = 0;
    for (int j = 1, k; j <= n; j = k) {
        int l = ran[j].l, r = ran[j].r;
        for (k = j + 1; k <= n && ran[k].l <= r; k++) {
            r = max(r, ran[k].r);
        }

        cnt[0] = cnt[1] = 0;
        for (int i = l; i <= r; i++) {
            cnt[black[i]]++;
        }

        int a = max(cnt[0], cnt[1]);
        int b = min(cnt[0], cnt[1]);
        ans += a - b;
    }

    printf("%d\n", ans);
    return 0;
}
