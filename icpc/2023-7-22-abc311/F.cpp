#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 2000;
constexpr int MOD = 998244353;

int n, m;
char S[NMAX + 10][NMAX + 10];
int h[NMAX + 10];
int f[NMAX + 10];

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", S[i] + 1);
    }
    for (int y = 1; y <= m; y++) {
        h[y] = n + 1;
        for (int x = 1; x <= n; x++) {
            if (S[x][y] == '#') {
                h[y] = x;
                break;
            }
        }
    }

    f[n + 1] = 1;
    for (int y = 1; y <= m; y++) {
        for (int x = n; x >= 1; x--) {
            add(f[x], f[x + 1]);
        }

        // for (int x = 1; x <= n + 1; x++) {
        //     printf("%d ", f[x]);
        // }
        // puts("");

        add(f[h[y] + 1], MOD - f[h[y] + 2]);
        // for (int x = 1; x <= n + 1; x++) {
        //     printf("%d ", f[x]);
        // }
        // puts("");
        for (int x = n + 1; x > h[y]; x--) {
            f[x] = 0;
        }
        add(f[n + 1], f[n]);
        for (int x = n; x > 1; x--) {
            f[x] = f[x - 1];
        }
        f[1] = 0;

        // for (int x = 1; x <= n + 1; x++) {
        //     printf("%d ", f[x]);
        // }
        // puts("");
    }

    int ans = 0;
    for (int x = 0; x <= n + 1; x++) {
        add(ans, f[x]);
    }

    printf("%d\n", ans);
    return 0;
}
