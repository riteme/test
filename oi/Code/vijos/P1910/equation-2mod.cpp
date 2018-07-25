#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#define NMAX 100
#define MMAX 1000000
#define BUFFERSIZE 10000
#define MOD1 100000007
#define MOD2 99999999967

typedef long long int64;

static int n;
static int64 m;
static int64 a1[NMAX + 10];
static int64 a2[NMAX + 10];
static char buffer[BUFFERSIZE + 10];
static int cnt;
static int64 answer[MMAX + 10];

inline int64 mod1() {
    int len = strlen(buffer);

    int64 result = 0;
    int64 pow10 = 1;
    for (int i = len - 1; i >= 0; i--) {
        if (buffer[i] == '-') {
            result = -result;
            break;
        }

        result = (result + pow10 * (buffer[i] - '0')) % MOD1;
        pow10 = pow10 * 10 % MOD1;
    }

    return result;
}

inline int64 mod2() {
    int len = strlen(buffer);

    int64 result = 0;
    int64 pow10 = 1;
    for (int i = len - 1; i >= 0; i--) {
        if (buffer[i] == '-') {
            result = -result;
            break;
        }

        result = (result + pow10 * (buffer[i] - '0')) % MOD2;
        pow10 = pow10 * 10 % MOD2;
    }

    return result;
}

inline int64 evaluate1(int64 x) {
    int64 result = (a1[n] * x + a1[n - 1]) % MOD1;

    for (int i = n - 2; i >= 0; i--)
        result = (result * x + a1[i]) % MOD1;

    return result;
}

inline int64 evaluate2(int64 x) {
    int64 result = (a2[n] * x + a2[n - 1]) % MOD2;

    for (int i = n - 2; i >= 0; i--)
        result = (result * x + a2[i]) % MOD2;

    return result;
}

int main() {
    scanf("%d%lld", &n, &m);

    for (int i = 0; i <= n; i++) {
        scanf("%s", buffer);
        a1[i] = mod1();
        a2[i] = mod2();
    }

    for (int64 x = 1; x <= m; x++)
        if (evaluate1(x) == 0 && evaluate2(x) == 0)
            answer[++cnt] = x;

    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++)
        printf("%lld\n", answer[i]);

    return 0;
}
