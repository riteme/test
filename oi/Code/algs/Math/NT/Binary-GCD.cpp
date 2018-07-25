#include <cstdio>
#include <algorithm>

typedef long long int64;

inline int64 gcd(int64 a, int64 b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

inline int64 bgcd(int64 a, int64 b) {
    if (a < b)
        std::swap(a, b);
    if (b == 0)
        return a;
    if (a & 1) {
        if (b & 1)
            return bgcd((a - b) >> 1, b);
        else
            return bgcd(a, b >> 1);
    } else {
        if (b & 1)
            return bgcd(a >> 1, b);
        else
            return bgcd(a >> 1, b >> 1) << 1;
    }
}

inline int64 tail_bgcd(int64 a, int64 b, int shift = 0) {
    if (a < b)
        std::swap(a, b);
    if (b == 0)
        return a << shift;
    if (a & 1) {
        if (b & 1)
            return tail_bgcd((a - b) >> 1, b, shift);
        else
            return tail_bgcd(a, b >> 1, shift);
    } else {
        if (b & 1)
            return tail_bgcd(a >> 1, b, shift);
        else
            return tail_bgcd(a >> 1, b >> 1, shift + 1);
    }
}

inline int64 iterative_bgcd(int64 a, int64 b) {
    int shift = 0;

    while (b) {
        if (a < b)
            std::swap(a, b);
        if (a & 1) {
            if (b & 1)
                a = (a - b) >> 1;
            else
                b >>= 1;
        } else {
            if (b & 1)
                a >>= 1;
            else {
                a >>= 1;
                b >>= 1;
                shift++;
            }
        }
    }

    return a << shift;
}

int main() {
    int64 n, m;
    scanf("%lld%lld", &n, &m);

    int64 answer = 0;
    for (int64 i = 1; i <= n; i++)
        for (int64 j = 1; j <= m; j++)
            answer += tail_bgcd(i, j);

    printf("%lld\n", answer);

    return 0;
}  // function main
