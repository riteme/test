#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

int n;
i64 t[NMAX + 10];

int solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", t + i);
    sort(t + 1, t + n + 1);
    int cnt = 0;
    i64 cur = 0;
    for (int i = 1; i <= n; i++) {
        if (cur > t[i])
            cnt++;
        else
            cur += t[i];
    }
    return n - cnt;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++)
        printf("Case #%d: %d\n", _t, solve());
    return 0;
}