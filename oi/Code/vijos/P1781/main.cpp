#include <cstdio>

typedef long long int64;

void exgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
    } else {
        int64 m, n;
        exgcd(b, a % b, m, n);
        x = n;
        y = m - (a / b) * n;
    }
}

int main() {
    int64 a, b, x, y;
    scanf("%lld%lld", &a, &b);

    exgcd(a, b, x, y);

    if (x < 0)
        x += b;

    printf("%lld\n", x);

    return 0;
}
