#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

i64 solve(i64 x[3]) {
    if (x[0] == x[1] && x[1] == x[2])
        return 0;

    i64 t0 = (x[1] - x[0] + 1) / 2;
    i64 t1 = x[2] - x[1];
    i64 t;
    if (t0 == 0) {
        t = 2 * (x[2] - x[0]) / 3;
        x[0] += 3 * (t / 2);
        x[1] += 3 * (t / 2);
        if (x[1] < x[2]) {
            t++;
            x[0] += 1;
            x[1] += 2;
        }
    } else if (t1 == 0) {
        t = t0;
        x[0] += 2 * t;
        x[1] += t / 2;
        x[2] += t - t / 2;
    } else {
        t = min(t0, t1);
        x[0] += 2 * t;
        x[1] += t;
    }

    sort(x, x + 3);
    return solve(x) + t;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 x[3];
        scanf("%lld%lld%lld", x + 0, x + 1, x + 2);
        sort(x, x + 3);
        if ((x[2] - x[0]) % 2 > 0 || (x[2] - x[1]) % 2 > 0) {
            puts("-1");
            continue;
        }
        x[2] = (x[2] - x[0]) / 2;
        x[1] = (x[1] - x[0]) / 2;
        x[0] = 0;
        i64 s = x[0] + x[1] + x[2];
        if (s % 3 > 0) {
            puts("-1");
            continue;
        }

        printf("%lld\n", solve(x));
    }
    return 0;
}
