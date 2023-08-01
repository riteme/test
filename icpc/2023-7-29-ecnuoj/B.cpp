#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

constexpr int NMAX = 100000;

int n, T, X;
int a[NMAX + 10];

bool check(int i, int x) {
    return a[i] - T <= x && x <= a[i] + T;
}

int test(int b) {
    int combo = 0, max_combo = 0;
    for (int i = 1; i <= n; i++) {
        if (check(i, b - X) || check(i, b) || check(i, b + X))
            combo++;
        else
            combo = 0;
        max_combo = max(max_combo, combo);
    }
    return max_combo;
}

int main() {
    scanf("%d%d%d", &n, &X, &T);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        a[i] %= X;
    }

    int ans = 0;
    for (int b = 0; b < X; b++) {
        ans = max(ans, test(b));
    }

    printf("%d\n", ans);
    return 0;
}
