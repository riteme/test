#include <cstdio>
#include <cstring>

#include <tuple>
#include <algorithm>

using namespace std;

typedef __int128_t i8;
typedef long long i64;

#define THRESHOLD 100'000'000'000'000'00

auto stern_brocot(i8 p0, i8 q0) -> tuple<i8, i8> {
    i8 n1 = 0, m1 = 1, n2 = 1, m2 = 0;
    while (m1 < THRESHOLD) {
        i8 n = n1 + n2, m = m1 + m2;
        i8 num = n * n * q0;
        i8 dem = m * m * p0;
        if (num == dem)
            return make_tuple(n, m);
        if (num < dem)
            n1 = n, m1 = m;
        else
            n2 = n, m2 = m;
    }

    return make_tuple(n1, m1);
}

i8 f(i8 n, i8 a, i8 b, i8 c) {
    if (n < 0)
        return 0;
    if (!a)
        return b / c * (n + 1);
    else if (a >= c)
        return f(n, a % c, b, c) + a / c * n * (n + 1) / 2;
    else if (b >= c)
        return f(n, a, b % c, c) + b / c * (n + 1);
    else {
        i8 m = (a * n + b) / c;
        return m * n - f(m - 1, c, c - b - 1, a);
    }
}

i8 tb[101][101][2];

void solve(i64 n, i64 p0, i64 q0) {
    i8 p, q;
    // tie(p, q) = stern_brocot(p0, q0);
    // printf("%lld/%lld\n", i64(p), i64(q));
    p = tb[p0][q0][0];
    q = tb[p0][q0][1];

    i64 ans = f(n, p, 0, q);
    printf("%lld\n", ans + n + 1);
}

int main() {
    for (int p = 1; p <= 100; p++)
    for (int q = 1; q <= 100; q++)
        tie(tb[p][q][0], tb[p][q][1]) = stern_brocot(p, q);

    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n, p, q;
        scanf("%lld%lld%lld", &p, &q, &n);
        solve(n, p, q);
    }

    return 0;
}