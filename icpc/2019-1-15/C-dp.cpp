#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 5000
#define INF 0x3f3f3f3f3f3f3f3f

#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define rrep(i, r, l) for (int i = (r); i >= (l); i--)

typedef long long i64;

struct Edge {
    int v, w;
};

static int n, K, size[NMAX + 10];
static vector<Edge *> T[NMAX + 10];
static i64 f[NMAX + 10][3][NMAX + 10], g[2][NMAX + 10];

template <typename T>
inline void chkmax(T &a, const T &b) {
    if (a < b) a = b;
}

template <typename ... T>
inline void print(i64 *a, int n, const char *str, const T& ... args) {
    printf(str, args...);
    printf(": ");
    if (a[0] <= -INF/2) printf("     ");
    rep(i, 0, n) if (a[i] > -INF/2) printf("%4lld ", a[i]); else printf("");
    //printf("\n     ");
    //i64 last = INF;
    //rep(i, 1, n) if (a[i] > -INF/2 && a[i - 1] > -INF/2) {
    //    printf("%4lld ", a[i] - a[i - 1]);
    //    assert(a[i] - a[i - 1] <= last);
    //    last = a[i] - a[i - 1];
    //} else printf("---- ");
    putchar('\n');
}

void dp(int x, int fa) {
    size[x] = 1;
    f[x][0][0] = f[x][2][0] = 0;
    for (auto e : T[x]) {
        int v = e->v;
        if (v == fa) continue;
        dp(v, x);
        //if (x == 1) printf("v = %d\n", v);
        rep(j, 0, size[v] / 2 + 1) {
            rep(k, 0, size[x] / 2) {
                chkmax(g[0][j + k], f[v][2][j] + f[x][0][k]);
                chkmax(g[1][j + k], f[v][2][j] + f[x][1][k]);
                chkmax(g[1][j + k + 1], f[v][0][j] + e->w + f[x][0][k]);
            }
            //if (x == 1) {
            //    print(g[0], (size[x] + size[v]) / 2, "g[0], j = %2d", j);
            //    print(g[1], (size[x] + size[v]) / 2, "g[1], j = %d", j);
            //}
        }
        size[x] += size[v];
        memcpy(f[x][0], g[0], sizeof(i64) * (size[x] / 2 + 1));
        memcpy(f[x][1], g[1], sizeof(i64) * (size[x] / 2 + 1));
        rep(i, 0, size[x] / 2) g[0][i] = g[1][i] = -INF;
    }
    rep(i, 0, size[x] / 2) f[x][2][i] = max(f[x][0][i], f[x][1][i]);
    //if (x == 1) {
    //    print(f[x][0], size[x] / 2, "f[x][0]");
    //    print(f[x][1], size[x] / 2, "f[x][1]");
    //    print(f[x][2], size[x] / 2, "f[x][2]");
    //}
}

int main() {
    scanf("%d%d", &n, &K);
    rep(i, 1, n - 1) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        T[u].push_back(new Edge{v, w});
        T[v].push_back(new Edge{u, w});
    }
    rep(i, 1, n) rep(j, 0, 2) rep(k, 0, n) f[i][j][k] = -INF;
    rep(i, 0, n) g[0][i] = g[1][i] = -INF;
    dp(1, 0);
    if (f[1][2][K] > -INF / 2) printf("%lld\n", f[1][2][K]);
    else puts("Impossible");
    return 0;
}
