#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2000

static int t;
static int n;
static char seq[NMAX + 10];

static void initialize() {
    scanf("%d", &t);
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
            y[i] = (i + width <= n ? rank[i + width] : 0);
        }  // for

        sort(sa, sa + n + 1, cmp);

        width *= 2;
        rank[sa[0]] = 0;
        for (int i = 1; i <= n; i++)
            rank[sa[i]] = (x[sa[i]] == x[sa[i - 1]] && y[sa[i]] == y[sa[i - 1]]
                               ? rank[sa[i - 1]]
                               : rank[sa[i - 1]] + 1);
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

int main() {
    initialize();

    for (int _cnt = 0; _cnt < t; _cnt++) {
        scanf("%s", seq);
        n = strlen(seq);
        seq[n] = '$';

        sort_suffix();
        evaluate_lcp();

        // for (int i = 0; i <= n; i++)
        //     printf("%d ", sa[i]);
        // putchar('\n');
        // for (int i = 0; i <= n; i++)
        //     printf("%d ", rank[i]);
        // putchar('\n');
        // for (int i = 1; i <= n; i++)
        //     printf("%d ", lcp[i]);
        // putchar('\n');

        int answer = 0;
        for (int i = 1; i <= n; i++)
            answer += n - sa[i] - lcp[i];
        printf("%d\n", answer);
    }  // for

    return 0;
}  // function main
