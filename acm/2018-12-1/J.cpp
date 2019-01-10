#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define UP 0
#define DW 1
#define UPUP 2
#define DWDW 3

static int n, a[NMAX + 10];
static vector<int> G[NMAX + 10];
static i64 f[NMAX + 10][4], ans;

void dp(int x, int p) {
    f[x][UP] = f[x][DW] = 1;
    f[x][UPUP] = f[x][DWDW] = 0;
    for (int v : G[x]) {
        if (v == p) continue;
        dp(v, x);
        if (a[x] > a[v]) {
            ans += f[v][UP] * (f[x][DW] + f[x][DWDW]) +
                   f[v][UPUP] * f[x][DW]/* + f[v][DW] * f[x][UP]*/;
            f[x][UP] += f[v][UP];
            f[x][UPUP] += f[v][UPUP];
            f[x][DWDW] += f[v][DW];
        } else if (a[x] < a[v]) {
            ans += f[v][DW] * (f[x][UP] + f[x][UPUP]) +
                   f[v][DWDW] * f[x][UP]/* + f[v][UP] * f[x][DW]*/;
            f[x][DW] += f[v][DW];
            f[x][DWDW] += f[v][DWDW];
            f[x][UPUP] += f[v][UP];
        } else if (a[x] == a[v]) {
            ans += f[v][DW] * (f[x][UP] + f[x][UPUP]) +
                   f[v][UP] * (f[x][DW] + f[x][DWDW]);
            f[x][UP] += f[v][UP];
            f[x][DW] += f[v][DW];
            f[x][UPUP] += f[v][UPUP];
            f[x][DWDW] += f[v][DWDW];
        }
    }

    printf("%d: %lld %lld %lld %lld\n", x, f[x][UP], f[x][UPUP], f[x][DW], f[x][DWDW]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ans = 0;
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dp(1, 0);
        printf("%lld\n", ans);
        for (int i = 1; i <= n; i++) G[i].clear();
    }
    return 0;
}
