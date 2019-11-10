#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, K;
static int a[NMAX + 10];

void solve(int l, int r) {
    //fprintf(stderr, "[%d, %d]\n", l, r);
    if (l + 1 < r) {
        int m = (l + r) / 2;
        if (K) {
            K -= 2;
            solve(l, m);
            solve(m, r);
        } else reverse(a + l, a + r);
    }
}

int main() {
    scanf("%d%d", &n, &K);
    if (K & 1) {
        K--;
        for (int i = 0; i < n; i++)
            a[i] = n - i;
        solve(0, n);
        if (K) puts("-1");
        else {
            for (int i = 0; i < n; i++)
                printf("%d ", a[i]);
            puts("");
        }
    } else puts("-1");
    return 0;
}
