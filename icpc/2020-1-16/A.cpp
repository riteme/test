#include <cstdio>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    i64 a1, a2, k1, k2, n;
    scanf("%lld%lld%lld%lld%lld", &a1, &a2, &k1, &k2, &n);

    if (k1 > k2) {
        swap(a1, a2);
        swap(k1, k2);
    }

    i64 mi = max(0LL, n - a1 * (k1 - 1) - a2 * (k2 - 1));
    i64 mx = 0;
    if (a1 * k1 < n) mx = a1 + (n - a1 * k1) / k2;
    else mx = n / k1;

    printf("%lld %lld\n", mi, mx);
    return 0;
}