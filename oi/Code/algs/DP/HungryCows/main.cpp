#include <iostream>

using namespace std;

#define NMAX 2000
#define BMAX 1000

static int n, b;
static int element_count = 0;  // 区间总数计数

// f: 动态规划;
static int f[NMAX + 10];

// first[i]表示在[0, i]上的结尾未i的第一个区间
static int first[NMAX + 10];

// next[i]表示与当前区间结尾位置一样的下一个区间，-1表示结束;
static int next[BMAX + 10];

// s[i]表示第i个区间的起点
static int s[BMAX + 10];

int main() {
    ios::sync_with_stdio(false);

    return 0;
}  // function main
