#include <cstdio>

#define NMAX 39

static int n;
static int magic[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d", &n);

    int x = 1;
    int y = n / 2 + 1;
    magic[x][y] = 1;
    for (int i = 2; i <= n * n; i++) {
        if (x == 1 && y != n) {
            x = n;
            y++;
        } else if (y == n && x != 1) {
            y = 1;
            x--;
        } else if (x == 1 && y == n) {
            x++;
        } else {
            if (!magic[x - 1][y + 1]) {
                x--;
                y++;
            } else
                x++;
        }

        magic[x][y] = i;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", magic[i][j]);
        }
        printf("\n");
    }

    return 0;
}
