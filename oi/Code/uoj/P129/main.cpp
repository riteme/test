/**
 * 显然，如果我们按照质数来状压DP是可以的，但是500以内质数太多
 * 无法记录状态
 * 考虑将所有小于sqrt(n)的质数挑出来，只有8个
 * 用他们进行质因数分解后，每个数要么等于1
 * 要么留下一个大于sqrt(n)的质数
 * 剩下1的分为一组暴力状压DP
 * 其余的则考虑剩下的那个素数
 * 由于只能被一边选到，所以设g[0/1][S1][S2]表示当前的数字
 * 被A或者B所选择的方案，转移时则分别枚举是否与另外一个人冲突
 * 如果不选择，则g[0/1][S1][S2] = f[S1][S2]
 * 最后一组DP完的时候，f[S1][S2] = g[0][S1][S2] + g[1][S1][S2] - f[S1][S2]
 * 减去是因为不选的方案被计算了两次
 * 注意到g[0]和g[1]互为倒置矩阵，所以只用DP其中一个即可
 */

// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <algorithm>

using namespace std;

#define NMAX 500
#define SMAX 256

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};

struct Number {
    Number() : big(1), state(0) {}

    int big, state;

    bool operator<(const Number &b) const {
        return big < b.big;
    }
};

static int n, P;
static Number num[NMAX + 10];
static int f[SMAX + 10][SMAX + 10];
static int g[SMAX + 10][SMAX + 10];

inline void add(int &dest, int src) {
    dest += src;

    if (dest >= P)
        dest -= P;
}

void initialize() {
    scanf("%d%d", &n, &P);

    for (int i = 2; i <= n; i++) {
        int x = i;
        
        for (int j = 0; j < 8; j++) {
            if (x % primes[j] == 0)
                num[i].state |= 1 << j;

            while (x % primes[j] == 0) {
                x /= primes[j];
            }
        }

        num[i].big = x;
    }

    sort(num + 2, num + n + 1);
}

int main() {
    initialize();

    f[0][0] = 1;
    bool fresh = true;
    for (int i = 2; i <= n; i++) {
        if (fresh) {
            memcpy(g, f, sizeof(g));
            fresh = false;
        }

        int s = num[i].state;
        for (int j = SMAX - 1; j >= 0; j--) {
            for (int k = SMAX - 1; k >= 0; k--) {
                if (j & k)
                    continue;

                if (!(k & s))
                    add(g[j | s][k], g[j][k]);
            }
        }

        if (i == n ||
            num[i].big == 1 ||
            num[i].big != num[i + 1].big) {
            fresh = true;

            for (int j = 0; j < SMAX; j++) {
                for (int k = 0; k < SMAX; k++) {
                    f[j][k] = (g[j][k] + g[k][j] - f[j][k]) % P;

                    if (f[j][k] < 0)
                        f[j][k] += P;
                }
            }
        }
    }

    int ans = 0;
    for (int j = 0; j < SMAX; j++) {
        for (int k = 0; k < SMAX; k++) {
            add(ans, f[j][k]);
        }
    }

    printf("%d\n", ans);

    return 0;
}
