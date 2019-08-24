#include <bits/stdc++.h>

using namespace std;

#define NMAX 500

static int n, m, k;
static bool ch[NMAX + 10][NMAX + 10];

static bool check() {
    puts("Checking...");

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int d1 = 1, d2 = 1, d3 = 1, d4 = 1;
            int x, y;

            x = i + 1;
            while (x <= n && ch[x][j] == ch[i][j])
                x++, d1++;
            x = i - 1;
            while (x >= 1 && ch[x][j] == ch[i][j])
                x--, d1++;

            y = j + 1;
            while (y <= m && ch[i][y] == ch[i][j])
                y++, d2++;
            y = j - 1;
            while (y >= 1 && ch[i][y] == ch[i][j])
                y--, d2++;

            x = i + 1;
            y = j + 1;
            while (x <= n && y <= m && ch[x][y] == ch[i][j])
                x++, y++, d3++;
            x = i - 1;
            y = j - 1;
            while (x >= 1 && y >= 1 && ch[x][y] == ch[i][j])
                x--, y--, d3++;

            x = i + 1;
            y = j - 1;
            while (x <= n && y >= 1 && ch[x][y] == ch[i][j])
                x++, y--, d4++;
            x = i - 1;
            y = j + 1;
            while (x >= 1 && y <= m && ch[x][y] == ch[i][j])
                x--, y++, d4++;

            if (d1 >= k || d2 >= k || d3 >= k || d4 >= k)
                return false;
        }  // for
    }      // for

    return true;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    bool color = true;
    int x, y;
    while (scanf("%d%d", &x, &y) != EOF) {
        printf("(%d, %d): %d\n", x, y, color);
        ch[x][y] = color;
        color = !color;
    }  // while

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", ch[i][j]);
        }  // for
        putchar('\n');
    }  // for

    assert(check());

    return 0;
}  // function main
