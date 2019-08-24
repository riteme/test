#include <cstdio>

#define NMAX 100000

static int n, m;
static int direction[NMAX + 10];
static char name[NMAX + 10][20];

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf("%d%s", direction + i, &name[i][0]);

    int pos = 0;
    while (m--) {
        int d, x;
        scanf("%d%d", &d, &x);

        if (d == 0) {
            if (direction[pos] == 0)
                pos -= x;
            else
                pos += x;
        } else {
            if (direction[pos] == 0)
                pos += x;
            else
                pos -= x;
        }

        pos = (pos + n) % n;
    }

    printf("%s\n", &name[pos][0]);

    return 0;
}
