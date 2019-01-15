#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100

static int n, m, L[NMAX + 10], R[NMAX + 10];
static int pos[NMAX  + 10], seq[NMAX + 10];
static int pre[NMAX + 10], suc[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        pos[i] = i;
        scanf("%d%d", L + i, R + i);
    }
    for (int i = 1; i <= m; i++) scanf("%d%d", pre + i, suc + i);
    bool ok;
    do {
        ok = true;
        for (int i = 1; i <= n; i++) ok &= L[i] <= pos[i] && pos[i] <= R[i];
        for (int i = 1; i <= m; i++) ok &= pos[pre[i]] < pos[suc[i]];
    } while (!ok && next_permutation(pos + 1, pos + n + 1));
    if (ok) {
        for (int i = 1; i <= n; i++) seq[pos[i]] = i;
        for (int i = 1; i <= n; i++) printf("%d\n", seq[i]);
    } else puts("-1");

    return 0;
}
