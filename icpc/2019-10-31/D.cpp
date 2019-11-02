#include <cstdio>
#include <cstring>
#include <climits>

#define NMAX 10000

typedef unsigned long long u64;
typedef long long i64;

static int n;
static u64 b[NMAX + 10];

i64 zig(u64 x) {
    if (x == ULLONG_MAX) return LLONG_MIN;
    if (x == ULLONG_MAX - 1) return LLONG_MAX;
    if (x & 1) return -i64((x + 1) / 2);
    return x / 2;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", b + i);

    u64 v = 0, pw = 1;
    for (int i = 1; i <= n; i++) {
        if (b[i] >> 7) {
            v += (b[i] - 128) * pw;
            pw *= 128;
        } else {
            v += b[i] * pw;
            pw = 1;
            printf("%lld\n", zig(v));
            v = 0;
        }
    }

    return 0;
}
