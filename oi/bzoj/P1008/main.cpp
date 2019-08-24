#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

#define MOD 100003

inline int64 quick_pow(int64 a, int64 b) {
    a %= MOD;

    int64 result = 1;
    while (b) {
        if (b & 1) {
            result *= a;
            result %= MOD;
        }

        a *= a;
        a %= MOD;
        b >>= 1;
    }

    return result;
}

int main() {
    int64 m, n;
    scanf("%lld%lld", &m, &n);

    int64 answer = (quick_pow(m, n) - m * quick_pow(m - 1, n - 1)) % MOD;

    if (answer < 0)
        answer += MOD;
    printf("%lld", answer);

    return 0;
}  // function main
