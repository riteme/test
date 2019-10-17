#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MOD 998244353

#define ASSERT(expr) \
    if (!(expr)) return false;

typedef long long i64;

static int n;
static char s[NMAX + 10];
static i64 sum[NMAX + 10], pw[NMAX + 10];

i64 H(int l, int r) {
    i64 rax = (sum[r] - sum[l - 1] * pw[r - l + 1]) % MOD;
    if (rax < 0) rax += MOD;
    return rax;
}

void initialize() {
    scanf("%s", s + 1);
    pw[0] = 1;
    for (n = 1; s[n]; n++) {
        pw[n] = pw[n - 1] * 10 % MOD;
        sum[n] = (sum[n - 1] * 10 + s[n] - '0') % MOD;
    }
    n--;
}

void print(const char *beg, const char *ed) {
    for ( ; beg != ed; beg++)
        putchar(*beg);
}

void output(int i, int j) {
    print(s + 1, s + i);
    putchar('+');
    print(s + i, s + j);
    putchar('=');
    print(s + j, s + n + 1);
    putchar('\n');
}

bool check(int i, int j) {
    int p, q, k, c = 0;
    for (p = i - 1, q = j - 1, k = n; p >= 1 || q >= i; p--, q--, k--) {
        c += (p >= 1 ? s[p] : '0') - '0' + (q >= i ? s[q] : '0') - '0';
        ASSERT(k && c % 10 == s[k] - '0');
        c /= 10;
    }
    if (c) ASSERT(k && c == s[k--] - '0');
    ASSERT(k == j - 1);
    return true;
}

bool attempt(int i, int j) {
    ASSERT(1 < i && i < j && j <= n);
    ASSERT(i == 2 || s[1] != '0');
    ASSERT(i + 1 == j || s[i] != '0');
    ASSERT(j == n || s[j] != '0');
    ASSERT((H(1, i - 1) + H(i, j - 1)) % MOD == H(j, n));
    ASSERT(check(i, j));
    output(i, j);
    return true;
}

int main() {
    initialize();
    for (int j = n; j >= 1; j--) {
        int l = n - j + 1;
        if (attempt(j - l, j) || attempt(j - l + 1, j) ||
            attempt(l, j) || attempt(l + 1, j))
            break;
    }
    return 0;
}
