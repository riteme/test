#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

#define BUFFERSIZE 10000100

static char buffer[BUFFERSIZE];
static int sorted[BUFFERSIZE];
static int rank[BUFFERSIZE];
static int x[BUFFERSIZE];
static int y[BUFFERSIZE];
static int cnt[BUFFERSIZE];
static int bucket[BUFFERSIZE];

static void sort_suffix(int length) {
    int rankmax = 0;
    for (int i = 0; i < length; i++) {
        rank[i] = buffer[i];
        sorted[i] = i;

        if (rank[i] > rankmax)
            rankmax = rank[i];
    }

    int width = 1;
    while (width < length) {
        // Step 1: Using rank array to fill x & y
        for (int i = 0; i < length; i++) {
            x[i] = rank[i];

            if (i + width < length)
                y[i] = rank[i + width];
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

        // Step 3: Rewrite rank array
        rank[sorted[0]] = 1;
        rankmax = 0;
        for (int i = 1; i < length; i++) {
            rank[sorted[i]] = rank[sorted[i - 1]];
            if (x[sorted[i]] != x[sorted[i - 1]] ||
                y[sorted[i]] != y[sorted[i - 1]])
                rank[sorted[i]]++;

            if (rank[sorted[i]] > rankmax)
                rankmax = rank[sorted[i]];
        }

        width <<= 1;
    }  // while
}

int main() {
    int length;
    scanf("%d%s", &length, buffer);
    sort_suffix(length);

    for (int i = 0; i < length; i++)
        printf("%d\n", sorted[i] + 1);

    return 0;
}  // function main
