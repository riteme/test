#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2000

typedef long long i64;
typedef i64 Arr2[NMAX + 1][NMAX + 1];

static int n, K, L;
static int A[NMAX + 10], B[NMAX + 10];
static int seq[NMAX + 10], tmp[NMAX + 10];
static Arr2 pa, pb, sa, sb;

inline void reindex(int *a) {
    memcpy(tmp + 1, a + 1, sizeof(int) * n);
    for (int i = 1; i <= n; i++) a[i] = tmp[seq[i]];
}

inline void calcpre(int *a, Arr2 o) {
    memcpy(seq + 1, a + 1, sizeof(int) * n);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j > 1 && seq[j] > seq[j - 1]; j--) swap(seq[j], seq[j - 1]);
        for (int j = 1; j <= i; j++) o[i][j] = o[i][j - 1] + seq[j];
    }
}

inline void calcsuf(int *a, Arr2 o) {
    memcpy(seq + 1, a + 1, sizeof(int) * n);
    for (int i = n; i >= 1; i--) {
        for (int j = i; j < n && seq[j] > seq[j + 1]; j++) swap(seq[j], seq[j + 1]);
        for (int j = 1; j <= n - i + 1; j++) o[i][j] = o[i][j - 1] + seq[n - j + 1];
    }
}

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &K, &L);
        for (int i = 1; i <= n; i++) scanf("%d", A + i);
        for (int i = 1; i <= n; i++) scanf("%d", B + i);
        for (int i = 1; i <= n; i++) seq[i] = i;
        sort(seq + 1, seq + n + 1, [](int x, int y) {
            return A[x] + B[x] > A[y] + B[y];
        });
        reindex(A); reindex(B);
        calcpre(A, pa); calcpre(B, pb);
        calcsuf(A, sa); calcsuf(B, sb);
        i64 ans = 0;
        for (int x = L; x <= min(n, 2 * K - L); x++)
        for (int y = max(0, x - K); y + L <= x && y + L <= K; y++)
            ans = max(ans,
                pa[x][x - y] + pb[x][L + y] +
                sa[x + 1][K - x + y] + sb[x + 1][K - L - y]);
        printf("%lld\n", ans);
    }
    return 0;
}
