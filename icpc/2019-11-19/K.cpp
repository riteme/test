#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n, K;
static i64 w[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &K);
        i64 s = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", w + i);
            s += w[i];
        }
        for (int i = 1; i <= n; i++)
            printf("%.8lf ", w[i] + (double) K * w[i] / s);
        puts("");
    }
    return 0;
}
