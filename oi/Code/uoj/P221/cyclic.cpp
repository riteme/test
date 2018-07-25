// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

inline int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }  // while

    return a;
}

int main() {
    int n, m, k;
    i64 ans = 0;
    scanf("%d%d%d", &n, &m, &k);

    for (int j = 1; j <= m; j++) {
        if (gcd(j, k) != 1)
            continue;

        for (int i = 1; i <= n; i++) {
            ans += gcd(i, j) == 1 ? 1 : 0;
        }  // for
    }      // for

    printf("%lld\n", ans);

    return 0;
}  // function main
