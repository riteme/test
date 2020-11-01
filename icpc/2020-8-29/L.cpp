#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_set>

using namespace std;

using i64 = long long;

int main() {
    i64 x, ans = 0;
    scanf("%lld", &x);

    unordered_set<i64> mp;
    while (x > 1) {
        if (mp.count(x)) {
            ans = -1;
            break;
        }
        mp.insert(x);

        i64 n = x / 2;
        i64 s;
        if (x & 1) {
            s = 2 * (n + 1);
            x = 3 * n + 2;
        } else {
            s = 2 * n;
            x = n;
        }

        ans += s;
    }

    printf("%lld\n", ans);
    return 0;
}
