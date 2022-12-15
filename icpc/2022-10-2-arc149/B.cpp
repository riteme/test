#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 300000;

int n;
int v[NMAX + 10], f[NMAX + 10], p[NMAX + 10];

int solve() {
    int m = 1, ans = 1;
    for (int i = 1; i <= n; i++) {
        int j = upper_bound(p, p + m, v[i]) - p;
        f[i] = j;
        ans = max(ans, j);
        if (j == m) {
            m++;
            p[j] = v[i];
        } else {
            p[j] = min(p[j], v[i]);
        }
    }
    return ans;
}

int a[NMAX + 10], b[NMAX + 10];
int s[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        s[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", b + i);
    }

    sort(s + 1, s + n + 1, [](int i, int j) { return a[i] < a[j]; });
    for (int i = 1; i <= n; i++) {
        v[i] = b[s[i]];
    }
    int ans1 = n + solve();

    sort(s + 1, s + n + 1, [](int i, int j) { return b[i] < b[j]; });
    for (int i = 1; i <= n; i++) {
        v[i] = a[s[i]];
    }
    int ans2 = n + solve();

    int ans = max(ans1, ans2);
    printf("%d\n", ans);

    return 0;
}
