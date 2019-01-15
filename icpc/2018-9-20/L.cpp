#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, A, B, m;
static vector<int> G[NMAX + 10];
static int ay[NMAX + 10], by[NMAX + 10];
static int L[NMAX + 10], R[NMAX + 10], sz[NMAX + 10];

bool dp(int x, int f) {
    int sl = 0, sr = sz[x] = 1;
    for (int v : G[x]) {
        if (v == f) continue;
        if (!dp(v, x)) return false;
        sz[x] += sz[v];
        sl += L[v];
        sr += R[v];
    }
    L[x] = max(ay[x], sl);
    R[x] = min(min(sz[x], m - by[x]), sr);
    return L[x] <= R[x];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }

        scanf("%d", &A);
        for (int i = 0; i < A; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            ay[x] = max(ay[x], y);
        }

        scanf("%d", &B);
        for (int i = 0; i < B; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            by[x] = max(by[x], y);
        }

        int l = 0, r = n + 1;
        while (l < r) {
            m = (l + r) >> 1;
            int oy = ay[1];
            ay[1] = max(ay[1], m);
            if (dp(1, 0)) r = m;  // Key Point: m in [L[1], R[1]]
            else l = m + 1;
            ay[1] = oy;
        }
        printf("%d\n", l <= n ? l : -1);

        for (int i = 1; i <= n; i++) G[i].clear();
        memset(ay, 0, sizeof(int) * (n + 10));
        memset(by, 0, sizeof(int) * (n + 10));
    }
    return 0;
}
