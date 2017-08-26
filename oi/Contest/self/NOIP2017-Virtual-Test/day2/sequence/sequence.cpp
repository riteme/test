#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 2000
#define rep(var, l, r) for (int var = l; var <= r; var++)

typedef long long i64;

static int n;
static char str[NMAX + 10];
static char f[2][NMAX + 10][NMAX + 10];
static char cnt[NMAX + 10];

int main() {
    scanf("%s", str);
    n = strlen(str);
    
    f[0][0][0] = 1;
    int cur = 0, nxt = 1;
    rep(i, 0, n - 1) {
        memset(f[nxt], 0, sizeof(f[nxt]));

        rep(j, 0, n) rep(k, 0, n) {
            if (f[cur][j][k] == 0)
                continue;
            if (str[i] != '0')
                f[nxt][j][max(j, k) + 1] ^= f[cur][j][k];
            if (str[i] != '1')
                f[nxt][j + 1][k] ^= f[cur][j][k];
        }

        swap(cur, nxt);
    }

    rep(j, 0, n) rep(k, 0, n) {
        cnt[max(j, k)] ^= f[cur][j][k];
    }

    rep(i, 1, n) {
        putchar(cnt[i] + '0');
    }
    putchar('\n');

    return 0;
}
