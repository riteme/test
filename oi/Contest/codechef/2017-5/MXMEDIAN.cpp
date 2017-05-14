#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static int seq[NMAX + 10];

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 1; i <= 2 * n; i++) {
            scanf("%d", seq + i);
        }

        sort(seq + 1, seq + n * 2 + 1);

        printf("%d\n", seq[2 * n - n / 2]);
        for (int i = 1; i <= n; i++) {
            printf("%d %d ", seq[i], seq[n + i]);
        }
        printf("\n");
    }

    return 0;
}

