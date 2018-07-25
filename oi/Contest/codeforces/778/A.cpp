#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, m;
static int t[NMAX + 10];
static char T[NMAX + 10], P[NMAX + 10];

bool test(int x) {
    int j = 1;
    for (int i = 1; i <= n && j <= m; i++) {
        if (t[i] <= x)
            continue;
        if (T[i] == P[j])
            j++;
    }

    return j > m;
}

int main() {
    scanf("%s%s", T + 1, P + 1);
    n = strlen(T + 1), m = strlen(P + 1);

    for (int i = 1; i <= n; i++) {
        int u;
        scanf("%d", &u);
        t[u] = i;
    }

    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2 + 1;

        if (test(mid))
            l = mid;
        else
            r = mid - 1;
    }

    printf("%d\n", l);

    return 0;
}
