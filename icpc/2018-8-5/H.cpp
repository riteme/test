#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 1000000

static int cnt[NMAX + 10];
static bool mark[NMAX + 10];

inline i64 c2(i64 x) {
    return x * (x - 1) >> 1;
}

int main() {
    for (int i = 2; i <= NMAX; i++) {
        cnt[i] = cnt[i - 1];
        if (mark[i]) continue;
        cnt[i]++;
        for (int j = 2 * i; j <= NMAX; j += i)
            mark[j] = true;
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        i64 ans = 0;
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        int t;
        for (int i = 1; i <= b; i = t + 1) {
            int x = a / i, y = b / i;
            if (x) t = min(a / x, b / y);
            else t = b / y;
            ans += c2(y - x) * (cnt[t] - cnt[i - 1]);
        }
        printf("%lld\n", ans);
        fflush(stdout);
    }

    return 0;
}
