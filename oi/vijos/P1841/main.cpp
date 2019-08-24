#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long int64;

inline int64 quick_pow(int64 a, int64 b, int64 m) {
    int64 r = 1;
    while (b) {
        if (b & 1)
            r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }  // while
    return r;
}

int main() {
    int64 n, m, k, x;
    scanf("%lld%lld%lld%lld", &n, &m, &k, &x);

    int64 answer = (x + m * quick_pow(10, k, n) % n) % n;
    printf("%lld\n", answer);

    return 0;
}  // function main
