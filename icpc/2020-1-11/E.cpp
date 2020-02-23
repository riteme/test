#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200
#define BASE 19260817

typedef unsigned long long u64;

int n;
u64 pw[NMAX + 10], h[NMAX + 10];
char s[NMAX + 10];

u64 H(int l, int r) {
    return h[r] - h[l - 1] * pw[r - l + 1];
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++)
        pw[i] = pw[i - 1] * BASE;
    for (int i = 1; i <= n; i++)
        h[i] = h[i - 1] * BASE + s[i];

    int ans = n;
    for (int l = 1; l <= n; l++)
    for (int r = l; r <= n; r++) {
        int cnt = 0;
        u64 C = H(l, r);
        for (int i = 1; i <= n; i++)
        if (H(i, i + r - l) == C) {
            cnt++;
            i += r - l;
        }
        ans = min(ans, n - cnt * (r - l) + r - l + 1);
    }

    printf("%d\n", ans);
    return 0;
}