/**
 * 贪心 + DP判定是否可行
 * 关于位运算最大/最小普遍可以贪心
 * 从高位到低位枚举该位是否可以为0，然后采用DP的方式来判断
 * 对于A = 1，有简单算法
 */

#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

static int n, a, b;
static i64 seq[2010];

void initialize() {
    scanf("%d%d%d", &n, &a, &b);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
    }  // for
}

namespace Solver1 {

static i64 answer;
static bool f[110][110];

i64 main() {
    for (int i = 60; i >= 0; i--) {
        memset(f, 0, sizeof(f));

        f[0][0] = true;
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= j; k++) {
                i64 sum = 0;
                for (int p = j; p >= 1; p--) {
                    sum += seq[p];

                    if (f[p - 1][k - 1] &&
                        (((sum >> (i + 1)) | answer) == answer) &&
                        !((sum >> i) & 1)) {
                        f[j][k] = true;
                        break;
                    }
                }  // for
            }      // for
        }          // for

        answer = (answer << 1) | 1;
        for (int i = a; i <= b; i++) {
            if (f[n][i]) {
                answer ^= 1;
                break;
            }
        }  // for
    }      // for

    return answer;
}

}  // namespace Solver1

namespace Solver2 {

static i64 answer;
static int f[2010];

i64 main() {
    for (int i = 60; i >= 0; i--) {
        memset(f, 0, sizeof(f));

        for (int j = 1; j <= n; j++) {
            i64 sum = 0;
            f[j] = n + 1;
            for (int k = j; k >= 1; k--) {
                sum += seq[k];

                if ((((sum >> (i + 1)) | answer) == answer) &&
                    !((sum >> i) & 1)) {
                    f[j] = min(f[j], f[k - 1] + 1);
                }
            }  // for
        }      // for

        answer <<= 1;
        if (f[n] > b)
            answer |= 1;
    }  // for

    return answer;
}

}  // namespace Solver2

int main() {
    initialize();

    if (a == 1)
        printf("%lld\n", Solver2::main());
    else
        printf("%lld\n", Solver1::main());

    return 0;
}  // function main
