/**
 * 窝草吓死我了......果然不要天天想着看题解......
 * 设f[l][r][s]表示从l到r的这一段，上一次添加的是s边(L表示左, R表示右)
 * 的方案数
 * 基于这么一个观察，最左边和最右边的数一定是等中间的数构造完毕后才加入的
 * 如果能够加入，就需要按照条件判断，这里不多说了
 * 注意当l == r的时候答案只应该贡献一次，
 * 即选择L贡献或者是R贡献。
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define MOD 19650827
#define L 0
#define R 1

static int n;
static int seq[NMAX + 10];
static int f[NMAX + 10][NMAX + 10][2];
static bool marked[NMAX + 10][NMAX + 10][2];

static int dp(int l, int r, int s) {
    if (l == r && s == L)  // only answer once
        return 1;
    if (marked[l][r][s])
        return f[l][r][s];
    marked[l][r][s] = true;
    int &answer = f[l][r][s];

    if (s == L) {
        if (seq[l] < seq[l + 1])
            answer += dp(l + 1, r, L);
        if (seq[l] < seq[r])
            answer += dp(l + 1, r, R);
    } else {
        if (seq[r] > seq[l])
            answer += dp(l, r - 1, L);
        if (seq[r] > seq[r - 1])
            answer += dp(l, r - 1, R);
    }

    answer %= MOD;
    return answer;
}

int main() {
    // freopen("chorusu.in", "r", stdin);
    // freopen("chorusu.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }

    int answer = dp(1, n, L) + dp(1, n, R);
    answer %= MOD;
    printf("%d\n", answer);

    return 0;
}
