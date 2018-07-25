// 修建双塔
// 简单动规
// 定义状态：f[i][j]:
// 前i个水晶组成高度差为j的双塔中,高度较低的最高的高塔(即第二高)
// 放置第i个水晶的情况:
// 1. 不放: f[i - 1][j], 高度差不变
// 2. 放在较高的塔上: f[i - 1][j + h[i]], 高度差变大了h[i]
// 3. 放在较低的塔上,分为两种子情况
//      a. 放上去后仍然较低: f[i - 1][j - h[i]] + h[i],
//          高度差变小了h[i], 较低塔增高h[i]
//      b. 放上去后比原来的最高塔更高了: f[i - 1][h[i] - j],
//          高度差变为新高度与原最高高度的差,为h[i] - j, 原最高塔变为
//          较低塔, 求出院最高塔的高度为原较低塔的高度加上原高度差
//
//  最后注意边界检查或将为求解的地方设为负无穷,以防算出不可行解

#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 2000
#define IMPOSSIBLE "Impossible"

static int n;
static int sum;
static int h[NMAX + 10];
static int f[NMAX + 10][MMAX + 10];

template <typename T>
inline T abs(const T &v) {
    return v >= 0 ? v : -v;
}

void initialize();
void output();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            f[i][j] = max(max(
                              // Do not place
                              f[i - 1][j],
                              // Place on the higher tower
                              f[i - 1][j + h[i]]),
                          (h[i] <= j
                               // Place on the lower tower, but is still lower
                               ? f[i - 1][j - h[i]] + h[i]
                               // Place on the lower tower, but become higher
                               : f[i - 1][h[i] - j] + j));
        }  // for
    }      // for

    output();
    return 0;
}  // function main

void initialize() {
    cin >> n;

    sum = 0;
    // int x;
    // generate_n(&h[1],
    //            n,
    //            [&x]() {
    //                cin >> x;
    //                sum += x;
    //                return x;
    //            });

    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        sum += h[i];
    }  // for

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sum; j++) { f[i][j] = INT_MIN; }  // for
    }                                                          // for
    f[0][0] = 0;
}

void output() {
    if (f[n][0] > 0)
        cout << f[n][0];
    else
        cout << IMPOSSIBLE;
}
