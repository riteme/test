#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2000

static int n;
static char seq[NMAX + 10];

static void initialize() {
    scanf("%s", seq);
    n = strlen(seq);
    seq[n] = '%';
    for (int i = 2 * n; i > n; i--)
        seq[i] = seq[2 * n - i];
    n *= 2;
}

static int sa[NMAX + 10];
static int rank[NMAX + 10];
static int x[NMAX + 10];
static int y[NMAX + 10];

static bool cmp(const int a, const int b) {
    return x[a] < x[b] || (x[a] == x[b] && y[a] < y[b]);
}

static void sort_suffix() {
    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        rank[i] = seq[i];
    }

    int width = 1;
    while (width <= n) {
        for (int i = 0; i <= n; i++) {
            x[i] = rank[i];
            y[i] = (i + width <= n ? rank[i + width] : 0);
        }

        sort(sa, sa + n + 1, cmp);

        width *= 2;
        rank[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            rank[sa[i]] = (x[sa[i]] == x[sa[i - 1]] && y[sa[i]] == y[sa[i - 1]]
                               ? rank[sa[i - 1]]
                               : rank[sa[i - 1]] + 1);
        }
    }
}

static int lcp[NMAX + 10];

static void evaluate_lcp() {
    int j = 0;
    for (int i = 0; i <= n; i++) {
        if (rank[i] == 0)
            continue;
        j = max(j - 1, 0);
        while (seq[sa[rank[i]] + j] == seq[sa[rank[i] - 1] + j])
            j++;
        lcp[rank[i]] = j;
    }
}

#define LOGN 12

static int st[NMAX + 10][LOGN + 1];

static void evaluate_st() {
    for (int i = 0; i <= n; i++) {
        st[i][0] = lcp[i];
    }

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 0; i <= n; i++) {
            if (i + (1 << (j - 1)) <= n)
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            else
                st[i][j] = st[i][j - 1];
        }
    }
}

inline int query(int left, int right) {
    if (left == right)
        return lcp[left];

    int len = right - left + 1;
    int k = 0;
    while ((1 << (k + 1)) < len)
        k++;

    return min(st[left][k], st[right - (1 << k) + 1][k]);
}

inline int compute_lcp(int x, int y) {
    // printf("rank[%d] = %d, rank[%d] = %d\n", x, rank[x], y, rank[y]);
    return query(min(rank[x], rank[y]) + 1, max(rank[x], rank[y]));
}

int main() {
    initialize();
    sort_suffix();
    evaluate_lcp();
    evaluate_st();

    // for (int i = 0; i <= n; i++)
    //     printf("%c ", seq[i]);
    // putchar('\n');
    // for (int i = 0; i <= n; i++)
    //     printf("%d ", sa[i]);
    // putchar('\n');
    // for (int i = 0; i <= n; i++)
    //     printf("%d ", rank[i]);
    // putchar('\n');
    // for (int i = 0; i <= n; i++)
    //     printf("%d ", lcp[i]);
    // putchar('\n');

    // putchar('\n');
    // for (int j = LOGN; j >= 0; j--) {
    //     for (int i = 0; i <= n; i++) {
    //         printf("%d ", st[i][j]);
    //     }  // for
    //     putchar('\n');
    // }  // for

    int left = 0, right = 0;
    for (int i = 0; seq[i] != '%'; i++) {
        int r;
        r = compute_lcp(i, n - i + 1);
        // printf("odd: i = %d, j = %d, r = %d\n", i, n - i + 1, r);
        if ((2 * r > right - left + 1) ||
            (2 * r == right - left + 1 && i - r < left)) {
            left = i - r;
            right = i + r - 1;
        }

        r = compute_lcp(i, n - i);
        // printf("even: i = %d, j = %d, r = %d\n", i, n - i, r);
        if ((2 * r - 1 > right - left + 1) ||
            (2 * r - 1 == right - left + 1 && i - r + 1 < left)) {
            left = i - r + 1;
            right = i + r - 1;
        }
    }

    seq[right + 1] = 0;
    printf("%s\n", seq + left);

    return 0;
}
