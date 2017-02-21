/**
 * 首先，根据鸽巢原理，可以知道，答案一定不小于L = (a_n - a_1) / n
 * 然后对于每个长度为L的区间，如果里面有数字，那么就只用考虑其最大值和最小值
 * 因为其它的值的差都太小，不会成为答案
 * 如果只有一个数字，同样也不会不合法
 * 这样一来，最开始的询问为n + 1的代价
 * 后面至多n次询问，剩下n - 2个数字都会花费一次代价
 * 总代价为3 * n - 1
 */

#include "gap.h"

#include <cmath>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000

static int t, n;
static i64 seq[NMAX + 10];

i64 solve1() {
    i64 mn = 0, mx = 1000000000000000000;
    for (int i = 1; i <= (n + 1) / 2; i++) {
        MinMax(mn, mx, &mn, &mx);
        seq[i] = mn;
        seq[n - i + 1] = mx;
        mn++, mx--;
    }

    i64 ans = 0;
    for (int i = 1; i < n; i++) {
        ans = max(ans, seq[i + 1] - seq[i]);
    }

    return ans;
}

i64 solve2() {
    vector<i64> seq;
    i64 mn, mx;
    MinMax(0, 1000000000000000000, &mn, &mx);

    seq.push_back(mn);
    i64 L = max(1LL,
                static_cast<i64>(ceil(static_cast<double>(mn + mx) / n) + 0.5));
    for (i64 i = mn + 1; i < mx; i += L) {
        i64 j = min(mx - 1, i + L - 1);
        i64 a, b;
        MinMax(i, j, &a, &b);

        if (a >= 0) {
            seq.push_back(a);
            seq.push_back(b);
        }
    }  // for
    seq.push_back(mx);

    i64 ans = 0;
    for (size_t i = 0; i < seq.size() - 1; i++) {
        ans = max(ans, seq[i + 1] - seq[i]);
    }  // for

    return ans;
}

i64 findGap(int T, int N) {
    t = T;
    n = N;

    if (t == 1)
        return solve1();
    else
        return solve2();
}
