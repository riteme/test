/**
 * 取模有个重要的性质我居然不知道......
 * d | a并且d | b，于是：
 * a mod b = d(a / d mod b / d)
 * 证明？按照mod的定义来就可以证明了
 * 于是这里就是运用欧拉定理，如果不互质就利用上面的性质化为互质
 */

#include <cstdio>

typedef long long i64;

#define NMAX 10000000

inline i64 quick_pow(i64 a, i64 b, i64 m) {
    i64 r = 1;
    while (b) {
        if (b & 1)
            r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }

    return r;
}

inline i64 phi(i64 n) {
    i64 r = n, u = n;
    for (i64 i = 2; i * i <= n; i++) {
        if (u % i == 0) {
            r = r * (i - 1) / i;

            while (u % i == 0) {
                u /= i;
            }
        }
    }

    if (u > 1)
        r = r * (u - 1) / u;

    return r;
}

static bool visited[NMAX + 10];
static i64 answer[NMAX + 10];

i64 evaluate(i64 p) {
    if (p <= 2)
        return 0;
    if (visited[p])
        return answer[p];

    i64 &ret = answer[p];
    i64 k = 0;
    while (!((p >> k) & 1)) {
        k++;
    }

    i64 q = p >> k;
    i64 c = phi(q);
    i64 t = (evaluate(c) - k) % c;
    if (t < 0)
        t += c;

    ret = quick_pow(2, k, p) * 
          quick_pow(2, t, q) % p;
    return ret;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        i64 p;
        scanf("%lld", &p);
        printf("%lld\n", evaluate(p));
    }

    return 0;
}
