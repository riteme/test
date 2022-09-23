#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 1000000;

int n;
i64 x[NMAX + 10];

i64 sum() {
    sort(x + 1, x + n + 1);
    i64 s = 0;
    for (int i = 1; i <= n; i++) {
        s += x[i];
    }
    i64 pre = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        pre += x[i];
        ans += (i * x[i] - pre) + ((s - pre) - (n - i) * x[i]);
    }
    // printf("ans=%llu\n", ans);
    return ans;
}

i64 p[NMAX + 10], q[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%llu", p + i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%llu", q + i);
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        x[i] = p[i];
    }
    ans += sum();
    for (int i = 1; i <= n; i++) {
        x[i] = q[i];
    }
    ans += sum();
    for (int i = 1; i <= n; i++) {
        x[i] = p[i] + q[i];
    }
    ans -= sum() / 2;
    for (int i = 1; i <= n; i++) {
        x[i] = p[i] - q[i];
    }
    ans -= sum() / 2;
    printf("%llu\n", ans);

    return 0;
}
