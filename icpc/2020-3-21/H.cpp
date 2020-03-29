#include <cstdio>
#include <cstring>

typedef long long i64;

int n;
i64 p[20];

void solve() {
    i64 L, R, N;
    scanf("%lld%lld%lld", &L, &R, &N);
    n = 0;
    for (i64 i = 2; i * i <= N; i++) if (N % i == 0) {
        p[n++] = i;
        while (N % i == 0) N /= i;
    }
    if (N > 1) p[n++] = N;

    i64 ans = R - L + 1;
    for (int S = 1; S < (1 << n); S++) {
        i64 pr = 1;
        int cnt = 0;
        for (int i = 0; i < n; i++) if ((S >> i) & 1) {
            pr *= p[i];
            cnt++;
        }
        ans += (cnt & 1 ? -1 : 1) * (R / pr - (L - 1) / pr);
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        printf("Case #%d: ", t);
        solve();
    }

    return 0;
}