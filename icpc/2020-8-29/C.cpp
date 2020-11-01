#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

int main() {
    i64 n;
    scanf("%lld", &n);
    i64 ans = 0;
    for (i64 i = 1; i * 2 <= n; i++) {
        if (n % i == 0)
            ans++;
    }
    for (i64 q = 2; q <= n; q++)
    for (i64 a = 1; a <= n; a++) {
        i64 s = a * (1 + q);
        i64 p = a * q;
        if (s > n)
            break;
        while (s < n) {
            p *= q;
            s += p;
        }
        if (s == n)
            ans++;
    }
    printf("%lld\n", ans);
    return 0;
}
