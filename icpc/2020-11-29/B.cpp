#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm>

using namespace std;

constexpr int NMAX = 10000;

int n;
int a[NMAX + 10], b[NMAX + 10], c[NMAX + 10];

int cnt;
struct {
    int i, j, x;
} r[4 * NMAX + 10];

void mov(int i, int j, int x, bool mod = true) {
    if (x == 0)
        return;

    r[cnt++] = {i, j, x};
    if (mod) {
        a[i] -= i * x;
        a[j] += i * x;
        assert(a[i] >= 0);
        assert(a[j] >= 0);
    }
}

void _main() {
    cnt = 0;
    scanf("%d", &n);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        sum += a[i];
        b[i] = c[i] = i;
    }

    if (sum % n) {
        puts("-1");
        return;
    }

    int aver = sum / n;
    sort(b + 2, b + n + 1, [](int i, int j) {
        return i - a[i] % i < j - a[j] % j;
    });
    sort(c + 2, c + n + 1, [](int i, int j) {
        return a[i] - a[i] % i > a[j] - a[j] % j;
    });

    int j = 2, k = 2;
    while (true) {
        while (j <= n && a[j] == 0) j++;
        while (k <= n && a[k] < k) k++;

        if (j > n && k > n)
            break;

        int cj = j - a[j] % j;
        if (j <= n && cj <= a[1]) {
            mov(1, j, cj);
            mov(j, 1, a[j] / j);
        } else if (k <= n) {
            mov(k, 1, a[k] / k);
        } else {
            puts("-1");
            return;
        }
    }

    for (int i = 2; i <= n; i++) {
        mov(1, i, aver);
    }

    assert(cnt <= 3 * n);
    for (int i = 1; i <= n; i++) {
        assert(a[i] == aver);
    }

    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++) {
        printf("%d %d %d\n", r[i].i, r[i].j, r[i].x);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}