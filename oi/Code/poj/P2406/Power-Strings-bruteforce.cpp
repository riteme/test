#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000

static int n;
static char seq[NMAX + 10];

static int solve() {
    int width = 1;
    while (width < n) {
        if (n % width == 0) {
            int i = 0, j = width;
            while (j < n) {
                if (seq[i] != seq[j])
                    goto failed;

                i = (i + 1) % width;
                j++;
            }  // while
            break;
        }

    failed:
        width++;
    }  // while

    return width;
}

int main() {
    while (true) {
        scanf("%s", seq);
        if (seq[0] == '.')
            break;
        n = strlen(seq);

        printf("%d\n", n / solve());
    }

    return 0;
}  // function main
