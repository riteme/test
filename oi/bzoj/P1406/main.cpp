/**
 * 分为两半枚举
 * x^2 \equiv 1 \pmod{n}
 * 所以
 * x^2 = kn + 1
 * x^2 - 1 = kn
 * (x + 1)(x - 1) = kn
 * 那么一定存在k = k_1k_2, n = n_1n_2
 * 满足
 * x + 1 = k_1n_1
 * x - 1 = k_2n_2
 * 如何枚举？首先枚举n的因子n1，然后枚举k1
 * 由于x < n，所以n1最好枚举大于sqrt n的因子，从而k1也会比较少
 * 然后假设k_1n_1是x + 1或x - 1，那么就只用判定另一部分是否是n_2的倍数
 */

#include <cstdio>

#include <set>

using namespace std;

typedef long long i64;

static i64 n;
static set<i64> answer;

void enumerate(i64 n1) {
    i64 n2 = n / n1;
    for (i64 k1 = 1; k1 * n1 <= n; k1++) {
        if ((k1 * n1 - 2) % n2 == 0)
            answer.insert(k1 * n1 - 1);
        if ((k1 * n1 + 2) % n2 == 0)
            answer.insert(k1 * n1 + 1);
    }
}

int main() {
    scanf("%lld", &n);

    for (i64 i = 1; i * i <= n; i++) {
        if (n % i == 0)
            enumerate(n / i);
    }

    if (n > 1) {
        answer.insert(1);
        answer.insert(n - 1);
    }

    for (set<i64>::iterator beg = answer.begin();
         beg != answer.end(); beg++) {
        if (*beg < n)
            printf("%lld\n", *beg);
    }

    if (answer.empty())
        printf("None\n");

    return 0;
}
