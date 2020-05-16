#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define M1 998244353
#define M2 247929239
#define BASE 19260817

typedef long long i64;

struct Hash {
    i64 h1, h2;

    Hash operator+(i64 v) const {
        i64 g1 = h1 + v, g2 = h2 + v;
        if (g1 >= M1) g1 -= M1;
        if (g2 >= M2) g2 -= M2;
        return {g1, g2};
    }

    Hash operator*(i64 v) const {
        return {h1 * v % M1, h2 * v % M2};
    }

    Hash operator+(const Hash &z) const {
        i64 g1 = h1 + z.h1, g2 = h2 + z.h2;
        if (g1 >= M1) g1 -= M1;
        if (g2 >= M2) g2 -= M2;
        return {g1, g2};
    }

    Hash operator-(const Hash &z) const {
        i64 g1 = h1 - z.h1, g2 = h2 - z.h2;
        if (g1 < 0) g1 += M1;
        if (g2 < 0) g2 += M2;
        return {g1, g2};
    }

    Hash operator*(const Hash &z) const {
        return {h1 * z.h1 % M1, h2 * z.h2 % M2};
    }

    bool operator==(const Hash &z) const {
        return h1 == z.h1 && h2 == z.h2;
    }
};

#define NMAX 100000

Hash pw[NMAX + 10];

int n;
char s[NMAX + 10];
Hash h[NMAX + 10];

Hash get(int l, int r) {
    return h[r] - h[l - 1] * pw[r - l + 1];
}

struct ran {
    int l, r;

    int len() const {
        return r - l + 1;
    }
};

int cmp(const ran &s1, const ran &s2) {
    int l = 0, r = min(s1.len(), s2.len());
    while (l < r) {
        int m = (l + r) / 2 + 1;
        if (get(s1.l, s1.l + m - 1) == get(s2.l, s2.l + m - 1))
            l = m;
        else
            r = m - 1;
    }

    char c1 = l == s1.len() ? 0 : s[s1.l + l];
    char c2 = l == s2.len() ? 0 : s[s2.l + l];
    if (c1 < c2)
        return -1;
    if (c1 > c2)
        return +1;
    return 0;
}

int sp, ans[NMAX + 10];
ran stk[NMAX + 10];

void solve() {
    scanf("%d%s", &n, s + 1);
    h[0] = {1, 1};
    for (int i = 1; i <= n; i++)
        h[i] = h[i - 1] * BASE + s[i];

    sp = 0;
    for (int i = n; i >= 1; i--) {
        stk[sp++] = {i, i};
        for (; sp > 1 && cmp(stk[sp - 1], stk[sp - 2]) < 0; sp--)
            stk[sp - 2] = {stk[sp - 1].l, stk[sp - 2].r};
        ans[i] = stk[sp - 1].len();
    }

    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
}

int main() {
    pw[0] = {1, 1};
    for (int i = 1; i <= NMAX; i++)
        pw[i] = pw[i - 1] * BASE;

    int T;
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}