#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 10
#define MMAX 20

static int n, m;
static struct Edge {
    int u, v;
} edge[MMAX + 10];
static int d[NMAX];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &edge[i].u, &edge[i].v);
    }
}

int main() {
    initialize();

    int ans = 0;
    for (int s = 0; s < (1 << m); s++) {
        memset(d, 0, sizeof(d));
        for (int i = 0; i < m; i++) {
            Edge &e = edge[i];
            if ((s >> i) & 1) {
                d[e.u]++;
                d[e.v]--;
            } else {
                d[e.u]--;
                d[e.v]++;
            }
        }

        int ret = 0;
        for (int i = 1; i <= n; i++) {
            ret += d[i] == 0;
        }

        ans = max(ans, ret);
    }

    printf("%d\n", ans);

    return 0;
}
