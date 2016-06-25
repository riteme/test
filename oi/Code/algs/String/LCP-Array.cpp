#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 1024
#define CMAX 256

static char str[BUFFERSIZE];
static int SA[BUFFERSIZE];
static int rnk[BUFFERSIZE];
static int bucket[BUFFERSIZE];
static int aux[BUFFERSIZE];
static int x[BUFFERSIZE], y[BUFFERSIZE];

static void radix_sort(int *t, int length, int rnkmax) {
    memset(bucket, 0, sizeof(int) * CMAX);
    for (int i = 0; i < length; i++)
        bucket[t[i]]++;
    for (int i = 1; i <= rnkmax; i++)
        bucket[i] += bucket[i - 1];
    for (int i = length - 1; i >= 0; i--)
        aux[--bucket[t[SA[i]]]] = SA[i];
    for (int i = 0; i < length; i++)
        SA[i] = aux[i];
}

static void suffix_sort(int length) {
    for (int i = 0; i < length; i++) {
        rnk[i] = str[i];
        SA[i] = i;
    }  // for

    int width = 1;
    int rnkmax = 256;
    while (width < length) {
        for (int i = 0; i < length; i++) {
            x[i] = rnk[i];
            y[i] = (i + width < length ? rnk[i + width] : 0);
        }  // for

        radix_sort(y, length, rnkmax);
        radix_sort(x, length, rnkmax);

        rnk[SA[0]] = 0;
        rnkmax = 0;
        for (int i = 1; i < length; i++) {
            rnk[SA[i]] = rnk[SA[i - 1]];
            if (x[SA[i]] != x[SA[i - 1]] || y[SA[i]] != y[SA[i - 1]])
                rnk[SA[i]]++;
            if (rnk[SA[i]] > rnkmax)
                rnkmax = rnk[SA[i]];
        }  // for

        width *= 2;
    }  // while
}

static int lcp[BUFFERSIZE];

static void compute_lcp(int length) {
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (rnk[i] == 0)
            continue;
        j--;
        if (j < 0)
            j = 0;
        while (str[SA[rnk[i]] + j] == str[SA[rnk[i] - 1] + j])
            j++;
        lcp[rnk[i]] = j;
    }  // for
}

int main() {
    scanf("%s", str);
    int length = strlen(str);
    suffix_sort(length);
    compute_lcp(length);

    printf("SA: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", SA[i]);
    }  // for
    putchar('\n');
    printf("rank: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", rnk[i]);
    }  // for
    putchar('\n');
    printf("lcp: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", lcp[i]);
    }  // for

    return 0;
}  // function main
