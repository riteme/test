#include <cstdio>

#define NMAX 200000

int n;
int deg[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        deg[u]++;
        deg[v]++;
    }

    int m = 0;
    for (int i = 1; i <= n; i++)
        m += deg[i] == 1;

    printf("%d\n", (m + 1) / 2);
    return 0;
}