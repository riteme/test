#define NDEBUG

#define NAME "a"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 15
#define AMAX 1000

typedef long long i64;

static int t, n;
static int seq[NMAX + 10];
static int f[NMAX + 10][AMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }
}

inline void chkmin(int &dest, int src) {
    if (src < dest)
        dest = src;
}

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    scanf("%d", &t);

    while (t--) {
        initialize();
        
        if (n == 1)
            printf("%d\n", seq[1]);
        else if (n == 2)
            printf("%d\n", abs(seq[1] - seq[2]));
        else {
            memset(f, 0x3f, sizeof(f));
            f[0][0] = 0;

            for (int i = 1; i <= n; i++) {
                for (int u = 0; u <= AMAX; u++) {
                    for (int v = 0; v <= AMAX; v++) {
                        chkmin(f[i][u ^ v], f[i - 1][u] + abs(seq[i] - v));
                    }
                }
            }

            printf("%d\n", f[n][0]);
        }
    }

    return 0;
}
