#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 20000
#define CMAX 1000000

static int n, k;
static int seq[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", seq + i);
    }  // for
    seq[n] = -1;
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
            y[i] = (i + width <= n ? rank[i + width] : -1);
        }  // for

        sort(sa, sa + n + 1, cmp);

        rank[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            rank[sa[i]] = (x[sa[i]] == x[sa[i - 1]] && y[sa[i]] == y[sa[i - 1]]
                               ? rank[sa[i - 1]]
                               : rank[sa[i - 1]] + 1);
        }  // for

        width *= 2;
    }  // while
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
    }  // for
}

static bool determine(int m) {
    int maxlength = 0;
    int current = 1;
    for (int i = 1; i <= n; i++) {
        if (lcp[i] >= m)
            current++;
        else {
            maxlength = max(maxlength, current);
            current = 1;
        }
    }  // for

    return max(current, maxlength) >= k;
}

int main() {
    initialize();
    sort_suffix();
    evaluate_lcp();

    // for (int i = 0; i <= n; i++) {
    //     printf("%d ", sa[i]);
    // }  // for
    // putchar('\n');

    // for (int i = 0; i <= n; i++) {
    //     printf("%d ", rank[i]);
    // }  // for
    // putchar('\n');

    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", lcp[i]);
    // }  // for
    // putchar('\n');

    int left = 0, right = n;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (determine(mid))
            left = mid;
        else
            right = mid;
    }  // while

    if (left < right && determine(right))
        left = right;

    printf("%d\n", left);

    return 0;
}  // function main
