#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define LOGN 20
#define MOD 1000000007

typedef long long i64;

static i64 f[NMAX + 10][LOGN + 1];
static bool mark[NMAX + 10];
static vector<int> pw[NMAX + 10];

int main() {
    f[0][0] = 1;
    for (int i = 1; i <= LOGN; i++) f[0][i] = 2;
    for (int i = 1; i <= NMAX; i++) {
        f[i][0] = 1;
        for (int j = 1; j <= LOGN; j++) f[i][j] = (f[i][j - 1] + f[i - 1][j]) % MOD;
    }
    for (int i = 2; i <= NMAX; i++) if (!mark[i]) {
        pw[i].push_back(1);
        for (int j = i + i; j <= NMAX; j += i) {
            mark[j] = true;
            int t = 0, x = j;
            while (x % i == 0) {
                x /= i;
                t++;
            }
            pw[j].push_back(t);
        }
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int r, n;
        scanf("%d%d", &r, &n);
        i64 ans = 1;
        for (auto p : pw[n]) ans = ans * f[r][p] % MOD;
        printf("%lld\n", ans);
    }

    return 0;
}
