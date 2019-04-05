/**
 * title: 后缀排序：DC3
 * category: 字符串
 * description: dc3.md
 * status: `ababa` not passed
 */

#include <cstdio>
#include <cstring>

#include <numeric>
#include <algorithm>

using namespace std;

#define NMAX 1000000

#define CH(i, n) i < n ? s[i] : 0
static int ch[NMAX + 10][3], seq[NMAX + 10];
static int arr[NMAX + 10], tmp[NMAX + 10], cnt[NMAX + 10];
inline bool cmp(int i, int j) {
    return ch[i][0] == ch[j][0] && ch[i][1] == ch[j][1] && ch[i][2] == ch[j][2];
}
inline bool sufcmp(int *s, int *rk, int n, int i, int j) {
    if (s[i] != s[j]) return s[i] < s[j];
    if ((i + 1) % 3 && (j + 1) % 3) return rk[i + 1] < rk[j + 1];
    if (s[i + 1] != s[j + 1]) return s[i + 1] < s[j + 1];
    return rk[i + 2] < rk[j + 2];
}
void radix_sort(int n, int m, int K, bool init = true) {
    if (init) for (int i = 0; i < n; i++) arr[i] = i;
    int *a = arr, *b = tmp;
    for (int k = 0; k < K; k++) {
        memset(cnt, 0, sizeof(int) * (m + 1));
        for (int i = 0; i < n; i++) cnt[ch[a[i]][k]]++;
        partial_sum(cnt, cnt + m + 1, cnt);
        for (int i = n - 1; i >= 0; i--) b[--cnt[ch[a[i]][k]]] = a[i];
        swap(a, b);
    }
    if (a != arr) memcpy(arr, tmp, sizeof(int) * n);
}
void suffix_sort(int *s, int n, int m, int *sa, int *rk) {
    s[n] = 0; n++;
    int p = 0, q = 0;
    for (int i = 1; i < n; i += 3, p++) for (int j = 0; j < 3; j++)
        ch[p][2 - j] = CH(i + j, n);
    for (int i = 2; i < n; i += 3, p++) for (int j = 0; j < 3; j++)
        ch[p][2 - j] = CH(i + j, n);
    radix_sort(p, m, 3);
    for (int i = 0; i < p; i++) {
        if (!q || (q && !cmp(arr[i - 1], arr[i]))) q++;
        s[n + arr[i]] = q;
    }
    if (q < p) suffix_sort(s + n, p, q, sa + n, rk + n);
    else {
        for (int i = 0; i < p; i++) sa[n + s[n + i] - 1] = i;
        for (int i = 0; i < p; i++) rk[n + sa[n + i]] = i + 1;
    }
    m = max(m, p);
    p = q = 0;
    for (int i = 1; i < n; i += 3, p++) rk[i] = rk[n + p];
    for (int i = 2; i < n; i += 3, p++) rk[i] = rk[n + p];
    for (int i = 0; i < n; i++) if (i % 3) seq[rk[i] - 1] = i;
    for (int i = 0; i < n; i += 3, q++) {
        ch[i][0] = i + 1 < n ? rk[i + 1] : 0;
        ch[i][1] = s[i];
        arr[q] = i;
    }
    radix_sort(q, m, 2, false);
    for (int i = seq[0] == n - 1, j = arr[0] == n - 1, k = 0; i < p || j < q; k++) {
        if (i == p) sa[k] = arr[j++];
        else if (j == q) sa[k] = seq[i++];
        else if (sufcmp(s, rk, n, seq[i], arr[j])) sa[k] = seq[i++];
        else sa[k] = arr[j++];
    }
    for (int i = 0; i < n - 1; i++) rk[sa[i]] = i + 1;
}

static int sa[3 * NMAX + 10], rk[3 * NMAX + 10], lcp[3 * NMAX + 10];

void compute_lcp(const char *s, int n) {
    int j = 0, p;
    for (int i = 0; i < n; i++, j = max(0, j - 1)) {
        if (rk[i] == 1) {
            j = 0;
            continue;
        }
        p = sa[rk[i] - 2];
        while (p + j < n && i + j < n && s[p + j] == s[i + j]) j++;
        lcp[rk[i]] = j;
}}

static char buf[NMAX + 10];
static int str[3 * NMAX + 10];

int main() {
    scanf("%s", buf);
    int n = strlen(buf);
    for (int i = 0; i < n; i++) str[i] = buf[i];
    suffix_sort(str, n, 255, sa, rk);
    //compute_lcp(buf, n);
    for (int i = 0; i < n; i++) printf("%d ", sa[i] + 1);
    putchar('\n');
    //for (int i = 2; i <= n; i++) printf("%d ", lcp[i]);
    //putchar('\n');
    return 0;
}
