#include <cstdio>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

int m;
int p[NMAX + 10];
i64 A[NMAX + 10], B[NMAX + 10];

int main() {
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        p[i] = i;
        scanf("%lld%lld", A + i, B + i);
    }

    sort(p + 1, p + m + 1, [](int i, int j) {
        i64 pi = A[i], qi = A[i] + B[i];
        i64 pj = A[j], qj = A[j] + B[j];
        if (pi * qj > pj * qi)
            return true;
        if (pi * qj == pj * qi && i < j)
            return true;
        return false;
    });

    for (int i = 1; i <= m; i++) {
        printf("%d ", p[i]);
    }
    puts("");

    return 0;
}
