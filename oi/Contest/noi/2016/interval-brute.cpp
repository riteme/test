// #define NDEBUG
#pragma GCC optimize(3)

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At #%d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#define DEBUG(message, ...) printf(message, __VA_ARGS__);
#else
#define TRACE
#define DEBUG
#endif

typedef long long int64;
typedef long double float128;

struct Interval {
    int left, right;
    int length;

    bool operator<(const Interval &b) const {
        return length < b.length;
    }
};  // struct Interval

#define NMAX 500000
#define MMAX 200000

static int n, m;
static Interval interval[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        interval[i].left = x;
        interval[i].right = y;
        interval[i].length = y - x;
    }  // for
}

int main() {
    // freopen("interval.in", "r", stdin);
    // freopen("interval.out", "w", stdout);
    initialize();
    TRACE

    fclose(stdin);
    fclose(stdout);
    return 0;
}
