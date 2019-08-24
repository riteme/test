#include <cstdio>
#include <cstring>
#include <cctype>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 1000000

#define ACM_BEGIN
#define rep(i, l, r) for (register int i = (l); i <= (r); ++i)
#define rrep(i, r, l) for (register int i = (r); i >= (l); --i)
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
        register int x = sa[i];
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
    RESET rrep(i, len + 1, 1) PUTS(pos[nsa[i]]); INDUCE
}
static int str[NMAX * 3 + 10], sa[NMAX * 3 + 10];
#define ACM_END

int main() {
    ios::sync_with_stdio(false);
    static char buffer[NMAX + 10];
    cin >> buffer;
    int n = 0;
    for (; buffer[n]; n++) str[n + 1] = buffer[n];
    str[n + 1] = 1;
    sais(n, 127, str, sa);
    rep(i, 2, n + 1) cout << sa[i] << ' ';
    return 0;
}
