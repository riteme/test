#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define INF 0x3f3f3f3f

typedef long long i64;

#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define rrep(i, r, l) for (int i = (r); i >= (l); --i)
#define PUTS(x) sa[cur[str[x]]--] = x
#define PUTL(x) sa[cur[str[x]]++] = x
#define LMS(x) (!type[x - 1] && type[x])
#define RESET memset(sa + 1, 0, sizeof(int) * (n + 1)); \
    memcpy(cur + 1, cnt + 1, sizeof(int) * m);
#define INDUCE rep(i, 1, m) cur[i] = cnt[i - 1] + 1; \
    rep(i, 1, n + 1) if (sa[i] > 1 && !type[sa[i] - 1]) PUTL(sa[i] - 1); \
    memcpy(cur + 1, cnt + 1, sizeof(int) * m); \
    rrep(i, n + 1, 1) if (sa[i] > 1 && type[sa[i] - 1]) PUTS(sa[i] - 1);
void sais(int n, int m, int *str, int *sa) {
    static int id[NMAX + 10];
    vector<bool> type(n + 2);
    type[n + 1] = true;
    rrep(i, n, 1) type[i] = str[i] == str[i + 1] ? type[i + 1] : str[i] < str[i + 1];
    int cnt[m + 1], cur[m + 1], idx = 1, y = 0, rt, lrt, *ns = str + n + 2, *nsa = sa + n + 2;
    memset(cnt, 0, sizeof(int) * (m + 1));
    rep(i, 1, n + 1) cnt[str[i]]++;
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    RESET rep(i, 2, n + 1) if (LMS(i)) PUTS(i); INDUCE
    memset(id + 1, 0, sizeof(int) * n);
    rep(i, 2, n + 1) if (LMS(sa[i])) {
        int x = sa[i];
        for (rt = x + 1; !LMS(rt); rt++) ;
        id[x] = y && rt + y == lrt + x && !memcmp(str + x, str + y, sizeof(int) * (rt - x + 1)) ? idx : ++idx;
        y = x, lrt = rt;
    }
    int len = 0, pos[(n >> 1) + 1];
    rep (i, 1, n) if (id[i]) {
        ns[++len] = id[i];
        pos[len] = i;
    }
    ns[len + 1] = 1, pos[len + 1] = n + 1;
    if (len == idx - 1) rep(i, 1, len + 1) nsa[ns[i]] = i;
    else sais(len, idx, ns, nsa);
    RESET; rrep(i, len + 1, 1) PUTS(pos[nsa[i]]); INDUCE
}

#define R 0
#define L 1

static int n, P, Q;
static char buf[NMAX + 10];
static int str[NMAX * 3 + 10], sa[NMAX * 3 + 10];
static int lcp[NMAX + 10], rk[NMAX + 10];
static int fa[2][NMAX + 10], mi[2][NMAX + 10];
static int K[NMAX + 10];

int find(int i, int x) {
    int p = fa[i][x];
    if (!p) return x;
    fa[i][x] = find(i, p);
    mi[i][x] = min(mi[i][x], mi[i][p]);
    return fa[i][x];
}

void initialize() {
    for (int i = n; i >= 1; i--)
        str[n - i + 1] = buf[i] - 'a' + 2;
    str[n + 1] = 1;
    sais(n, 256, str, sa);
    for (int i = 1; i <= n + 1; i++)
        rk[sa[i]] = i;

    int j = 0, p;
    for (int i = 1; i <= n + 1; i++, j = max(0, j - 1)) {
        if (rk[i] == 1) {
            j = 0;
            continue;
        }
        p = sa[rk[i] - 1];
        while (p + j <= n + 1 && i + j <= n + 1 && str[p + j] == str[i + j])
            j++;
        lcp[rk[i]] = j;
    }
    memset(fa[L] + 1, 0, sizeof(int) * (n + 2));
    memset(fa[R] + 1, 0, sizeof(int) * (n + 2));
    memset(mi[L] + 1, 0x3f, sizeof(int) * (n + 2));
    memset(mi[R] + 1, 0x3f, sizeof(int) * (n + 2));
    mi[L][1] = mi[R][n + 2] = 0;
}

bool chk(int i, int k) {
    int x = rk[n + 1 - i - k + 1];
    find(L, x);
    find(R, x);
    return max(mi[L][x], mi[R][x]) >= k;
}

static i64 dp[NMAX + 10];

int main() {
    while (scanf("%s", buf + 1) != EOF) {
        scanf("%d%d", &P, &Q);
        n = strlen(buf + 1);
        initialize();

        K[n + 1] = 0;
        for (int i = n; i >= 1; i--) {
            int x = rk[n + 1 - i];
            mi[L][x] = lcp[x];
            fa[L][x] = x - 1;
            mi[R][x] = lcp[x + 1];
            fa[R][x] = x + 1;
            K[i] = K[i + 1] + 1;
            while (K[i] && !chk(i, K[i]))
                K[i]--;
        }

        /*
        for (int i = 1; i <= n; i++)
            printf("%d ", K[i]);
        puts("");
        for (int i = 1; i <= n; i++)
            printf("%c ", str[n + 1 - i] - 2 + 'a');
        puts("");
        */

        memset(dp + 1, 0x3f, sizeof(i64) * n);
        dp[1] = P;
        for (int i = 1; i < n; i++) {
            dp[i + 1] = min(dp[i + 1], dp[i] + P);
            int j = i + K[i + 1];
            if (j <= n)
                dp[j] = min(dp[j], dp[i] + Q);
        }
        printf("%lld\n", dp[n]);
    }

    return 0;
}
