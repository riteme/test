#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define BASE 19260817

typedef unsigned long long u64;

u64 pw[NMAX + 10];
char ci[256], rev[256];
char s[NMAX + 10], t[NMAX + 10];
u64 S[NMAX + 10], T[NMAX + 10];

int main() {
    pw[0] = 1;
    for (int i = 1; i <= NMAX; i++)
        pw[i] = pw[i - 1] * BASE;

    int _t;
    scanf("%d", &_t);
    while (_t--) {
        scanf("%s", ci);
        for (int i = 0; i < 26; i++)
            rev[ci[i]] = 'a' + i;
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        for (int i = 1; i <= n; i++)
            t[i] = rev[s[i]];

        for (int i = 1; i <= n; i++) {
            S[i] = S[i - 1] * BASE + s[i];
            T[i] = T[i - 1] * BASE + t[i];
        }

        int len = (n + 1) / 2;
        for (; len <= n; len++) {
            int L = n - len;
            u64 Sc = S[n] - S[n - L] * pw[L];
            u64 Tc = T[L];
            if (Sc == Tc)
                break;
        }

        // printf("%d\n", len);
        for (int i = 1; i <= len; i++)
            putchar(s[i]);
        for (int i = 1; i <= len; i++)
            putchar(rev[s[i]]);
        puts("");
    }
    return 0;
}