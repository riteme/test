#include <cstdio>
#include <cstring>
 
#include <algorithm>
 
using namespace std;
 
typedef long long i64;
 
#define NMAX 500
#define MOD 998244353
#define INV2 499122177
 
static int n;
static i64 G[NMAX + 10][NMAX + 10];
static i64 D[NMAX + 10][NMAX + 10], dist[NMAX + 10];
static int seq[NMAX + 10];
 
inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}
 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(G, 0x3f, sizeof(G));
        i64 sum = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
            scanf("%lld", &G[i][j]);
            add(sum, G[i][j]);
        }
        memcpy(D, G, sizeof(D));
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
            if (D[i][j] > D[i][k] + D[k][j])
                D[i][j] = D[i][k] + D[k][j];
        }
 
        i64 ans = 0;
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                seq[k] = k;
                dist[k] = min(D[i][k], D[j][k]);
            }
            sort(seq + 1, seq + n + 1, [](int x, int y) {
                return dist[x] < dist[y];
            });
            bool ui = false, uj = false;
            for (int k = 1; k <= n; k++) {
                int x = seq[k];
                int cnt = n - k;
                if (x == j && !ui) cnt--;
                if (x == i && !uj) cnt--;
                if (x == i) ui = true;
                if (x == j) uj = true;
                add(ans, dist[x] % MOD * cnt % MOD);
            }
        }
 
        i64 m = n * (n - 1) / 2;
        ans = ans * 2 % MOD;
        add(ans, (m - 1) * sum % MOD);
        printf("%lld\n", ans * INV2 % MOD);
    }
 
    return 0;
}
