#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>

#include <vector>
#include <algorithm>

using namespace std;

#define LOGN 20
#define NMAX 1000000
#define MEMSIZE ((LOGN + 2) * NMAX)

int sa[NMAX + 10], rk[NMAX + 10], lcp[NMAX + 10];

void suffix_sort(int *s, int n, int m) {
    static int x[NMAX + 10], y[NMAX + 10], cnt[NMAX + 10], i;
    memset(cnt, 0, sizeof(int) * (m + 1));
    for (i = 0; i < n; i++) cnt[s[i]]++;
    for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (i = 0; i < n; i++) sa[--cnt[s[i]]] = i;
    for (i = 1, m = 1, rk[sa[0]] = 1; i < n; i++) {
        if (s[sa[i - 1]] != s[sa[i]]) m++;
        rk[sa[i]] = m;
    }
    for (int L = 1; L < n; L <<= 1) {
        memset(cnt, 0, sizeof(int) * (m + 1));
        for (i = 0; i < n; i++) cnt[y[i] = i + L < n ? rk[i + L] : 0]++;
        for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; i--) x[--cnt[y[i]]] = i;
        memset(cnt, 0, sizeof(int) * (m + 1));
        for (i = 0; i < n; i++) cnt[rk[i]]++;
        for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--cnt[rk[x[i]]]] = x[i];
        for (i = 1, m = 1, x[sa[0]] = 1; i < n; i++) {
            if (rk[sa[i - 1]] != rk[sa[i]] || y[sa[i - 1]] != y[sa[i]]) m++;
            x[sa[i]] = m;
        }
        memcpy(rk, x, sizeof(int) * n);
    }
}

void compute_lcp(int *s, int n) {
    int j = 0, p;
    for (int i = 0; i < n; i++, j = max(0, j - 1)) {
        if (rk[i] == 1) {
            j = 0;
            continue;
        }
        p = sa[rk[i] - 2];
        while (p + j < n && i + j < n && s[p + j] == s[i + j]) j++;
        lcp[rk[i]] = j;
    }
}

int _log[NMAX + 10];
int st[LOGN + 1][NMAX + 10];

void compute_st(int n) {
    for (int i = 0; i < n; i++) {
        st[0][i] = lcp[i];
    }
    for (int j = 1; j <= _log[n]; j++)
    for (int i = 0; i < n; i++)
    if (i + (1 << (j - 1)) < n) {
        st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    } else {
        st[j][i] = st[j - 1][i];
    }
}

int query(int l, int r) {
    int len = r - l + 1;
    int k = _log[len];
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}

int pa[NMAX + 10];
vector<int> T[NMAX + 10];

void compute_rkmp(int *s, int n) {
    pa[n - 1] = n;
    int j = n;
    for (int i = n - 2; i >= 0; i--) {
        while (j < n && s[i] != s[j - 1]) {
            j = pa[j];
        }
        if (s[i] == s[j - 1])
            j--;
        pa[i] = j;
    }
}

struct Node {
    int cnt;
    // Node *lch, *rch;
    int lch, rch;
};

size_t mempos;
Node o[MEMSIZE];
int tr[NMAX + 10];

int allocate() {
    int p = mempos;
    mempos++;
    memset(o + p, 0, sizeof(Node));
    return p;
}

int build(int L, int R) {
    int x = allocate();

    if (L < R) {
        int mi = (L + R) / 2;
        o[x].lch = build(L, mi);
        o[x].rch = build(mi + 1, R);
    }

    return x;
}

int modify(int x, int l, int r, int p) {
    int _ = x;
    x = allocate();
    memcpy(o + x, o + _, sizeof(Node));

    o[x].cnt++;
    if (l < r) {
        int mi = (l + r) / 2;
        if (p <= mi)
            o[x].lch = modify(o[x].lch, l, mi, p);
        else
            o[x].rch = modify(o[x].rch, mi + 1, r, p);
    }

    return x;
}

