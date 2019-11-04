#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

static int q;

#define ACM_BEGIN
#define NMAX 300000
#define LOGN 20
static int n;
static char s[NMAX + 10];
static int fa[LOGN][NMAX + 10];
static int rk[LOGN][NMAX + 10];
static int sa[NMAX + 10], h[NMAX + 10];
void suffix_sort(int m, int i = 0) {
    static int cnt[NMAX + 10], y[NMAX + 10], b[NMAX + 10];
#define SORT(_y) \
    memset(cnt, 0, sizeof(int) * (m + 1)); \
    for (i = 0; i <= n; i++) cnt[_y[i]]++; \
    for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1]; \
    for (i = n; i >= 0; i--) b[--cnt[_y[sa[i]]]] = sa[i]; \
    memcpy(sa, b, sizeof(int) * (n + 1));
#define RANK(_rk, _x, _y) \
    for (i = 0, m = 0; i <= n; i++) { \
        m += i && (_y[sa[i]] != _y[sa[i - 1]] || _x[sa[i]] != _x[sa[i - 1]]); \
        _rk[sa[i]] = m; \
    }
    for (i = 0; i <= n; i++) sa[i] = i;
    SORT(s);
    RANK(rk[0], s, s);
    for (int k = 0; k < LOGN - 1; k++) {
        for (i = 0; i <= n; i++) fa[k + 1][i] = fa[k][fa[k][i]];
        for (i = 0; i <= n; i++) y[i] = rk[k][fa[k][i]];
        SORT(y);
        SORT(rk[k]);
        RANK(rk[k + 1], rk[k], y);
}}
int lcp(int x, int y, int r = 0) {
    for (int k = LOGN - 1; k >= 0; k--)
    if (rk[k][x] == rk[k][y]) {
        x = fa[k][x];
        y = fa[k][y];
        r += 1 << k;
    } return r;
}
#define ACM_END

struct Query {
    int *ans, L;
};

static int ans[NMAX + 10], dep[NMAX + 10];
static int stk[NMAX + 10], t;
static vector<Query> op[NMAX + 10];

#define ACM_BEGIN
int main() {
#define ACM_END
    scanf("%d%d%s", &n, &q, s + 1);

#define ACM_BEGIN
    //s[0] = 0;
    //fa[0][0] = fa[0][1] = 0;
    for (int v = 2; v <= n; v++) {
        scanf("%d", &fa[0][v]);
        dep[v] = dep[fa[0][v]] + 1;
    }
    suffix_sort(255);
    for (int i = 1; i <= n; i++)
        h[i] = min(dep[sa[i]], lcp(sa[i - 1], sa[i]));
#define ACM_END

    auto _rk = rk[LOGN - 1];
    for (int i = 1; i <= q; i++) {
        int x, L;
        scanf("%d%d", &x, &L);
        op[_rk[x]].push_back({ans + i, L});
    }

    for (int i = 1; i <= n; i++) {
        while (t && h[stk[t]] >= h[i]) t--;
        stk[++t] = i;
        for (auto &e : op[i]) {
            int l = 0, r = t;
            while (l < r) {
                int m = (l + r) / 2 + 1;
                if (h[stk[m]] < e.L) l = m;
                else r = m - 1;
            }
            *e.ans += i - stk[l];
        }
    }
    stk[t = 0] = n + 1;
    for (int i = n; i >= 1; i--) {
        if (t) {
            for (auto &e : op[i]) {
                int l = 0, r = t;
                while (l < r) {
                    int m = (l + r) / 2 + 1;
                    if (h[stk[m]] < e.L) l = m;
                    else r = m - 1;
                }
                *e.ans += stk[l] - i - 1;
            }
        }
        while (t && h[stk[t]] >= h[i]) t--;
        stk[++t] = i;
    }

    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i] + 1);
    return 0;
#define ACM_BEGIN
}
#define ACM_END
