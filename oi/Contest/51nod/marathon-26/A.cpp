#pragma GCC optimize(3)
#pragma optimize("t", on)

#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t pos = BUFFERSIZE;
static char buf[BUFFERSIZE];

inline char _getchar() {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buf, 1, BUFFERSIZE, stdin);
    }
    return buf[pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c = _getchar();

    do {
        c = _getchar();
    } while (!isdigit(c));

    do {
        x = x * 10 + (c - '0');
        c = _getchar();
    } while (isdigit(c));
}

#define NMAX 2000000
#define MOD 1000000007
#define INV2 500000004

typedef long long i64;

static int n;
static i64 t;
static i64 num[NMAX];
static i64 prod[NMAX];

inline i64 qpow(i64 a, i64 b) {
    i64 r = 1;
    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

void fwt(i64 X[]) {
    for (int s = 1; s < n; s <<= 1) {
        int l = s << 1;
        for (int i = 0; i < n; i += l) {
            for (int j = i; j < i + s; j++) {
                i64 t = X[j + s];
                X[j + s] = (X[j] - t) % MOD;
                X[j] = (X[j] + t) % MOD;
            }
        }
    }
}

void rfwt(i64 X[]) {
    for (int s = 1; s < n; s <<= 1) {
        int l = s << 1;
        for (int i = 0; i < n; i += l) {
            for (int j = i; j < i + s; j++) {
                i64 t = X[j + s];
                X[j + s] = (X[j] - t) * INV2 % MOD;
                X[j] = (X[j] + t) * INV2 % MOD;
            }
        }
    }
}

void initialize() {
    scanf("%d%lld", &n, &t);
    n = 1 << n;

    for (int i = 0; i < n; i++) {
        scanf("%lld", num + i);
    }

    prod[0] = 1;
    for (int i = 1; i < n; i <<= 1) {
        prod[i] = 1;
    }
}

int main() {
    initialize();

    fwt(num);
    fwt(prod);

    for (int i = 0; i < n; i++) {
        prod[i] = qpow(prod[i], t);
        num[i] = num[i] * prod[i] % MOD;
    }

    rfwt(num);

    for (int i = 0; i < n; i++) {
        if (num[i] < 0)
            num[i] += MOD;

        printf("%lld ", num[i]);
    }
    putchar('\n');

    return 0;
}