int query(int x, int l, int r, int p) {
    if (l == r)
        return 0;

    int mi = (l + r) / 2;
    if (p <= mi)
        return query(o[x].lch, l, mi, p);
    else
        return o[o[x].lch].cnt + query(o[x].rch, mi + 1, r, p);
}

int n, m, q;
int s[NMAX + 10];
int sc[NMAX + 10];

void dfs(int x) {
    int len = n - x;
    for (int i = 0; i < T[x].size(); i++) {
        int v = T[x][i];

        if (x < n)
            tr[v] = modify(tr[x], 1, m, s[v + len]);
        else
            tr[v] = tr[x];

        dfs(v);
    }
}

void compute_tree() {
    for (int i = 0; i < n; i++) {
        T[i].clear();
    }

    for (int i = 0; i < n; i++) {
        T[pa[i]].push_back(i);
    }

    mempos = 1;
    tr[n] = build(1, m);
    dfs(n);
}

// FILE *fp = fopen("B.out", "r");

void _main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", s + i);
    }
    s[n] = 0;

    memcpy(sc, s, sizeof(int) * n);
    sort(sc, sc + n);
    sc[n] = INT_MAX;

    suffix_sort(s, n + 1, m);
    compute_lcp(s, n + 1);
    for (int i = 0; i <= n; i++) {
        lcp[i] = lcp[i + 1];
    }
    compute_st(n + 1);
    compute_rkmp(s, n);
    compute_tree();

    int lastans = 0;
    while (q--) {
        int op, c, p;
        scanf("%d%d%d", &op, &c, &p);

        c ^= lastans;
        p ^= lastans;

        // fprintf(stderr, "op=%d, char=%d, pos=%d\n", op, c, p);

        if (op == 1) {
            if (p == 1) {
                int l = 0, r = n;
                while (l < r) {
                    int mi = (l + r) / 2 + 1;
                    bool cmp;
                    if (s[sa[mi]] != c)
                        cmp = s[sa[mi]] < c;
                    else
                        cmp = rk[sa[mi] + 1] < rk[0];
                    if (cmp)
                        l = mi;
                    else
                        r = mi - 1;
                }
                lastans = l + 1;
            } else {
                p -= 2;
                lastans = rk[p] - 1;
                if (c < s[p] || (c == s[p] && rk[0] < rk[p]))
                    lastans++;
            }
        } else {
            if (p == n + 1) {
                int l = 0, r = n;
                while (l < r) {
                    int mi = (l + r) / 2;
                    if (sc[mi] < c)
                        l = mi + 1;
                    else
                        r = mi;
                }
                lastans = l + 1;
            } else {
                p -= 1;
                int len = n - p;
                lastans = rk[p] - 1;

                int l = rk[p] - 1, r = n;
                while (l < r) {
                    int mi = (l + r) / 2 + 1;
                    int minv = query(rk[p], mi);
                    if (minv < len)
                        r = mi - 1;
                    else
                        l = mi;
                }

                int rp = l;
                l = rk[p] - 1, r = rp;
                while (l < r) {
                    int mi = (l + r) / 2 + 1;
                    if (c <= s[sa[mi] + len])
                        r = mi - 1;
                    else
                        l = mi;
                }

                lastans += l - rk[p] + 1;

                lastans -= query(tr[p], 1, m, c);

                // REMEMBER THE NEW SUFFIX!!!
                if (c <= s[p])
                    lastans++;
            }
        }

        printf("%d\n", lastans);

        // int ans;
        // fscanf(fp, "%d", &ans);
        // printf("%d\n", ans);
        // assert(lastans == ans);
    }
}

int main() {
    _log[1] = 0;
    for (int i = 2; i <= NMAX + 5; i++) {
        _log[i] = _log[i >> 1] + 1;
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        // puts("AHA!");
        _main();
    }
    return 0;
}