#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using u8 = unsigned char;
using i64 = long long;

constexpr int NMAX = 100000;
constexpr int MMAX = 32;
constexpr int TMAX = 8;
constexpr i64 MOD = 1718250570826593163;

int n, m;
char t[MMAX][TMAX];
char s[NMAX + 10];
u8 f[NMAX + 10];
i64 g[NMAX + 10];

void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

void _main() {
    char buf[32];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%s%s", buf, t[i]);
    }
    scanf("%s", s + 1);

    f[0] = g[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = g[i] = 0;
    }

    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
        int k = i;
        bool ok = true;
        for (int p = 0; t[j][p]; p++) {
            if (s[k + 1] == t[j][p])
                k++;
            else {
                ok = false;
                break;
            }
        }

        if (ok) {
            f[k] += f[i];
            add(g[k], g[i]);
        }
    }

    if (g[n] == 1)
        puts("happymorsecode");
    else if (g[n] == 0)
        puts("nonono");
    else
        printf("puppymousecat %d\n", int(f[n] & 0x7f));
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
