#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 2000
#define INF 0x3f3f3f3f3f3f3f3f

int n;
i64 H;
struct Person {
    i64 a, b;

    bool operator<(const Person &z) const {
        return a + b < z.a + z.b;
    }
} p[NMAX + 10];
i64 f[NMAX + 10][NMAX + 10];

void solve() {
    i64 S = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &p[i].a, &p[i].b);
        S += p[i].a;
    }
    scanf("%lld", &H);

    sort(p + 1, p + n + 1);

    for (int i = 1; i <= n; i++)
    for (int j = 0; j <= i; j++) {
        f[i][j] = INF;
        if (j < i)
            f[i][j] = min(f[i][j], f[i - 1][j]);
        if (j > 0 && S - f[i - 1][j - 1] + p[i].b >= H)
            f[i][j] = min(f[i][j], f[i - 1][j - 1] + p[i].a);
    }

    int ans = n;
    for ( ; f[n][ans] == INF; ans--) ;
    printf("%d\n", ans);
}

int main() {
    while (scanf("%d", &n) != EOF)
        solve();
    return 0;
}