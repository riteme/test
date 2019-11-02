#include <cstdio>

typedef long long i64;

void dfs(i64 n) {
    if (n <= 1) printf("%lld ", n);
    else {
        dfs(n / 2);
        printf("%lld ", n & 1);
        dfs(n / 2);
    }
}

i64 cnt(i64 n) {
    if (!n) return 1;
    i64 r = n;
    for (int i = 0; n >> i; i++)
        if (!((n >> i) & 1)) r += 1LL << i;
    return r;
}

i64 sum(i64 n, i64 R) {
    if (R < 1) return 0;
    if (n <= 1) return R >= 1 && n;
    i64 lc = cnt(n / 2);
    if (R <= lc) return sum(n / 2, R);
    if (R + 1 <= lc) return n / 2 + (n & 1);
    return n / 2 + (n & 1) + sum(n / 2, R - lc - 1);
}

int main() {
    i64 n, L, R;
    scanf("%lld%lld%lld", &n, &L, &R);
    printf("%lld\n", sum(n, R) - sum(n, L - 1));
    return 0;
}
