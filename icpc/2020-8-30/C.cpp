#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define MMAX 100010
#define NMAX 200010

#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define rrep(i, r, l) for (int i = (r); i >= (l); i--)
#define PUTS(x) sa[cur[str[x]]--] = x;
#define PUTL(x) sa[cur[str[x]]++] = x;
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
    RESET rep(i, 2, n + 1) if (LMS(i)) PUTS(i); INDUCE;
    memset(id + 1, 0, sizeof(int) * (n + 1));
    rep(i, 2, n + 1) if (LMS(sa[i])) {
        int x = sa[i];
        for (rt = x + 1; !LMS(rt); rt++) ;
        id[x] = y && rt + y == lrt + x && !memcmp(str + x, str + y, sizeof(int) * (rt - x + 1)) ? idx : ++idx;
        y = x, lrt = rt;
    }
    int len = 0, pos[(n >> 1) + 1];
    rep(i, 1, n) if (id[i]) {
        ns[++len] = id[i];
        pos[len] = i;
    }
    ns[len + 1] = 1, pos[len + 1] = n + 1;
    if (len == idx - 1) rep(i, 1, len + 1) nsa[ns[i]] = i;
    else sais(len, idx, ns, nsa);
    RESET rrep(i, len + 1, 1) PUTS(pos[nsa[i]]); INDUCE;
}

int lcp[NMAX + 10], rk[NMAX + 10], sa[NMAX * 3 + 10];

void compute_lcp(int *s, int n) {
    int j = 0, p;
    for (int i = 1; i <= n; i++, j = max(0, j - 1)) {
        if (rk[i] == 1) {
            j = 0;
            continue;
        }
        p = sa[rk[i] - 1];
        while (p + j <= n && i + j <= n && s[p + j] == s[i + j]) {
            j++;
        }
        lcp[rk[i]] = j;
    }
}

char ds[MMAX + 10];
int nxt[MMAX + 10];
int str[NMAX * 3 + 10];

void _main() {
    scanf("%s", ds + 1);
    int n = strlen(ds + 1);
    for (int i = 1; i <= n; i++) {
        str[i] = str[n + i] = ds[i];
    }
    str[2 * n + 1] = 1;
    sais(2 * n, 255, str, sa);
    for (int i = 1; i <= 2 * n + 1; i++) {
        rk[sa[i]] = i;
    }

    compute_lcp(str, 2 * n + 1);

    nxt[1] = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && ds[j + 1] != ds[i]) {
            j = nxt[j];
        }
        if (ds[j + 1] == ds[i])
            j++;
        nxt[i] = j;
    }

    int cnt = 0;
    for (int i = 1, j = 0; i <= 2 * n; i++) {
        while (j && str[i] != ds[j + 1]) {
            j = nxt[j];
        }
        if (str[i] == str[j + 1])
            j++;
        if (j == n) {
            cnt++;
            j = nxt[j];
        }
    }
    //printf("cnt = %d\n", cnt);
    int rp = rk[n + 1];
    int lt = 0, eq = 1, gt = 0;
    int mi = 0;
    for (int i = 1; i <= 2 * n + 1; i++) {
        mi = min(mi, lcp[i]);
        int j = sa[i];
        if (j <= n) {
            if (mi < n) {
                if (i < rp)
                    lt++;
                else
                    gt++;
            }
            mi = INT_MAX;
        }
    }
    if (cnt > 1)
        gt--;

    printf("%d %d %d\n", lt, eq, gt);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case %d: ", i);
        _main();
    }
    return 0;
}
