#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000

int n, m;
i64 T;
i64 a[NMAX + 10];

int main() {
    scanf("%d%d%lld", &n, &m, &T);
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);

    i64 l = 0, r = 2000000000;
    for (int i = 1; i <= n; i++)
        l = max(l, (a[i] + T - 1) / T);

    while (l < r) {
        i64 t = (l + r) / 2;
        i64 sum = 0, cnt = 0;
        for (int i = 1; i <= n; i++) {
            sum += a[i];
            if (sum > T * t) {
                sum = a[i];
                cnt++;
            }
        }
        if (sum) cnt++;
        if (cnt <= m) r = t;
        else l = t + 1;
    }

    printf("%lld\n", l);
    return 0;
}