#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 300000;
constexpr int INF = 1000000000;

int n;
int lp[NMAX + 10], mx[NMAX + 10];
int a[NMAX + 10], b[NMAX + 10];

void _main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        b[i] = INF;
        lp[i] = 0;
        mx[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        mx[a[i]] = max(mx[a[i]], i - lp[a[i]]);
        lp[a[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        mx[i] = max(mx[i], n + 1 - lp[i]);
        b[mx[i]] = min(b[mx[i]], i);
    }

    for (int i = 2; i <= n; i++) {
        b[i] = min(b[i - 1], b[i]);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", b[i] >= INF ? -1 : b[i]);
    }
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}