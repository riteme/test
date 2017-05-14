// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

typedef long long i64;

#define NMAX 100000
#define LOGN 17

static int n;
static i64 lans[NMAX + 10];
static i64 rans[NMAX + 10];
static char str[NMAX + 10];
static int sa[NMAX + 10];
static int rnk[NMAX + 10];
static int h[NMAX + 10];
static int highbit[NMAX + 10];
static int st[LOGN + 1][NMAX + 10];

void bucket_sort(int *a, int *key) {
    static int bucket[NMAX + 10];
    static int cnt[NMAX + 10];

    memset(cnt + 1, 0, sizeof(int) * n);

    for (int i = 1; i <= n; i++) {
        cnt[key[a[i]]]++;
    }  // for

    for (int i = 0; i <= n; i++) {
        cnt[i] += cnt[i - 1];
    }  // for

    for (int i = n; i >= 1; i--) {
        bucket[cnt[key[a[i]]]--] = a[i];
    }  // for

    memcpy(a + 1, bucket + 1, sizeof(int) * n);
}

void suffix_sort() {
    static int x[NMAX + 10], y[NMAX + 10];

    memset(y, 0, sizeof(y));
    for (int i = 1; i <= n; i++) {
        y[str[i]] = 1;
    }  // for

    for (int i = '#'; i <= 'z'; i++) {
        y[i] += y[i - 1];
    }  // for

    for (int i = 1; i <= n; i++) {
        rnk[i] = y[str[i]];
    }  // for

    for (int len = 1; len <= n; len <<= 1) {
        int l = len >> 1;

        for (int i = 1; i <= n; i++) {
            sa[i] = i;
            x[i] = rnk[i];
            y[i] = i + l <= n ? rnk[i + l] : 0;
        }  // for

        bucket_sort(sa, y);
        bucket_sort(sa, x);

        rnk[sa[1]] = 1;
        for (int i = 2; i <= n; i++) {
            rnk[sa[i]] =
                rnk[sa[i - 1]] +
                (x[sa[i]] == x[sa[i - 1]] && y[sa[i]] == y[sa[i - 1]] ? 0 : 1);
        }  // for
    }      // for
}

void eval_lcp() {
    int j = 0;
    for (int i = 1; i <= n; i++) {
        if (rnk[i] == 1)
            continue;

        j = max(0, j - 1);

        while (str[i + j] == str[sa[rnk[i] - 1] + j]) {
            j++;
        }  // while

        h[rnk[i]] = j;
    }  // for
}

void make_st() {
    for (int i = 1; i <= n; i++) {
        st[0][i] = h[i];
    }  // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            st[j][i] = st[j - 1][i];

            if (i + (1 << (j - 1)) <= n)
                st[j][i] = min(st[j][i], st[j - 1][i + (1 << (j - 1))]);
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        highbit[i] = highbit[i >> 1] + 1;
    }  // for
}

inline int query_min(int l, int r) {
    int k = highbit[r - l + 1] - 1;
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}

inline int lcp(int i, int j) {
    if (rnk[i] > rnk[j])
        swap(i, j);
    return query_min(rnk[i] + 1, rnk[j]);
}

inline int lcs(int i, int j) {
    return lcp(n - i + 1, n - j + 1);
}

void initialize() {
    memset(lans, 0, sizeof(lans));
    memset(rans, 0, sizeof(rans));

    scanf("%s", str + 1);
    n = strlen(str + 1);
    str[n + 1] = '#';
    memcpy(str + n + 2, str + 1, n);
    reverse(str + n + 2, str + n * 2 + 2);
    n = n * 2 + 1;
    str[n + 1] = 0;

    suffix_sort();
    eval_lcp();
    make_st();
}

inline void add(int l, int r, i64 *arr) {
    if (l <= r) {
        arr[l]++;
        arr[r + 1]--;
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        // for (int i = 1; i <= n; i++) {
        //     printf("%d ", sa[i]);
        // }  // for

        // printf("\n");
        // for (int i = 1; i <= n; i++) {
        //     printf("%d ", h[i]);
        // }  // for

        // printf("\n");
        // continue;

        int realn = n / 2;
        for (int l = 1; l <= realn; l++) {
            for (int i = l; i + l <= realn; i += l) {
                int j = i + l;
                int front = lcs(i, j), back = lcp(i, j);

                if (front + back - 2 < l - 1)
                    continue;

                int lmin = i - min(l, front) + 1;
                int lmax = min(i + back - l, i);

                // printf(
                //     "l = %d, i = %d, j = %d, rans = [%d, %d], lans = [%d, "
                //     "%d]\n",
                //     l, i, j, lmin, lmax, lmin + 2 * l, lmax + 2 * l);

                add(lmin, lmax, rans);
                add(lmin + 2 * l, lmax + 2 * l, lans);
            }  // for
        }      // for

        i64 ans = 0;
        for (int i = 1; i <= realn; i++) {
            lans[i] += lans[i - 1];
            rans[i] += rans[i - 1];
            ans += lans[i] * rans[i];
        }  // for

        printf("%lld\n", ans);
    }  // while

    return 0;
}  // function main
