#include <cstdio>
#include <cstring>
#include <climits>

#include <stack>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 1000000

static int n;
static i64 A[NMAX + 10];
static int L[NMAX + 10], R[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    A[0] = INT_MIN;
    A[n + 1] = INT_MAX;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
    }

    stack<int> stk;
    for (int i = 1; i <= n + 1; i++) {
        while (!stk.empty() && A[stk.top()] < A[i]) {
            R[stk.top()] = i;
            stk.pop();
        }

        stk.push(i);
    }

    stk.pop();
    for (int i = n; i >= 0; i--) {
        while (!stk.empty() && A[stk.top()] <= A[i]) {
            L[stk.top()] = i;
            stk.pop();
        }

        stk.push(i);
    }
}

static i64 B[NMAX + 10], C[NMAX + 10];

inline void add(int l, int r, i64 s, i64 d) {
    // printf("[%d, %d] += %lld + %lldx\n", l, r, s, d);
    if (r < l)
        return;

    B[l] += s;
    B[r + 1] -= s + d * (r - l + 1);
    C[l - 1] += d;
    C[r] -= d;
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();

    for (int i = 1; i <= n; i++) {
        int p = i - L[i], q = R[i] - i, l = R[i] - L[i] - 1;
        if (p > q)
            swap(p, q);

        // printf("A[%d] = %lld\n", i, A[i]);
        // printf("p = %d, q = %d, l = %d\n", p, q, l);
        add(1, p, 0, A[i]);
        add(p + 1, q, p * A[i], 0);
        add(q + 1, l, (l - q + 1) * A[i], -A[i]);
    }

    memset(A, 0, sizeof(A));
    i64 k = 0;
    for (int i = 0; i <= n; i++) {
        A[i] = A[i - 1] + B[i] + k;
        k += C[i];
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        // printf("%lld ", A[i]);
        ans ^= A[i] % 998244353;
    }
    // puts("\n");

    printf("%lld\n", ans);

    return 0;
}
