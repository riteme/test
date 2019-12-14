#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, m;
static int fa[NMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        memset(fa + 1, 0, sizeof(int) * n);
        int ans = n;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u = find(u);
            v = find(v);
            if (u != v) {
                ans--;
                fa[u] = v;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
