#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 2000000

typedef long long int64;

static int cnt;
static int64 prime[NMAX + 10];
static bool marked[NMAX + 10];

static void evaluate_primes() {
    for (int64 i = 2; i <= NMAX; i++) {
        if (!marked[i])
            prime[++cnt] = i;

        for (int64 j = 1; j <= cnt && prime[j] * i <= NMAX; j++) {
            marked[prime[j] * i] = true;

            if (i % prime[j] == 0)
                break;
        }  // for
    }      // for
}

static int64 n, p;
static int64 times[NMAX + 10];

static void initialize() {
    scanf("%lld%lld", &n, &p);
}

inline int64 quick_pow(int64 a, int64 b) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % p;
        a = a * a % p;
        b >>= 1;
    }  // while

    return r;
}

inline int64 evaluate(int64 right, int64 m) {
    int64 result = 0;

    while (right / m) {
        result += right / m;
        right /= m;
    }  // while

    return result;
}

int main() {
    initialize();
    evaluate_primes();

    for (int i = 1; i <= cnt && prime[i] <= n * 2; i++) {
        times[i] += evaluate(n * 2, prime[i]) - evaluate(n + 1, prime[i]) -
                    evaluate(n, prime[i]);
    }  // for

    int64 answer = 1;
    for (int i = 1; i <= cnt; i++) {
        if (times[i] == 0)
            continue;

        answer *= quick_pow(prime[i], times[i]);
        answer %= p;
    }  // for

    printf("%lld\n", answer);

    return 0;
}  // function main
