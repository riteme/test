#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static int a[NMAX + 10], b[NMAX + 10];
static int seq[NMAX + 10];

int initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", a + i, b + i);
        seq[i] = i;
    }

    return n;
}

int main() {
    int t = 1;
    while (initialize()) {
        sort(seq + 1, seq + n + 1, [](int x, int y) {
            return b[x] > b[y];
        });
        
        int ans = 0, pre = 0;
        for (int i = 1; i <= n; i++) {
            int x = seq[i];
            pre += a[x];
            ans = max(ans, pre + b[x]);
        }

        printf("Case %d: %d\n", t++, ans);
    }

    return 0;
}
