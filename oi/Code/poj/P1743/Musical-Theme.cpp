#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 20000
#define CMAX 88

static int n;
static int seq[NMAX + 10];

static void initialize() {
    for (int i = 0; i < n; i++) {
        scanf("%d", seq + i);
    }  // for

    if (n > 1) {
        for (int i = 0; i < n; i++) {
            seq[i] = seq[i + 1] - seq[i];
        }  // for
        n--;

        seq[n] = -100;
    }
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
    }  // for

    int width = 1;
    while (width <= n) {
        for (int i = 0; i <= n; i++) {
            x[i] = rank[i];
            y[i] = (i + width <= n ? rank[i + width] : rank[i]);
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
    int maxsa = sa[0];
    int minsa = sa[0];
    for (int i = 1; i <= n; i++) {
        if (lcp[i] >= m) {
            maxsa = max(maxsa, sa[i]);
            minsa = min(minsa, sa[i]);
        } else {
            if (maxsa - minsa > m)
                return true;

            maxsa = sa[i];
            minsa = sa[i];
        }
    }  // for

    return maxsa - minsa > m;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == 0)
            break;

        initialize();

        if (n == 1) {
            puts("0");
            continue;
        }

        sort_suffix();
        evaluate_lcp();

        // for (int i = 0; i <= n; i++)
        //     printf("%d ", seq[i]);
        // putchar('\n');
        // for (int i = 0; i <= n; i++)
        //     printf("%d ", sa[i]);
        // putchar('\n');
        // for (int i = 0; i <= n; i++)
        //     printf("%d ", rank[i]);
        // putchar('\n');
        // for (int i = 1; i <= n; i++)
        //     printf("%d ", lcp[i]);
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

        if (left < 4)
            puts("0");
        else
            printf("%d\n", left + 1);
    }  // while

    return 0;
}  // function main
