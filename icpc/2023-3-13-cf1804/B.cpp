#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

constexpr int NMAX = 200000;

int n, K, D, W;
int a[NMAX + 10];

bool intersect(int l1, int r1, int l2, int r2) {
    return !(r1 < l2 || r2 < l1);
}

void solve() {
    scanf("%d%d%d%d", &n, &K, &D, &W);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    int cnt = 0;
    for (int i = 1; i <= n;) {
        cnt++;
        int j = i + 1;
        int used = 1;
        int t = a[i] + W;
        while (used < K && j <= n && intersect(a[j], a[j] + W, t, t + D)) {
            used++;
            j++;
        }
        i = j;
    }
    printf("%d\n", cnt);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
