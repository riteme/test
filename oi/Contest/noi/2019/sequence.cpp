#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long i64;

static int n, K, L;
static int A[NMAX + 10], B[NMAX + 10], seq[NMAX + 10];
static int ap[NMAX + 10], bp[NMAX + 10];
static bool mark[NMAX + 10];

bool cmpa(int x, int y) {
    return A[x] > A[y] || (A[x] == A[y] && B[x] > B[y]);
}

bool cmpb(int x, int y) {
    return B[x] > B[y] || (B[x] == B[y] && A[x] > A[y]);
}

bool cmpa1(int x, int y) {
    return A[x] < A[y];
}

bool cmpb1(int x, int y) {
    return B[x] < B[y];
}

int main() {
    //freopen("sequence.in", "r", stdin);
    //freopen("sequence.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &K, &L);
        for (int i = 1; i <= n; i++) scanf("%d", A + i);
        for (int i = 1; i <= n; i++) scanf("%d", B + i);
        for (int i = 1; i <= n; i++) ap[i] = bp[i] = i;
        sort(ap + 1, ap + n + 1, cmpa);
        sort(bp + 1, bp + n + 1, cmpb);
        memset(mark, 0, sizeof(mark));

        int p = 1, cnt = 0;
        i64 sum = 0;
        for (; cnt < L || p <= K; p++) {
            sum += A[ap[p]] + B[bp[p]];
            cnt += mark[ap[p]];
            mark[ap[p]] = true;
            cnt += mark[bp[p]];
            mark[bp[p]] = true;
        }

        printf("p = %d, K = %d, L = %d\n", p, K, L);
        int m = 0;
        for (int i = p; i <= n; i++) if (mark[ap[i]]) seq[++m] = ap[i];
        sort(seq + 1, seq + m + 1, cmpb1);
        for (int i = 0; i < p - 1 - K; i++) sum -= B[seq[i + 1]];
        m = 0;
        for (int i = p; i <= n; i++) if (mark[bp[i]]) seq[++m] = bp[i];
        sort(seq + 1, seq + m + 1, cmpa1);
        for (int i = 0; i < p - 1 - K; i++) sum -= A[seq[i + 1]];

        printf("%lld\n", sum);
    }

    return 0;
}
