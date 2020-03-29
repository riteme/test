#include <cassert>
#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 50

int n, A, B;
int a[NMAX + 10], b[NMAX + 10];
int f[300];

bool test(int K) {
    f[0] = 0;
    for (int i = 1; i <= A; i++)
        f[i] = INT_MIN;

    for (int i = 1; i <= n; i++) {
        for (int j = A; j >= 0; j--)
        for (int k = 0; k <= j && k * a[i] <= K; k++)
            f[j] = max(f[j], f[j - k] + (K - k * a[i]) / b[i]);

        if (f[A] >= B)
            return true;
    }

    return false;
}

void solve() {
    scanf("%d%d%d", &n, &A, &B);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", a + i, b + i);
        assert(b[i] > 0);
    }

    int l = 0, r = 400000;
    while (l < r) {
        int m = (l + r) / 2;
        if (test(m)) r = m;
        else l = m + 1;
    }

    printf("%d\n", l);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        printf("Case %d: ", t);
        solve();
    }
    return 0;
}