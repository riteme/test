#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 3000

typedef long long i64;

static int n;
static i64 K, H[NMAX + 10];

int main() {
    scanf("%d%lld", &n, &K);
    for (int i = 1; i <= n; i++) scanf("%lld", H + i);
    int ans = 1;
    for (int k = 2; k <= n; k++) {
        sort(H + 1, H + k + 1, [](i64 x, i64 y) { return x > y; });
        i64 sum = 0;
        for (int i = 1; i <= k; i += 2) sum += H[i];
        if (sum <= K) ans = k;
    }
    printf("%d\n", ans);
    return 0;
}
