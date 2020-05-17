#include <cstdio>
#include <cstring>

#include <vector>

using namespace std;

typedef long long i64;

#define NMAX 1000000
#define LOGN 20

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
static int rk[NMAX + 10], lcp[NMAX + 10];

void compute_lcp(const char *s, int n) {
  int j = 0, p;
  for (int i = 1; i <= n; i++, j = max(0, j - 1)) {
    if (rk[i] == 1) {
      j = 0;
      continue;
    }
    p = sa[rk[i] - 1];
    while (p + j <= n && i + j <= n && s[p + j] == s[i + j]) j++;
    lcp[rk[i]] = j;
}}

int n;
int _log[NMAX + 10];
int st[LOGN + 1][NMAX + 10];

void prepare_st() {
    _log[1] = 0;
    for (int i = 2; i <= n + 1; i++)
        _log[i] = _log[i >> 1] + 1;
    for (int i = 1; i <= n + 1; i++)
        st[0][i] = lcp[i];
    for (int j = 1; j <= LOGN; j++)
    for (int i = 1; i + (1 << (j - 1)) <= n + 1; i++)
        st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
}

int get_lcp(int i, int j) {
    i = rk[i];
    j = rk[j];
    if (i > j)
        swap(i, j);
    int k = _log[j - i];
    return min(st[k][i + 1], st[k][j - (1 << k) + 1]);
}

char buf[NMAX + 10];
int pre[NMAX + 10], nxt[NMAX + 10];
int L[NMAX + 10], R[NMAX + 10];
i64 buc[256];

void prepare_neighbor() {
    for (int i = 2; i <= n + 1; i++) {
        pre[sa[i]] = i > 2 ? sa[i - 1] : 0;
        nxt[sa[i]] = i <= n ? sa[i + 1] : 0;
    }

    for (int i = 1; i <= n; i++) {
        L[i] = pre[i];
        R[i] = nxt[i];
        nxt[pre[i]] = nxt[i];
        pre[nxt[i]] = pre[i];
    }
}

int main() {
    scanf("%s", buf + 1);
    n = strlen(buf + 1);
    for (int i = 1; i <= n; i++)
        str[i] = buf[i];
    str[n + 1] = 1;
    sais(n, 256, str, sa);

    for (int i = 1; i <= n + 1; i++)
        rk[sa[i]] = i;
    compute_lcp(buf, n + 1);
    prepare_st();
    prepare_neighbor();

    i64 ans = 0;
    for (int i = n; i >= 1; i--) {
        int c = buf[i];

        for (int z = 'a'; z <= 'z'; z++)
        if (z != c)
            ans += buc[z];

        if (L[i] && R[i] && buf[L[i]] == c && buf[R[i]] == c)
            buc[c] += get_lcp(L[i], R[i]);

        buc[c] += n + 1 - i;
        if (L[i] && buf[L[i]] == c)
            buc[c] -= get_lcp(i, L[i]);
        if (R[i] && buf[R[i]] == c)
            buc[c] -= get_lcp(i, R[i]);
    }
    ans += n + 1;
    printf("%lld\n", ans);

    return 0;
}