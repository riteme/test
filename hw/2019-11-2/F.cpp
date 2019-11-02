#include <cstdio>
#include <cstring>

#define NMAX 200000
#define A 19260817
#define B 0x87654321deedbeef
#define C 998244353

typedef unsigned long long u64;

u64 H(char *s, int n) {
    if (n & 1) {
        u64 r = 0, pw = 1;
        for (int i = 0; i < n; i++, pw *= A)
            r += s[i] * pw;
        return r;
    }

    u64 L = H(s, n / 2);
    u64 R = H(s + n / 2, n / 2);
    return (L ^ B) * (R ^ B) * C;
}

static char S[NMAX + 10], T[NMAX + 10];

int main() {
    scanf("%s%s", S, T);
    int n = strlen(S);
    puts(H(S, n) == H(T, n) ? "YES" : "NO");
    return 0;
}
