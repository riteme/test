#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 1000000

static char buffer[BUFFERSIZE];
static int sorted[BUFFERSIZE];
static int rnk[BUFFERSIZE];
static int x[BUFFERSIZE];
static int y[BUFFERSIZE];
static int cnt[BUFFERSIZE];
static int bucket[BUFFERSIZE];

static void sort_suffix(int length) {
    int rankmax = 0;
    for (int i = 0; i < length; i++) {
        rnk[i] = buffer[i];
        sorted[i] = i;

        if (rnk[i] > rankmax)
            rankmax = rnk[i];
    }

    int width = 1;
    while (width < length) {
        // Step 1: Using rnk array to fill x & y
        for (int i = 0; i < length; i++) {
            x[i] = rnk[i];

            if (i + width < length)
                y[i] = rnk[i + width];
            else
                y[i] = 0;
        }

        // Step 2: Radix sort
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < length; i++)
            cnt[y[i]]++;
        for (int i = 1; i <= rankmax; i++)
            cnt[i] += cnt[i - 1];
        for (int i = length - 1; i >= 0; i--)
            bucket[--cnt[y[sorted[i]]]] = sorted[i];
        for (int i = 0; i < length; i++)
            sorted[i] = bucket[i];

        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < length; i++)
            cnt[x[i]]++;
        for (int i = 1; i <= rankmax; i++)
            cnt[i] += cnt[i - 1];
        for (int i = length - 1; i >= 0; i--)
            bucket[--cnt[x[sorted[i]]]] = sorted[i];
        for (int i = 0; i < length; i++)
            sorted[i] = bucket[i];

        // Step 3: Rewrite rnk array
        rnk[sorted[0]] = 0;
        rankmax = 0;
        for (int i = 1; i < length; i++) {
            rnk[sorted[i]] = rnk[sorted[i - 1]];
            if (x[sorted[i]] != x[sorted[i - 1]] ||
                y[sorted[i]] != y[sorted[i - 1]])
                rnk[sorted[i]]++;

            if (rnk[sorted[i]] > rankmax)
                rankmax = rnk[sorted[i]];
        }

        width <<= 1;
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
        while (buffer[sorted[rnk[i]] + j] == buffer[sorted[rnk[i] - 1] + j])
            j++;
        lcp[rnk[i]] = j;
    }  // for
}

int main() {
    scanf("%s", buffer);
    int length = strlen(buffer);
    buffer[length] = '$';

    if (length == 1) {
        puts("1\n");
        return 0;
    }

    sort_suffix(length + 1);
    compute_lcp(length + 1);

    for (int i = 1; i <= length; i++)
        printf("%d ", sorted[i] + 1);
    putchar('\n');
    for (int i = 2; i <= length; i++)
        printf("%d ", lcp[i]);

    return 0;
}  // function main
