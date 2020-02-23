#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

int n;
i64 K;
char s[2 * NMAX + 10];

i64 eval(i64 L) {
    if (L <= K)
        return L * (L + 1) / 2;
    return K * L - K * (K - 1) / 2;
}

int main() {
    scanf("%s%lld", s + 1, &K);
    n = strlen(s + 1);
    memcpy(s + n + 1, s + 1, n);
    int i = 1;
    for ( ; s[i] == 'P' && i <= n; i++) ;
    if (i == n + 1) puts("0");
    else {
        i64 ans = K * n;
        for (int j = i + 1, k; j <= i + n; j = k) if (s[j] == 'P') {
            k = j;
            for ( ; k <= i + n && s[k] == s[j]; k++) ;
            ans -= eval(k - j);
        } else k = j + 1;
        printf("%lld\n", ans);
    }

    return 0;
}