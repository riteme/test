#include <cstdio>
#include <cassert>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 19;
constexpr int K = NMAX - 1;

i64 d[NMAX], s[NMAX], e[NMAX];

int readi(i64 n) {
    int i;
    memset(d, 0, sizeof(d));
    for (i = 0; n > 0 && i < NMAX; i++) {
        d[i] = n % 10;
        n /= 10;
    }
    return i;
}

inline i64 get(int L, int S) {
    int m = (L + 1) / 2;
    int m0 = L / 2;

    memset(s, 0, sizeof(s));
    for (int i = 0; i < m; i++) {
        s[i] = (S >> i) & 1;
    }
    for (int i = 0; i < m0; i++) {
        s[L - i - 1] = s[i];
    }

    if (s[K] != 0)
        return 0;

    memset(e, 0, sizeof(e));
    for (int i = 0; i < K; i++) {
        e[i] += d[i];
        if (e[i] < 0) {
            e[i + 1]--;
            e[i] += 10;
        }
        if (s[i] && e[i] < 10) {
            e[i + 1]--;
            e[i] += 10;
        }
    }
    e[K] += d[K];

    for (int i = 0; i < NMAX; i++) {
        if (e[i] < 0)
            return 0;
    }
    for (int i = 0; i < m0; i++) {
        if (e[L - i - 1] != e[i])
            return 0;
    }
    if (L % 2 == 1 && e[m0] % 2 == 1)
        return 0;
    for (int i = L; i < NMAX; i++) {
        if (e[i] != 0)
            return 0;
    }

    i64 cnt = 1;
    for (int i = 0; i < m0; i++) {
        i64 l = max(i ? 0LL : 1LL, e[i] - 9);
        i64 r = min(9LL, e[i]);
        cnt *= max(0LL, r - l + 1);
    }

    return cnt;
}

i64 enumerate(int L) {
    int m = (L + 1) / 2;
    i64 cnt = 0;
    for (int S = 0; S < (1 << m); S++) {
        i64 v = get(L, S);
        // printf("get(%d, %x)=%lld\n", L, S, v);
        cnt += v;
    }
    return cnt;
}

i64 solve(i64 n) {
    int c = readi(n);
    i64 cnt = 0;
    cnt += enumerate(c);
    if (c > 1)
        cnt += enumerate(c - 1);
    return cnt;
}

i64 eval(i64 n) {
    i64 cnt = 0;
    for (i64 m = 1; m <= n; m++) {
        int c = readi(m);

        reverse(d, d + c);
        i64 mr = 0;
        for (int i = c - 1; i >= 0; i--) {
            mr = mr * 10 + d[i];
        }

        if (m + mr == n) {
            // printf("%lld+%lld=%lld\n", m, mr, n);
            cnt++;
        }
    }

    return cnt;
}

int main() {
    i64 T;
    scanf("%lld", &T);

    // for (i64 n = 1; n <= T; n++)
    // // i64 n = T;
    // {
    //     i64 ans1 = solve(n);
    //     i64 ans2 = eval(n);

    //     if ((n & 0xffff) == 0)
    //         printf("#%lld\n", n);

    //     if (ans1 != ans2) {
    //         printf("n=%lld, got=%lld, expect=%lld\n", n, ans1, ans2);
    //         abort();
    //     }
    // }

    while (T--) {
        i64 n;
        scanf("%lld", &n);
        printf("%lld\n", solve(n));
    }

    return 0;
}