#include <cstdio>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    i64 n;
    scanf("%lld", &n);
    i64 l = 1, r = n;
    while (l < r) {
        i64 K = (l + r) / 2;
        i64 sum = 0, cur = n;
        while (cur) {
            sum += min(cur, K);
            cur = max(0LL, cur - K);
            cur -= cur / 10;
        }
        if (2 * sum >= n) r = K;
        else l = K + 1;
    }
    printf("%lld\n", l);
    return 0;
}
