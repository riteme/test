#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 400000

static int n;
static char buffer[BUFFERSIZE];

static int min_respresentation() {
    int i = 0, j = 1;
    while (i < n && j < n) {
        int k = 0;
        while (buffer[i + k] == buffer[j + k] && k < n)
            k++;
        if (k == n)
            return i;
        if (buffer[i + k] > buffer[j + k]) {
            i += k + 1;

            if (i == j)
                i++;
        } else {
            j += k + 1;

            if (i == j)
                j++;
        }
    }  // while

    if (i < n)
        return i;
    else
        return j;
}

static void initialize() {
    scanf("%d%s", &n, buffer);
}

int main() {
    // freopen("MinRepresentations.in", "r", stdin);
    // freopen("MinRepresentations.out", "w", stdout);
    initialize();

    buffer[n] = 'z' + 1;
    int start = min_respresentation();
    for (int i = start; i < n; i++) {
        putchar(buffer[i]);
    }  // for
    for (int i = 0; i < start; i++) {
        putchar(buffer[i]);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
