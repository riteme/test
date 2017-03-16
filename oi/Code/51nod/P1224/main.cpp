#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MOD 1000000007

typedef long long i64;

static int pcnt;
static int primes[NMAX + 10];
static int mindiv[NMAX + 10];
static bool marked[NMAX + 10];

void process_primes() {
    for (int i = 2; i <= NMAX; i++) {
        if (!marked[i]) {
            primes[++pcnt] = i;
            mindiv[i] = i;
        }

        for (int j = 1; j <= pcnt && i * primes[j] <= NMAX; j++) {
            int p = primes[j];
            marked[i * p] = true;
            mindiv[i * p] = p;

            if (i % p == 0)
                break;
        }
    }
}

static i64 A, K;
static i64 cur = 1;
static i64 e[NMAX + 10];

inline i64 cnt(i64 n, i64 p) {
    i64 ret = 0;

    while (n) {
        ret += n / p;
        n /= p;
    }

    return ret;
}

void initialize() {
    scanf("%lld%lld", &A, &K);

    process_primes();
}

static i64 tpow[64], stk[64];

int main() {
    initialize();

    i64 answer = 0;
    tpow[0] = 1;

    for (int i = 2; i <= A; i++) {
        int u = i;
        while (u > 1) {
            i64 k = 0;
            int p = mindiv[u];
            do {
                u /= p;
                k++;
            } while (mindiv[u] == p);
            e[p] += k * K;

            if (cnt(cur, p) >= e[p])
                continue;

            // 一个log的倍增，比二分强太多了......
            // 主要想法是考虑p的幂次，与cnt函数的过程相对应
            // tpow是p的幂次，stk则是cur = tpow[x]是cnt的返回值
            int pos = 0;
            i64 tmp = e[p];
            for (; stk[pos] < tmp; pos++) {
                tpow[pos + 1] = tpow[pos] * p;
                stk[pos + 1] = stk[pos] + tpow[pos];
            }

            for (cur = 0; pos; pos--) {
                if (tmp < stk[pos])
                    continue;

                i64 q = tmp / stk[pos];
                cur += tpow[pos] * q;
                tmp %= stk[pos];
            }
        }

        answer = (answer + cur) % MOD;
    }

    printf("%lld\n", answer);

    return 0;
}
