#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static int f[NMAX + 10];
static int sorted[NMAX + 10];
static int seq[NMAX + 10];

static bool cmp(const int a, const int b) {
    return f[a] < f[b] || (f[a] == f[b] && a > b);
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", f + i);
        sorted[i] = i;
    }

    sort(sorted + 1, sorted + n + 1, cmp);
}

int main() {
    initialize();

    for (int v = 1; v <= n; v++) {
        seq[sorted[v]] = v;
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", seq[i]);
    }

    return 0;
}
