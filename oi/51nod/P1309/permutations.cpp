#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 50000
#define MOD 1000000007

typedef long long int64;

inline int64 quick_pow(int64 a, int64 b) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

inline int64 inv(int64 x) {
    return quick_pow(x, MOD - 2);
}

static int n, m;
static int64 A[NMAX + 10];
static int64 fac[NMAX + 10];
static int64 P;
static int64 pre[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
    }

    sort(A + 1, A + n + 1);
    for (int i = 1; i <= n; i++) {
        pre[i] = (pre[i - 1] + A[i]) % MOD;
    }

    P = fac[n];
    for (int i = 1; i <= n; i++) {
        int64 cnt = 1;
        while (i < n && A[i] == A[i + 1]) {
            cnt++;
            i++;
        }

        P = P * inv(fac[cnt]) % MOD;
    }
}

int main() {
    initialize();

    while (m--) {
        int64 M;
        scanf("%lld", &M);

        int p = upper_bound(A + 1, A + n + 1, M) - A;
        int64 k = n - p + 1;
        int64 S = pre[p - 1];
        printf("%lld\n", (S * P % MOD) * inv(k + 1) % MOD);
    }

    return 0;
}
