#include <cstdio>

constexpr int NMAX = 200000;

int n;
int f[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", f + i);
    }

    int u = 1, v = 1;
    do {
        u = f[u];
        v = f[f[v]];
    } while (u != v);

    int m = 1;
    for (int x = f[u]; x != u; x = f[x]) {
        m++;
    }

    printf("%d\n", m);
    int x = u;
    do {
        printf("%d ", x);
        x = f[x];
    } while (x != u);
    puts("");

    return 0;
}
