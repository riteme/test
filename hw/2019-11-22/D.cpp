#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, m;
static int pre[NMAX + 10], in[NMAX + 10], post[NMAX + 10];

void solve(int pl, int pr, int il, int ir) {
    if (il > ir) return;
    int x = pre[pl];
    if (il < ir) {
        int *it = find(in + il, in + ir + 1, x);
        int lc = it - in - il;
        solve(pl + 1, pl + lc, il, il + lc - 1);
        solve(pl + lc + 1, pr, il + lc + 1, ir);
    }
    post[++m] = x;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++)
            scanf("%d", pre + i);
        for (int i = 1; i <= n; i++)
            scanf("%d", in + i);
        m = 0;
        solve(1, n, 1, n);
        for (int i = 1; i <= n; i++)
            printf(i < n ? "%d " : "%d\n", post[i]);
    }

    return 0;
}
