#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

bool solve(i64 n, i64 K) {
    i64 x = n;
    i64 s = 0;
    while (x) {
        s += x % 3;
        x /= 3;
    }

    assert(s % 2 == n % 2);
    return K % 2 == n % 2 && s <= K && K <= n;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n, K;
        scanf("%lld%lld", &n, &K);
        puts(solve(n, K) ? "Yes" : "No");
    }
    return 0;
}
