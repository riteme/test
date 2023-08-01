#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 1000;
constexpr i64 K = 1e10;

int n;
i64 A[NMAX + 10], B[NMAX + 10];
i64 C[NMAX + 10];

void update(i64 x, i64 y) {
    for (int i = 1; i <= n; i++) {
        A[i] = (A[i] + x) % y;
    }

    // for (int i = 1; i <= n; i++) {
    //     printf("%lld ", A[i]);
    // }
    // puts("");
    // for (int i = 1; i <= n; i++) {
    //     printf("%lld ", B[i]);
    // }
    // puts("");
    // puts("");
}

void make(i64 x) {
    i64 mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, A[i]);
    }
    i64 y = x + mx;
    printf("%lld %lld\n", x, y);
    update(x, y);
}

void finalize(i64 x, i64 y) {
    printf("%lld %lld\n", x, y);
    update(x, y);
}

void solve() {
    if (n == 1) {
        i64 d = B[1] - A[1];
        if (d < 0)
            d += K;
        finalize(d, K);
        return;
    }

    C[2] = B[2];
    for (int i = 3; i <= n; i++) {
        C[i] = (i - 2) * K + B[i];
    }
    C[1] = (n - 1) * K + B[1];

    make(C[1] - C[n] - A[1]);
    for (int i = n; i >= 3; i--) {
        make(C[i] - C[i - 1]);
    }

    finalize(B[2], K);
}

int aid[NMAX + 10];
i64 tmp[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", B + i);
    }

    bool okay = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i] == A[j] && B[i] != B[j])
                okay = false;
        }
    }

    puts(okay ? "Yes" : "No");

    if (!okay)
        return 0;

    for (int i = 1; i <= n; i++) {
        aid[i] = i;
    }

    sort(aid + 1, aid + n + 1, [](int i, int j) {
        return A[i] < A[j];
    });
    n = unique(aid + 1, aid + n + 1, [](int i, int j) {
        return A[i] == A[j];
    }) - aid - 1;

    for (int i = 1; i <= n; i++) {
        tmp[i] = A[aid[i]];
    }
    memcpy(A, tmp, sizeof(A));
    for (int i = 1; i <= n; i++) {
        tmp[i] = B[aid[i]];
    }
    memcpy(B, tmp, sizeof(B));

    printf("%d\n", n);
    solve();

    return 0;
}
