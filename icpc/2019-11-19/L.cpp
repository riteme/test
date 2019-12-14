#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000
#define MOD 1000000007
#define BASE 19260817

typedef unsigned long long u64;

static int n, q;
static int s[NMAX + 10];
static u64 H[NMAX + 10][NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        memset(s + 1, 0, sizeof(int) * n);
        for (int i = 1; i <= n; i++) {
            int v, j = 1;
            scanf("%d", &v);
            for ( ; s[j] && s[j] != v; j++) ;
            if (j)
                memmove(s + 2, s + 1, sizeof(int) * (j - 1));
            s[1] = v;

            u64 ci = 0;
            for (int k = 1; k <= n; k++) {
                //ci = (ci * BASE + s[k]) % MOD;
                ci = ci * BASE + s[k];
                H[i][k] = ci;
            }
        }
        while (q--) {
            int m;
            scanf("%d", &m);
            u64 ci = 0;
            for (int i = 0; i < m; i++) {
                int v;
                scanf("%d", &v);
                //ci = (ci * BASE + v) % MOD;
                ci = ci * BASE + v;
            }
            bool ok = false;
            for (int i = 0; !ok && i <= n; i++)
                ok |= H[i][m] == ci;
            puts(ok ? "Yes" : "No");
        }
    }
    return 0;
}
