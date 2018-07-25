// #define NDEBUG

#define NAME "b"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

#define MOD 1000000007
#define NMAX 100

typedef long long i64;

static int t, n, k;
static int f[NMAX + 10][NMAX + 10][NMAX + 10];

inline int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }

    return a;
}

void initialize() {
    scanf("%d", &t);
}

inline void add(int &dest, int src) {
    dest += src;
    if (dest >= MOD)
        dest -= MOD;
}

int dp(int i, int j, int g) {
    if (i == 0)
        return g == 1;
    if (f[i][j][g])
        return f[i][j][g];

    int &ret = f[i][j][g];
    for (int v = 1; v <= j; v++) {
        add(ret, dp(i - 1, v, gcd(v, g)));
    }

    return ret;
}

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();

    while (t--) {
        scanf("%d%d", &n, &k);

        memset(f, 0, sizeof(f));
        printf("%d\n", dp(k, n, 0));
    }

    return 0;
}
