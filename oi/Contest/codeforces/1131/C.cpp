#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 100

static int n;
static int A[NMAX + 10], B[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", A + i);
    sort(A + 1, A + n + 1);
    for (int i = 1, j = 1; i <= n; i++) {
        B[j] = A[i];
        j = n - j + 1;
        if (i % 2 == 0) j++;
    }
    for (int i = 1; i <= n; i++) printf("%d ", B[i]);
    return 0;
}
