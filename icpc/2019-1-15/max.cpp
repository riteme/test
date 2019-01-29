#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 250000
#define INF 0x3f3f3f3f3f3f3f3f

#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define rrep(i, r, l) for (int i = (r); i >= (l); i--)

typedef long long i64;

struct Edge {
    int v, w;
};

static int n, K, size[NMAX + 10];
static vector<Edge *> T[NMAX + 10];
static int cnt[NMAX + 10][3];

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
    for (auto e : T[x]) {
        int v = e->v;
        if (v == fa) continue;
        dp(v, x);
        cnt[x][1] = max(cnt[v][2] + cnt[x][1], cnt[v][0] + 1 + cnt[x][0]);
        cnt[x][0] += cnt[v][2];
    }
    cnt[x][2] = max(cnt[x][0], cnt[x][1]);
}

int main() {
    scanf("%d%d", &n, &K);
    rep(i, 1, n - 1) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        T[u].push_back(new Edge{v, w});
        T[v].push_back(new Edge{u, w});
    }
    dp(1, 0);
    srand(*(new int) ^ time(0));
    printf("%d %d\n", n, cnt[1][2] + rand() % 3 - 1);
    return 0;
}
