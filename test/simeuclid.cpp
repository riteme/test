#include <iostream>
#include <algorithm>

using namespace std;

typedef long long i64;

static i64 ml, mr, ma, mb, mc;
#define chk(x, y) y = max(y, abs(x));

inline i64 sum(i64 l, i64 r) {
    return (r * (r + 1) - l * (l - 1)) >> 1;
}

inline i64 fdi(i64 a, i64 b) {
    return a / b - (a * b < 0);
}

i64 eval(i64 l, i64 r, i64 a, i64 b, i64 c) {
    chk(l, ml); chk(r, mr); chk(a, ma); chk(b, mb); chk(c, mc);
    if (!a) return fdi(b, c) * sum(l, r);
    if (abs(a) >= c) return eval(l, r, a % c, b, c) + a / c * sum(l, r);
    i64 m = (a * r + b) / c;
    return m * r - eval(1, m, c, -b - 1, a);
}

int main() {
    i64 l, r, a, b, c;
    cin >> l >> r >> a >> b >> c;
    i64 std = 0;
    bool ok = true;
    for (i64 k = l; k <= r; k++) {
        ok &= a * k + b >= 0;
        std += fdi(a * k + b, c);
    }
    if (!ok) puts("Condition failed.");
    printf("std = %lld, tst = %lld\n", std, eval(l, r, a, b, c));
    printf("%lld %lld %lld %lld %lld\n", ml, mr, ma, mb, mc);
    return 0;
}
