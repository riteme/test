#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

typedef long long i64;

int w, h, n;
i64 x[NMAX + 10], y[NMAX + 10], r[NMAX + 10];
int fa[NMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

void link(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v)
        fa[u] = v;
}

i64 pw(i64 x) {
    return x * x;
}

int main() {
    scanf("%d%d%d", &w, &h, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld", x + i, y + i, r + i);

    for (int i = 1; i <= n; i++) {
        if (x[i] - r[i] <= 0 || y[i] + r[i] >= h)
            link(n + 1, i);
        if (x[i] + r[i] >= w || y[i] - r[i] <= 0)
            link(n + 2, i);
    }
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
    if (pw(x[i] - x[j]) + pw(y[i] - y[j]) <= pw(r[i] + r[j]))
        link(i, j);

    int u = find(n + 1);
    int v = find(n + 2);
    puts(u == v ? "N" : "S");
    return 0;
}