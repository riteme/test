/**
 * 首先需要将式子化为方便处理的形式：
 * 1/n! = 1/x + 1/y
 * -> n!(x + y) = xy
 * ** => (x - n!)(y - n!) = n!^2
 * 最后一步没有想到，如果推出了最后一步，
 * 你就会发现答案就是n!^2的因子个数......
 * 于是通过质因数分解来计算因子个数即可
 * 注意到x <= y，所以答案需要除以2，并向上取整。
 * 如何答案是偶数时如何向上取整？
 * 实际上一个数的平方的因子个数一定是奇数个，
 * 这个结论可以通过质因数分解后的因子个数计算公式得出结论。
 */

#include <cstdio>

#define NMAX 1000000
#define MOD 1000000007
#define INV2 500000004

typedef long long i64;

static int n;
static bool marked[NMAX + 10];

inline i64 cnt(int p) {
    int u = n;
    i64 ret = 0;

    while (u) {
        ret += u / p;
        u /= p;
    }

    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        if (marked[i])
            continue;

        for (int j = i + i; j <= n; j += i) {
            marked[j] = true;
        }
    }

    i64 answer = 1;
    for (int i = 2; i <= n; i++) {
        if (marked[i])
            continue;

        i64 c = cnt(i) << 1;
        answer = answer * (1 + c) % MOD;
    }
    printf("%lld\n", (answer + 1) * INV2 % MOD);

    return 0;
}
