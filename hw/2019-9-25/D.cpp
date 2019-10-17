#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 4000

static int n, X[NMAX + 10], A[NMAX + 10];
static int L[NMAX + 10], R[NMAX + 10];
static int seq[NMAX + 10];
static bool ok[NMAX + 10], cov[2 * NMAX + 10];

bool cmp(int i, int j) {
    return A[i] > A[j];
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        for (int i = 1; i <= n; i++) {
            scanf("%d", A + i);
            seq[i] = i;
            if (i > 1) {
                X[i] = 0;
                for (int j = 1; j < i; j++)
                    X[i] = max(X[i], X[j] + 2 * min(A[i], A[j]));
            } else X[i] = A[i];
            L[i] = X[i] - A[i];
            R[i] = X[i] + A[i] - 1;
        }
        sort(seq + 1, seq + n + 1, cmp);
        memset(cov, 0, sizeof(cov));
        for (int _i = 1; _i <= n; _i++) {
            int i = seq[_i];
            ok[i] = false;
            for (int j = L[i]; j <= R[i]; j++) {
                ok[i] |= !cov[j + NMAX];
                cov[j + NMAX] = true;
            }
        }
        for (int i = 1; i <= n; i++) if (ok[i])
            printf("%d ", i);
        puts("");
    }
    return 0;
}
