#include <cstdio>

int v[1000][1000];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            puts("?");
            printf("%d %d #\n", i, j);
            fflush(stdout);
            scanf("%d", &v[i][j]);
        }
    }
    puts("!");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            putchar(v[i][j] ? '#' : ' ');
        }
        puts("");
    }
    return 0;
}
