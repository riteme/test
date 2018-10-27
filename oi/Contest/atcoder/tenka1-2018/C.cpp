#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000

static int n;
static i64 A[NMAX + 10], S[NMAX + 10];

inline i64 eval() {
    i64 r = 0;
    for (int i = 1; i < n; i++) r += abs(S[i] - S[i + 1]);
    return r;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", A + i);
    sort(A + 1, A + n + 1);
    for (int i = 1, j = n, t = 1; i <= j; i++, j--) {
        S[t++] = A[i];
        if (i < j) S[t++] = A[j];
    }

    i64 ans = 0;
    if (n & 1) {
        swap(S[1], S[n - 2]);
        ans = eval();
        i64 l = S[n];
        memmove(S + 2, S + 1, sizeof(i64) * (n - 1));
        S[1] = l;
    } else swap(S[1], S[n - 1]);
    ans = max(ans, eval());
    printf("%lld\n", ans);
    return 0;
}
