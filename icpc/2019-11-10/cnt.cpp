#include <cstdio>

static int a[100];

int main() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        a[u] -= w;
        a[v] += w;
    }
    for (int i = 0; i < 100; i++)
        if (a[i]) printf("a[%d] = %d\n", i, a[i]);
}
