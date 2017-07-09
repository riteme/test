#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 20
#define SMAX 15000000
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

static int n;
static int tpow[NMAX + 10];
static i64 A[NMAX + 10], B[NMAX + 10], C[NMAX + 10], D[NMAX + 10];
static i64 f[2][SMAX];

void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld%lld%lld%lld", A + i, B + i, C + i, D + i);
    }
}

i64 dp(int p, int s) {
    if (s == 0)
        return 0;
    if (f[p][s] < INF)
        return f[p][s];
    i64 &ret = f[p][s] = p ? INF : -INF;
    for (int i = 0, x = s; i < n; x /= 3, i++) {
        int bit = x % 3;

        if (!bit)
            continue;
        if (p)
            ret = min(ret, dp(0, s - tpow[i]) - (bit == 1 ? D[i] : B[i]));
        else
            ret = max(ret, dp(1, s - tpow[i]) + (bit == 1 ? C[i] : A[i]));
    }

    return ret;
}

int main() {
    initialize();

    int s = 1;
    for (int i = 0; i < n; i++) {
        tpow[i] = s;
        s *= 3;
    }
    
    memset(f, 0x3f, sizeof(f));
    printf("%lld\n", dp(0, s - 1));

    return 0;
}
