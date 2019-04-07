#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 300000

static int n, seq[NMAX + 10];
static int L[NMAX + 10], R[NMAX + 10];
static int pl[NMAX + 10], sl[NMAX + 10], pr[NMAX + 10], sr[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) L[i] = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);
        seq[i] = c;
        L[c] = min(L[c], i);
        R[c] = max(R[c], i);
    }
    pl[0] = sl[n + 1] = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        pl[i] = min(pl[i - 1], L[i]);
        pr[i] = max(pr[i - 1], R[i]);
    }
    for (int i = n; i >= 1; i--) {
        sl[i] = min(sl[i + 1], L[i]);
        sr[i] = max(sr[i + 1], R[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int c = seq[i];
        int p = min(pl[c - 1], sl[c + 1]), q = max(pr[c - 1], sr[c + 1]);
        ans = max(ans, max(i - p, q - i));
    }
    printf("%d\n", ans);

    return 0;
}