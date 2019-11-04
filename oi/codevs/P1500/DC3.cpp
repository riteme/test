#include <cstdio>
#include <memory.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int maxn = 20000100;

int ws[maxn], wa[maxn], wb[maxn], wv[maxn];
int sa[maxn], rk[maxn], height[maxn];
int a[maxn];
char s[maxn];

int indx[110], maxLen, ans[maxn], cnta;
bool vis[110];

// dc3
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x)*3 + 1 : ((x)-tb) * 3 + 2)

int c0(int *r, int a, int b) {
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}

int c12(int k, int *r, int a, int b) {
    if (k == 2)
        return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
    else
        return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
}

void sort(int *r, int *a, int *b, int n, int m) {
    int i;
    for (i = 0; i < n; i++)
        wv[i] = r[a[i]];
    for (i = 0; i < m; i++)
        ws[i] = 0;
    for (i = 0; i < n; i++)
        ws[wv[i]]++;
    for (i = 1; i < m; i++)
        ws[i] += ws[i - 1];
    for (i = n - 1; i >= 0; i--)
        b[--ws[wv[i]]] = a[i];
    return;
}

void dc3(int *r, int *sa, int n, int m) {
    int i, j, *rn = r + n, *san = sa + n;
    int ta = 0, tb = (n + 1) / 3, tbc = 0, p;
    r[n] = r[n + 1] = 0;
    for (i = 0; i < n; i++)
        if (i % 3 != 0)
            wa[tbc++] = i;

    sort(r + 2, wa, wb, tbc, m);
    sort(r + 1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);

    for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;

    if (p < tbc)
        dc3(rn, san, tbc, p);
    else
        for (i = 0; i < tbc; i++)
            san[rn[i]] = i;

    for (i = 0; i < tbc; i++)
        if (san[i] < tb)
            wb[ta++] = san[i] * 3;

    if (n % 3 == 1)
        wb[ta++] = n - 1;

    sort(r, wb, wa, ta, m);
    for (i = 0; i < tbc; i++)
        wv[wb[i] = G(san[i])] = i;

    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for (; i < ta; p++)
        sa[p] = wa[i++];
    for (; j < tbc; p++)
        sa[p] = wb[j++];
    return;
}

int main() {
    int n, k, i, j, len, maxch, mlen, cas = 1, h;
    n = 0;
    maxch = mlen = 0;
    indx[0] = 0;
    scanf("%d%s", &cas, s);
    len = strlen(s);
    if (mlen < len)
        mlen = len;
    for (j = 0; j < len; j++) {
        a[n++] = (int)s[j];
        if (a[n - 1] > maxch)
            maxch = a[n - 1];
    }
    a[n++] = 0;
    indx[i] = n - 1;

    dc3(a, sa, n, maxch + 1);

    for (int i = 1; i < n; i++) {
        printf("%d\n", sa[i] + 1);
    }  // for

    return 0;
}