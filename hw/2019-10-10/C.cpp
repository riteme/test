#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, K, q;
static int a[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &K, &q);
    while (n--) {
        int l, r;
        scanf("%d%d", &l, &r);
        a[l]++;
        a[r + 1]--;
    }
    for (int i = 1; i <= NMAX + 1; i++) {
        a[i] += a[i - 1];
        a[i - 1] = a[i - 2] + (a[i - 1] >= K);
    }
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", a[r] - a[l - 1]);
    }
    return 0;
}
