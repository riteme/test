#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define rep(i, l, r) for (int i = l; i <= (r); i++)

static int n, L;
static int w[NMAX + 10], h[NMAX + 10];
static int f[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &L);

    rep(i, 1, n) {
        scanf("%d%d", h + i, w + i);
    }
}

inline void chkmin(int &a, int b) {
    if (b < a) a = b;
}

inline void chkmax(int &a, int b) {
    if (b > a) a = b;
}

int main() {
    initialize();

    rep(i, 1, n) {
        f[i] = INT_MAX;
        for (int j = i, l = w[i], m = h[i];
             l <= L && j; j--, l += w[j], chkmax(m, h[j])) {
            chkmin(f[i], f[j - 1] + m);
        }
    }

    printf("%d\n", f[n]);

    return 0;
}
