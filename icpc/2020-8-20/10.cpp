#include <cstdio>
#include <cstring>

#include <algorithm>

int a[3][3];

void _main() {
    for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
        scanf("%d", a[i] + j);
    }

    int ans = 0;
    for (int x1 = 0; x1 < 3; x1++)
    for (int y1 = 0; y1 < 3; y1++) {
        bool ok = true;
        for (int x2 = 0; x2 < 3; x2++)
        for (int y2 = 0; y2 < 3; y2++)
        if (x1 != x2 && y1 != y2) {
            int sg = 0;
            for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            if (!((i == x1 && j == y1) || (i == x2 && j == y2))) {
                sg ^= a[i][j] - 1;
            }
            for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            if (i != x1 && i != x2 && j != y1 && j != y2) {
                sg ^= a[i][j] - 1;
                sg ^= a[i][j];
            }

            if (!sg)
                ok = false;
        }

        if (ok)
            ans++;
    }

    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
