#include <cstdio>

typedef long long int64;

#define MOD 1000000007
#define DIV2 500000004
#define DIV4 250000002
#define DIV6 166666668

inline int64 f(int64 n) {
    n %= MOD;
    int64 p1 = ((n*n%MOD)*n + 3 * n*n + 2*n) % MOD;
    int64 p2 = (((-2*n-3)*n % MOD) * (n + 1) % MOD) * DIV2 % MOD;
    int64 p3 = ((n*(2*n+1) % MOD)*(n+1)%MOD)*DIV6%MOD;
    int64 answer = (p1 + p2 + p3) % MOD;

    if (answer < 0)
        answer += MOD;

    return answer;
}

inline int64 s(int64 n, int64 m) {
    return (f(n) * f(m) % MOD) * DIV4 % MOD;
}

int main() {
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    int64 n, m;
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", s(n, m));

    return 0;
}
