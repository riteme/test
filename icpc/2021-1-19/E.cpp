#pragma GCC optimize(3)
#include <cstdio>
#include <cstring>

#include <set>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

constexpr int S = 26;
constexpr int NMAX = 2500000;
constexpr int INF = 0x3f3f3f3f;

void add(int &a, int &b, int c) {
    if (c < a) {
        b = a;
        a = c;
    } else if (a < c && c < b) {
        b = c;
    }
}

int v[NMAX + 10];
int ans[NMAX + 10];

void cover(int x, int xl, int xr, int L, int R, int w) {
    if (L <= xl && xr <= R)
        v[x] = min(v[x], w);
    else {
        int m = (xl + xr) >> 1;
        if (L <= m)
            cover(x << 1, xl, m, L, R, w);
        if (R > m)
            cover((x << 1) | 1, m + 1, xr, L, R, w);
    }
}

void commit(int x, int xl, int xr) {
    if (xl < xr) {
        int m = (xl + xr) >> 1;
        int lch = x << 1;
        int rch = lch | 1;
        v[lch] = min(v[lch], v[x]);
        v[rch] = min(v[rch], v[x]);
        commit(lch, xl, m);
        commit(rch, m + 1, xr);
    } else
        ans[xl] = v[x];
}

struct SAM {
    int mcnt;
    struct Node {
        int maxlen, fail;
        int first;
        int ch[S];
    } m[NMAX + 10];
    void reset() {
        memset(m, 0, sizeof(m));
        mcnt = 1;
        m[0].maxlen = -1;
        fill(m[0].ch, m[0].ch + S, 1);
    }

    int append(int x, int c) {
        int y = ++mcnt;
        m[y].first = m[y].maxlen = m[x].maxlen + 1;
        while (!m[x].ch[c]) {
            m[x].ch[c] = y;
            x = m[x].fail;
        }
        int p = m[x].ch[c];
        if (m[x].maxlen + 1 != m[p].maxlen) {
            int q = ++mcnt;
            m[q] = m[p];
            m[q].maxlen = m[x].maxlen + 1;
            m[p].fail = m[y].fail = q;
            while (m[x].ch[c] == p) {
                m[x].ch[c] = q;
                x = m[x].fail;
            }
        } else
            m[y].fail = p;
        return y;
    }

    int seq[NMAX + 10], scnt[NMAX + 10];
    
    void tsort() {
        memset(scnt, 0, sizeof(int) * mcnt);
        for (int i = 1; i <= mcnt; i++)
            scnt[m[i].maxlen]++;
        partial_sum(scnt, scnt + mcnt, scnt);
        for (int i = 1; i <= mcnt; i++) {
            seq[scnt[m[i].maxlen]--] = i;
        }
    }

    void subsum() {
        tsort();

        for (int i = 1; i <= mcnt; i++) {
            fi[i] = se[i] = INF;
        }

        for (int i = mcnt; i > 1; i--) {
            int x = seq[i];
            int p = m[x].fail;
            add(fi[p], se[p], m[x].first);
            add(fi[p], se[p], fi[x]);
            add(fi[p], se[p], se[x]);
        }
    }

    int fi[NMAX + 10], se[NMAX + 10];

    void solve(int n) {
        subsum();

        for (int i = 2; i <= mcnt; i++) {
            int l = m[i].first;
            //int r = min(n, min_first[i] - 1);
            int r = n;
            if (m[i].first == fi[i])
                r = min(r, se[i] - 1);
            else
                r = min(r, fi[i] - 1);

            if (r < l)
                continue;

            int L = m[m[i].fail].maxlen + 1;
            //printf("[%d, %d]: %d\n", l, r, L);
            cover(1, 1, n, l, r, L);
        }

        commit(1, 1, n);
        for (int i = 1; i <= n; i++) {
            printf("%d\n", ans[i]);
        }
    }
} sam;

int n;
char s[NMAX + 10];

int main() {
    memset(v, 0x3f, sizeof(v));

    sam.reset();
    scanf("%d%s", &n, s + 1);
    int x = 1;
    for (int i = 1; i <= n; i++) {
        x = sam.append(x, s[i] - 'a');
    }
    sam.solve(n);

    return 0;
}
