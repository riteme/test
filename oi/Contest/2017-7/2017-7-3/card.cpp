#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long i64;

static int n, q;
static i64 A[NMAX + 10], B[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", A + i, B + i);
    }
}

int main() {
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    initialize();

    while (q--) {
        i64 t;
        scanf("%lld", &t);

        for (int i = 1; i <= n; i++) {
            if (A[i] <= t)
                swap(A[i], B[i]);
        }
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += A[i];
    }

    printf("%lld\n", ans);

    return 0;
}
