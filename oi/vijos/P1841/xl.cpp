#include <cstdio>

typedef long long int64;

inline int64 quick_pow(int64 a, int64 b, int64 m) {
    int64 r = 1;
    
    while (b) {
        if (b & 1)
            r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }

    return r;
}

int main() {
    int64 n, m, k, x;
    scanf("%lld%lld%lld%lld", &n, &m, &k, &x);
    printf("%lld\n", (quick_pow(10, k, n) * m + x) % n);

    return 0;
}
