/**
 * 推一推式子，可以知道答案：
 * \sum a_i + (1 - x) * \sum [a_i / x]
 * 如何计算\sum [a_i / x]
 * 对于a_i < x的数，值为0
 * 记suf[i]为大于等于i的数的个数，那么上面的和式为
 * suf[x] + suf[2x] + ... + suf[kx]
 * 根据调和级数可知时间复杂度为O(n \ln n)
 */

#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long int64;

static int n;
static int seq[NMAX + 10];
static int maxv;
static int suf[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
        suf[seq[i]]++;
        maxv = max(maxv, seq[i]);
    }

    for (int i = maxv; i >= 1; i--) {
        suf[i] += suf[i + 1];
    }
}

int main() {
    initialize();

    int64 answer;
    int64 sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += seq[i];
    }
    answer = sum;

    for (int x = 2; x <= maxv; x++) {
        int64 t = 0;
        for (int i = x; i <= maxv; i += x) {
            t += suf[i];
        }

        answer = min(answer, sum + (1 - x) * t);
    }

    printf("%lld\n", answer);

    return 0;
}
