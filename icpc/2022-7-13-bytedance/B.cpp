#include <cstdio>
#include <cassert>
#include <cstring>

#include <map>
#include <string>
#include <algorithm>

using namespace std;

using i64 = long long;
using i128 = __int128_t;

constexpr int NMAX = 100000;

int n;
i128 c[NMAX + 10];
i128 f[NMAX + 10];
i128 d[NMAX + 10];
i128 g[NMAX + 10];
i128 e[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        i64 x, y, z;
        // scanf("%lld%lld%lld", c + i, f + i, d + i);
        scanf("%lld%lld%lld", &x, &y, &z);
        c[i] = x;
        f[i] = y;
        d[i] = z;
    }
    for (int i = 1; i < n; i++) {
        i64 x, y;
        // scanf("%lld%lld", g + i, e + i);
        scanf("%lld%lld", &x, &y);
        g[i] = x;
        e[i] = y;
    }

    i128 ans = 0;
    i128 zero = 0;
    i128 sum = 0;
    map<i128, i128> cnt;
    for (int i = 1; i <= n; i++) {
        cnt[zero + f[i]] += c[i];
        sum += c[i];

        i128 need = d[i];
        while (need > 0) {
            if (cnt.empty()) {
                puts("-1");
                return 0;
            }

            auto it = cnt.begin();
            i128 take = min(it->second, need);
            ans += take * (it->first - zero);
            need -= take;
            it->second -= take;
            sum -= take;
            if (it->second <= 0)
                cnt.erase(it);
        }

        zero -= e[i];
        need = sum - g[i];
        while (need > 0) {
            assert(cnt.size() > 0);
            auto it = prev(cnt.end());
            i64 take = min(it->second, need);
            need -= take;
            it->second -= take;
            sum -= take;
            if (it->second <= 0)
                cnt.erase(it);
        }
    }

    string out;
    do {
        out.push_back(ans % 10 + '0');
        ans /= 10;
    } while (ans > 0);
    reverse(out.begin(), out.end());
    puts(out.c_str());
    return 0;
}
