#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

#define BUFFERSIZE 20000
#define CMAX 256

static char buffer[BUFFERSIZE];
static int sorted[BUFFERSIZE];
static bool type[BUFFERSIZE];
static int position[BUFFERSIZE];
static int bucket[CMAX];
static int lbucket[CMAX];
static int sbucket[CMAX];

#define L_TYPE false
#define S_TYPE true

static void sort_suffix(int length) {
    // Initialize buckets
    for (int i = 0; i < length; i++)
        bucket[buffer[i]]++;
    for (int i = 1; i < CMAX; i++) {
        lbucket[i] = bucket[i - 1];
        bucket[i] += bucket[i - 1];
        sbucket[i] = bucket[i] - 1;
    }

    // Scan suffixes' types
    type[length - 1] = S_TYPE;
    for (int i = length - 2; i >= 0; i--) {
        if (buffer[i] < buffer[i + 1])
            type[i] = S_TYPE;
        else if (buffer[i] > buffer[i + 1])
            type[i] = L_TYPE;
        else
            type[i] = type[i + 1];
    }

    // Scan all the LMS substrings
    int cnt = 0;
    for (int i = 1; i < length; i++)
        if (type[i] == S_TYPE && type[i - 1] == L_TYPE)
            position[cnt++] = i;

    // Induced sort the LMS prefixes
    for (int i = 0; i < length; i++)
        sorted[i] = -1;
    for (int i = 0; i < cnt; i++)
        sorted[sbucket[buffer[position[i]]]--] = position[i];
    for (int i = 0; i < length; i++)
        if (sorted[i] > 0 && type[sorted[i] - 1] == L_TYPE)
            sorted[lbucket[buffer[sorted[i] - 1]]++] = sorted[i] - 1;
    for (int i = 1; i < CMAX; i++)  // Reset buffer-type bucket
        sbucket[i] = bucket[i] - 1;
    for (int i = length - 1; i >= 0; i--)
        if (sorted[i] > 0 && type[sorted[i] - 1] == S_TYPE)
            sorted[sbucket[buffer[sorted[i] - 1]]--] = sorted[i] - 1;
}

int main() {
    int length;
    scanf("%d%s", &length, buffer);
    buffer[length] = '$';

    sort_suffix(length + 1);
    for (int i = 1; i <= length; i++)
        printf("%d\n", sorted[i] + 1);

    return 0;
}  // function main
