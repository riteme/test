#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int f[3][NMAX + 10];

inline void chkmin(int &a, int b) {
    if (b < a)
        a = b;
}

int main() {
    memset(f, 0x3f, sizeof(f));
    f[1][0] = f[2][0] = 0;
    for (int i = 1; i <= NMAX; i++) {
        if (i >= 1)
            chkmin(f[1][i], f[1][i - 1] + 1);
        if (i >= 2)
            chkmin(f[2][i], f[2][i - 2] + 1);

        int s = sqrt(i);
        s *= s;
        if (s < i) {
            chkmin(f[1][i], f[1][s] + 1);
            chkmin(f[2][i], f[2][s] + 1);
        }
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("%d\n", f[k][n] < 0x3f3f3f3f ? f[k][n] : -1);
    }

    return 0;
}
