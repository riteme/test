#include <cstdio>

#include <algorithm>

using namespace std;

typedef long long i64;

bool check(i64 a, i64 b, i64 c, i64 d) {
    return (a <= c && b <= d) || (a <= d && b <= c);
}

int main() {
    i64 a, b, c, d;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);

    i64 ans = 19260817;
    for (i64 i = 0; i <= 60; i++)
    for (i64 j = 0; j <= 60; j++) {
        i64 di = 1LL << i;
        i64 dj = 1LL << j;
        if (check((a + di - 1) / di, (b + dj - 1) / dj, c, d))
            ans = min(ans, i + j);
    }

    printf("%lld\n", ans);
    return 0;
}
