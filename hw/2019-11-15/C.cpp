#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static struct {
    int u, v;
} e[NMAX + 10];
static int deg[NMAX + 10];
static int c[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d%d", &e[i].u, &e[i].v);
    for (int i = 1; i <= n; i++)
        scanf("%d", c + i);
    int cnt = 0;
    for (int i = 1; i < n; i++) if (c[e[i].u] != c[e[i].v]) {
        cnt++;
        deg[e[i].u]++;
        deg[e[i].v]++;
    }
    int p = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] == cnt) p = i;
    puts(p ? "YES" : "NO");
    if (p) printf("%d\n", p);
    return 0;
}
