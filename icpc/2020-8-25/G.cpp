#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

i64 a[4];

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        i64 s = 0, mx = 0;
        for (int i = 0; i < 4; i++) {
            scanf("%lld", a + i);
            s += a[i];
            mx = max(mx, a[i]);
        }

        printf("Case %d: ", t);
        if ((s - mx) > mx) {
            double b = s * 0.5;
            double ans = sqrt((b - a[0]) * (b - a[1]) * (b - a[2]) * (b - a[3]));
            printf("%.6lf\n", ans);
        } else puts("-1");
    }
    return 0;
}
