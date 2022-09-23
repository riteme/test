#include <cstdio>
#include <cassert>
#include <cstring>

#include <random>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int LT = 0;
constexpr int GE = 1;

int query(i64 x) {
    printf("? %lld\n", x);
    fflush(stdout);
    char op[8];
    scanf("%s", op);
    return op[0] == '<' ? LT : GE;
}

void submit(i64 x) {
    printf("= %lld\n", x);
    fflush(stdout);
}

i64 randi(i64 l, i64 r) {
    static random_device rd;
    static mt19937_64 gen(rd());
    // static mt19937_64 gen(0xdeadbeef19260817);

    binomial_distribution<i64> dist(r - l);
    return l + dist(gen);
}

void solve(i64 k, i64 l, i64 r, i64 n) {
    if (l == r) {
        submit(l);
        return;
    } else if (k == 0) {
        assert(l + 1 == r);

        if (query(r) == LT)
            submit(l);
        else
            submit(r);
    } else {
        assert(k > 0);
        i64 m = 1 << (k - 1);

        i64 pmin = max(0LL, n - m);
        i64 pmax = min(n, m);
        assert(pmin <= pmax);
        i64 p = randi(pmin, pmax);
        i64 q = n - p;

        i64 x = l + m + p;
        assert(x <= r);
        if (query(x) == LT)
            solve(k - 1, l, x - 1, p);
        else
            solve(k - 1, x, r, q);
    }
}

int main() {
    i64 n, q, K;
    scanf("%lld%lld", &n, &q);

    K = 0;
    while ((1LL << (K + 1)) <= n) {
        K++;
    }

    while (q--) {
        solve(K, 1, n, n - (1 << K));
    }

    return 0;
}