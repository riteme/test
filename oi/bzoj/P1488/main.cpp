#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 60
#define MOD 997

inline int evaluate_gcd(int a, int b) {
    while (b) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }

    return a;
}

inline int quick_pow(int a, int b) {
    int r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

inline int evaluate_inv(int x) {
    return quick_pow(x, MOD - 2);
}

static int n;
static int len;
static int a[NMAX + 10];
static int fact[NMAX + 10];
static int inv[MOD];
static int gcd[NMAX + 10][NMAX + 10];
static int tpow[5001];

static void initialize() {
    fact[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    for (int i = 1; i < MOD; i++) {
        inv[i] = evaluate_inv(i);
    }

    for (int i = 1; i <= NMAX; i++) {
        for (int j = 1; j <= NMAX; j++) {
            gcd[i][j] = evaluate_gcd(i, j);
        }
    }

    tpow[0] = 1;
    for (int i = 1; i <= 5000; i++) {
        tpow[i] = tpow[i - 1] * 2 % MOD;
    }

    scanf("%d", &n);
}

static int evaluate(int sum, int maxv) {
    int result = 0;

    if (sum == 0) {
        int cnt = 0;

        for (int i = 1; i <= len; i++) {
            cnt += a[i] / 2;
            
            for (int j = i + 1; j <= len; j++) {
                cnt += gcd[a[i]][a[j]];
            }
        }

        result = tpow[cnt] * fact[n] % MOD; 
        cnt = 0;
        int last = 0;
        for (int i = 1; i <= len; i++) {
            result = result * inv[a[i]] % MOD;

            if (a[i] != last) {
                result = result * inv[fact[cnt]] % MOD;
                last = a[i];
                cnt = 0;
            }

            cnt++;
        }

        result = result * inv[fact[cnt]] % MOD;
    } else {
        len++;

        for (int i = min(sum, maxv); i >= 1; i--) {
            a[len] = i;
            result += evaluate(sum - i, i);
            result %= MOD;
        }

        len--;
    }

    return result;
}

int main() {
    initialize();

    int sum = evaluate(n, n);
    printf("%d\n", sum * inv[fact[n]] % MOD);

    return 0;
}
