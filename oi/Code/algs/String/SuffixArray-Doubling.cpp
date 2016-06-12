#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

#define BUFFERSIZE 1024
#define CMAX 256

static char buffer[BUFFERSIZE];
static int sorted[BUFFERSIZE];
static int rank[BUFFERSIZE];
static int x[BUFFERSIZE];
static int y[BUFFERSIZE];
static int cnt[CMAX];
static int bucket[BUFFERSIZE];

static void sort_suffix(int length) {
    for (int i = 0; i < CMAX; i++)
        cnt[i] = 0;
    for (int i = 0; i < length; i++)
        cnt[buffer[i]]++;
    for (int i = 1; i < CMAX; i++)
        cnt[i] += cnt[i - 1];
    for (int i = length - 1; i >= 0; i--)
        sorted[--cnt[buffer[i]]] = i;
    rank[sorted[0]] = 1;
    for (int i = 1; i < length; i++) {
        rank[sorted[i]] = rank[sorted[i - 1]];
        if (buffer[sorted[i]] != buffer[sorted[i - 1]])
            rank[sorted[i]]++;
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
        for (int i = 0; i < CMAX; i++)
            cnt[i] = 0;
        for (int i = 0; i < length; i++)
            cnt[y[i]]++;
        for (int i = 1; i < CMAX; i++)
            cnt[i] += cnt[i - 1];
        for (int i = length - 1; i >= 0; i--)
            sorted[--cnt[y[i]]] = i;

        for (int i = 0; i < CMAX; i++)
            cnt[i] = 0;
        for (int i = 0; i < length; i++)
            cnt[x[sorted[i]]]++;
        for (int i = 1; i < CMAX; i++)
            cnt[i] += cnt[i - 1];
        for (int i = length - 1; i >= 0; i--)
            bucket[--cnt[x[sorted[i]]]] = sorted[i];
        for (int i = 0; i < length; i++)
            sorted[i] = bucket[i];

        // Step 3: Rewrite rank array
        rank[sorted[0]] = 1;
        for (int i = 1; i < length; i++) {
            rank[sorted[i]] = rank[sorted[i - 1]];
            if (x[sorted[i]] != x[sorted[i - 1]] ||
                y[sorted[i]] != y[sorted[i - 1]])
                rank[sorted[i]]++;
        }

        width <<= 1;
    }  // while
}

int main() {
    scanf("%s", buffer);

    int length = strlen(buffer);
    sort_suffix(length);

    for (int i = 0; i < length; i++)
        printf("%d ", sorted[i]);
    putchar('\n');
    for (int i = 0; i < length; i++)
        printf("%d ", rank[i]);
    putchar('\n');

    return 0;
}  // function main
