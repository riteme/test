/**
 * 非常机智的欧几里得类似算法
 * 考虑这么几种情况：
 * [a/b, c/d]中如果有整数，显然取这个整数最优
 * 这个的判定注意一下，之前实现的不好结果某些数据无限递归......
 * 如果a > b，那么可以考虑将**整数部分从两个分数中减去**（问题规模缩小）
 * 这样a就会小于b
 * 如果a < b，那么**可以将所有分数倒过来**，得到b/a > q/p > d/c（同类问题转化）
 * 是一个子问题。
 * 边界条件是a = 0，此时第一个分数为0
 * 为了取到最小值，显然q = 1，此时要满足1/x < c/d
 * 换言之d < cx，为了使x最小，我们取x = floor(d/c) + 1
 */

#include <cstdio>

typedef long long i64;

void solve(i64 a, i64 b, i64 c, i64 d, i64 &p, i64 &q) {
    if (a == 0) {
        p = 1;
        q = d / c + 1;
    } else if ((a / b + 1) * d < c) {
        p = a / b + 1;
        q = 1;
    } else if (a < b)
        solve(d, c, b, a, q, p);
    else {
        solve(a % b, b, c - a / b * d, d, p, q);
        p += a / b * q;
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        i64 a, b, c, d, p, q;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        solve(a, b, c, d, p, q);
        printf("%lld/%lld\n", p, q);
    }
}
