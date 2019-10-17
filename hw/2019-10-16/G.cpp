#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define BASE 0xdeadbeef19260817u

typedef unsigned long long u64;

static int n, m, K;
static int a[NMAX + 10], b[NMAX + 10];
static u64 H[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++) {
        scanf("%d%d%d", &n, &m, &K);
        u64 pw = 1;
        for (int i = 1; i <= m; i++)
            pw *= BASE;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            H[i] = H[max(0, i - K)] * BASE + a[i];
            int j = i - m * K;
            if (j >= 1) H[i] -= a[j] * pw;
        }
        u64 sig = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d", b + i);
            sig = sig * BASE + b[i];
        }
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            cnt += sig == H[i];
        printf("Case #%d: %d\n", _t, cnt);
    }
    return 0;
}
