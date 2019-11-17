/**
 * https://blog.csdn.net/yo_bc/article/details/78143353
 * https://blog.csdn.net/qq_35033987/article/details/78889683
 */

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define ACM_BEGIN
#define MULTIPLE 1
#define UNIQUE 0
#define IMPOSSIBLE -1
#define NMAX 100
#define MMAX (NMAX * NMAX)
static int n, m1, m2
static int d[NMAX + 10], d0[NMAX + 10];
static Edge { int u, v; } e1[MMAX + 10], e2[MMAX + 10];
int realize(Edge *e, int &m, int K = 0) {
    static int q1[NMAX + 10], q2[NMAX + 10];
    int ret = UNIQUE;
    for (int i = 1; i <= n; i++) id[i] = i;
    for (int i = 1; i < n; i++) {
        int u = id[i];
        sort(id + i + 1, id + n + 1, [](int x, int y) {
            return d[x] > d[y];
        });  // 可以考虑换成双队列实现
        if (i + d[u] > n) return IMPOSSIBLE;
        for (int j = i + 1; j <= i + d[u]; j++) {
            int v = id[j];
            if (d[v] == 0) return IMPOSSIBLE;
            if (j == i + d[u] && j < n && d[v] == d[id[j + 1]]) {
                ret = MULTIPLE;
                if (K--) v = id[++j];
            }
            e[++m] = {u, v};
            d[v]--;
    }}
    if (d[id[n]] != 0) return IMPOSSIBLE;
    return ret;
}
#define ACM_END

bool check(Edge *e, int m) {
    memset(d, 0, sizeof(d));
    for (int i = 1; i <= m; i++) {
        d[e[i].u]++;
        d[e[i].v]++;
    }
    return memcmp(d + 1, d0 + 1, sizeof(int) * n) == 0;
}

void print(Edge *e, int m) {
    printf("%d %d\n", n, m);
    for (int i = 1; i <= m; i++)
        printf("%d ", e[i].u);
    puts("");
    for (int i = 1; i <= m; i++)
        printf("%d ", e[i].v);
    puts("");
    assert(check(e, m));
}

int main() {
    while (scanf("%d", &n) != EOF) {
#define ACM_BEGIN
m1 = m2 = 0;
for (int i = 1; i <= n; i++)
    scanf("%d", d0 + i);
memcpy(d, d0, sizeof(d));
int ret = realize(e1, m1);
if (ret == MULTIPLE) {
    memcpy(d, d0, sizeof(d));
    realize(e2, m2, 1);
}
if (ret == IMPOSSIBLE) puts("IMPOSSIBLE");
else {
    puts(ret == UNIQUE ? "UNIQUE" : "MULTIPLE");
    print(e1, m1);
    if (ret == MULTIPLE) print(e2, m2);
}
#define ACM_END
    }
    return 0;
}
