#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 20
#define MOD 1000000007

typedef long long i64;

inline i64 inv(i64 n) {
    return n <= 1 ? n : (MOD - MOD / n) * inv(MOD % n) % MOD;
}

static int n, m;
static int u[NMAX * NMAX + 10];
static int v[NMAX * NMAX + 10];
static int w[NMAX * NMAX + 10];
static int fa[NMAX + 10];

inline int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

inline void link(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y)
        fa[x] = y;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", u + i, v + i, w + i);
    }  // for

    i64 ans = 0, cnt = 0;
    for (int s = 0; s < (1 << m); s++) {
        memset(fa, 0, sizeof(fa));

        int ecnt = 0;
        i64 sum = 0;
        for (int i = 0; i < m; i++) {
            if ((s >> i) & 1) {
                ecnt++;
                if (find(u[i]) == find(v[i])) {
                    sum = -1;
                    break;
                }

                link(u[i], v[i]);
                sum = (sum + w[i]) % MOD;
            }
        }  // for

        if (sum >= 0 && ecnt == n - 1) {
            cnt++;
            ans = (ans + sum) % MOD;
        }
    }  // for

    ans = ans * inv(cnt) % MOD;
    printf("%lld\n", ans);

    return 0;
}  // function main
