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

static void initialize() {}

int main() {
    // freopen("xxxx.in", "r", stdin);
    // freopen("xxxx.out", "w", stdout);
    initialize();
    TRACE

    fclose(stdin);
    fclose(stdout);
    return 0;
}
