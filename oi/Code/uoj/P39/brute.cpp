#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, m, K, q;
static bool mat[NMAX + 10][10];

void initialize() {
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        mat[x][y] = true;
    }

    scanf("%d", &q);
}

int main() {
    initialize();

    while (q--) {
        if (m == 1) {
            puts("0");
            continue;
        }

        int x, y;
        scanf("%d%d", &x, &y);
        int up = 0, down = 0;
        for (int i = x; i >= 1; i--) {
            if (mat[i][1] || mat[i][2])
                break;
            up++;
        }

        for (int i = x + 1; i <= n; i++) {
            if (mat[i][1] || mat[i][2])
                break;
            down++;
        }

        printf("%d\n", up * down);
    }

    return 0;
}
