#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

#define NMAX 100000
#define MOD 1000000007

typedef long long int64;

static int64 fac[NMAX * 2 + 10];
static int64 facinv[NMAX * 2 + 10];

static void exgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
    } else {
        int64 m, n;
        exgcd(b, a % b, m, n);
        x = n;
        y = m - (a / b) * n;
    }
}

static int64 inv(int64 x) {
    int64 a, b;
    exgcd(x, MOD, a, b);

    if (a < 0)
        a += MOD;

    return a;
}

static void initialize_factorial() {
    int64 bound = NMAX * 2 + 5;

    fac[0] = 1;
    for (int64 i = 1; i <= bound; i++)
        fac[i] = fac[i - 1] * i % MOD;
    facinv[bound] = inv(fac[bound]);
    for (int64 i = bound - 1; i >= 0; i--)
        facinv[i] = facinv[i + 1] * (i + 1) % MOD;
}

inline int64 c(int64 n, int64 m) {
    if (n < 0)
        n = -n + m - 1;
    if (n < m)
        return 0;
    return (fac[n] * facinv[m] % MOD) * facinv[n - m] % MOD;
}

inline int64 evaluate_coeff(int64 n, int64 m, int64 k) {
    int64 p = m - 1;
    int64 answer = 0;
    
    int64 flag = 1;
    for (int64 i = 0; i <= p && i * k <= n - k; i++) {
        answer += flag * c(p, i) *
                  c(p + n - (1 + i) * k - 1, n - (1 + i) * k) % MOD;
        answer %= MOD;
        flag *= -1;
    }

    return answer;
}

inline int64 solve(int64 n, int64 m) {
    int64 answer = 0;

    for (int64 i = n / m; i <= n; i++) {
        answer += m * evaluate_coeff(n, m, i) % MOD;
        answer %= MOD;
    }

    if (answer < 0)
        answer += MOD;

    return answer;
}

int main() {
    initialize_factorial();

    int t;
    scanf("%d", &t);

    while (t--) {
        int64 n, m;
        scanf("%lld%lld", &n, &m);

        printf("%lld\n", solve(n, m));
    }

    return 0;
}
