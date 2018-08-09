#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

typedef unsigned long long u64;

#define K 16
#define SMAX (1 << K)
#define NMAX 64

static int n, l;
static u64 A[NMAX];
static bool f[NMAX][SMAX];
static u64 h[NMAX][SMAX], g[NMAX][SMAX];

inline u64 cut(u64 x) {
    return (x >> l) & (SMAX - 1);
}

void dp() {
    memset(f, 0, sizeof(f));
    memset(h, 0, sizeof(h));
    memset(
    f[0][0] = f[0][cut(A[i])] = true;
    h[0][cut(A[i])] = A[i];
    g[0][cut(A[i])] = 1;
    for (int i = 0; i < n - 1; i++) for (u64 s = 0; s < SMAX; s++) {
        if (!f[i][s]) continue;
        u64 ns = cut(h[i][s] + A[i + 1]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%llu", A + i);
    srand(time(NULL));

    return 0;
}
