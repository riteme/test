#pragma GCC optimize(3)

#define NDEBUG

#include <cassert>
#include <cstring>
#include <cstdio>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long int64;

#define NMAX 5000000

static int n;
static int64 seq[NMAX + 10];
static int64 sa, sb, sc, sd, a1, mod;

inline int64 gf(int64 x) {
    int64 x2 = x * x % mod;
    int64 x3 = x2 * x % mod;

    return (sa * x3 % mod + sb * x2 % mod + sc * x % mod + sd) % mod;
}

inline int64 gf2(int64 x) {
    int64 p1 = (sa * x + sb) % mod;
    int64 p2 = (p1 * x + sc) % mod;
    return (p2 * x + sd) % mod;
}

static void initialize() {
    scanf("%d", &n);

#ifdef USE_GENERATOR
    scanf("%lld%lld%lld%lld%lld%lld", &sa, &sb, &sc, &sd, &a1, &mod);

    int64 a0 = 0;
    seq[1] = a1;
    for (int i = 2; i <= n; i++) {
        seq[i] = (gf2(a1) + gf2(a0)) % mod;
        a0 = a1;
        a1 = seq[i];
    }
#else
    for (int i = 1; i <= n; i++)
        scanf("%lld", seq + i);
#endif
}

int main() {
    initialize();

    int64 minv = seq[1];
    int64 answer = 0;
    for (int i = 2; i <= n; i++) {
        answer = max((seq[i] - minv + 1) >> 1, answer);

        minv = min(minv, seq[i]);
    }

    printf("%lld\n", answer);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
