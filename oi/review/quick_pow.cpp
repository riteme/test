#include <cstdio>

typedef long long int64;

inline int64 quick_pow(int64 a, int64 b) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a;
        a = a * a;
        b >>= 1;
    }

    return r;
}

static int64 recursive_quick_pow(int64 a, int64 b) {
    if (b == 0)
        return 1;
    if (b & 1)
        return recursive_quick_pow(a * a, b >> 1) * a;
    return recursive_quick_pow(a * a, b >> 1);
}

int main() {
    int64 a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld\n", recursive_quick_pow(a, b));

    return 0;
}
