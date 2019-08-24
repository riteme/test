#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#define NMAX 100
#define MMAX 1000000
#define BUFFERSIZE 10000
#define MOD 100000007

typedef long long int64;

static int n;
static int64 m;
static int64 a[NMAX + 10];
static char buffer[BUFFERSIZE + 10];
static int cnt;
static int64 answer[MMAX + 10];

inline int64 mod() {
    int len = strlen(buffer);

    int64 result = 0;
    int64 pow10 = 1;
    for (int i = len - 1; i >= 0; i--) {
        if (buffer[i] == '-') {
            result = -result;
            break;
        }

        result = (result + pow10 * (buffer[i] - '0')) % MOD;
        pow10 = pow10 * 10 % MOD;
    }

    return result;
}

inline int64 evaluate(int64 x) {
    int64 result = (a[n] * x + a[n - 1]) % MOD;

    for (int i = n - 2; i >= 0; i--)
        result = (result * x + a[i]) % MOD;

    return result;
}

int main() {
    scanf("%d%lld", &n, &m);

    for (int i = 0; i <= n; i++) {
        scanf("%s", buffer);
        a[i] = mod();
    }

    for (int64 x = 1; x <= m; x++)
        if (evaluate(x) == 0)
            answer[++cnt] = x;

    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++)
        printf("%lld\n", answer[i]);

    return 0;
}
