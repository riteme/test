/**
 * See Line 48
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define SPACESIZE 62

typedef long long int64;

static int n;
static int64 id[NMAX + 10];
static int64 W[NMAX + 10];
static int sorted[NMAX + 10];
static int64 basis[SPACESIZE];

static bool cmp(const int a, const int b) {
    return W[a] > W[b];
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", id + i, W + i);
        sorted[i] = i;
    }

    sort(sorted + 1, sorted + n + 1, cmp);

}

int main() {
    initialize();

    int64 answer = 0;
    for (int cnt = 1; cnt <= n; cnt++) {
        int64 p = id[sorted[cnt]];
        int64 w = W[sorted[cnt]];

        for (int i = SPACESIZE; i >= 0; i--) {
            // CAUTION!!!: `p & (1 << i)` is wrong
            // Since 1 is int so 1 << i is also a int
            // 1 << 62 will be overflowed for int
            // The correct code is `p & (1LL << i)
            // You'd better use `p >> i` for convenience & performance
            if (p >> i) {
                if (basis[i])
                    p ^= basis[i];
                else {
                    basis[i] = p;
                    break;
                }
            }
        }

        if (p)
            answer += w;
    }

    printf("%lld\n", answer);

    return 0;
}
