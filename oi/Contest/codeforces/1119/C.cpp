#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500

static int n, m;
static int A[NMAX + 10][NMAX + 10], B[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        scanf("%d", &A[i][j]);
        A[i][j] ^= A[i - 1][j] ^ A[i][j - 1] ^ A[i - 1][j - 1];
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        scanf("%d", &B[i][j]);
        B[i][j] ^= B[i - 1][j] ^ B[i][j - 1] ^ B[i - 1][j - 1];
    }
    bool ok = true;
    for (int i = 1; i <= n; i++) ok &= A[i][m] == B[i][m];
    for (int i = 1; i <= m; i++) ok &= A[n][i] == B[n][i];
    puts(ok ? "Yes" : "No");
    return 0;
}
