#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000
#define MOD 1000000007

typedef long long i64;

int n;
int b[NMAX + 10];
i64 g[NMAX + 10][NMAX + 10];

i64 add(i64 a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
    return a;
}

i64 sub(i64 a, i64 b) {
    a -= b;
    if (a < 0)
        a += MOD;
    return a;
}

void _main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", b + i);
    }

    g[1][1] = 1;
    for (int i = 2; i <= n; i++)
    for (int k = 1; k <= i; k++) {
        i64 v;
        if (b[i] == 0)
            v = g[i - 1][k - 1];
        else
            v = sub(g[i - 1][i - 1], g[i - 1][k - 1]);
        g[i][k] = add(g[i][k - 1], v);
    }

    printf("%lld\n", g[n][n]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
