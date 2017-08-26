#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 500

typedef long long i64;

static int n;
static i64 A[NMAX + 10], B[NMAX + 10], C[NMAX + 10];
static i64 f[NMAX + 10][NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld", A + i, B + i, C + i);
    }
}

inline void chkmax(i64 &a, i64 b) {
    if (b > a)
        a = b;
}

int main() {
    initialize();

    i64 ans = -1e18;
    for (int a = 0; a <= n; a++) {
    for (int b = 0; b <= n; b++) {
    for (int c = 0; c <= n; c++) {
        f[a][b][c] = -1e18;
    }}}

    f[0][0][0] = 0;
    for (int a = 0; a <= n; a++) {
    for (int b = 0; b <= n; b++) {
    for (int c = 0; c <= n; c++) {
        if (a + b + c > n)
            continue;
        if (a + b + c == n) {
            if (a - 1 == c)
                ans = max(ans, f[a][b][c]);
        } else {
            int i = a + b + c + 1;
            chkmax(f[a + 1][b][c], f[a][b][c] + A[i]);
            chkmax(f[a][b + 1][c], f[a][b][c] + B[i]);
            chkmax(f[a][b][c + 1], f[a][b][c] + C[i]);
        }
    }}}

    printf("%lld\n", ans);

    return 0;
}
